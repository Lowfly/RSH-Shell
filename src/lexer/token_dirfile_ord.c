
#include <stdlib.h>
#include "tokeniser.h"

int		type_is_good(t_ttype token)
{
  if (token == RED_L || token == RED_R || token == D_RED_R
      || token == D_RED_L)
    return (1);
  else if (token == FILENAME || token == SPACE)
    return (1);
  else if (token == WORD)
    return (2);
  return (0);
}

t_token		*token_dir_ord_first(t_token **list)
{
  t_token	*ptr;
  t_token	*save;
  t_token	*tmp;
  int		ret;

  save = *list;
  ptr = *list;
  ret = type_is_good(ptr->type);
  while (ptr && ret != 0 && ret == 1)
    {
      ret = type_is_good(ptr->type);
      if (ret != 2)
	ptr = ptr->next;
    }
  if (ptr == NULL || ptr->type != WORD)
    return (save);
  *list = ptr;
  while (ptr->next && ptr->next->type == SPACE)
    ptr = ptr->next;
  tmp = save;
  while (tmp->next != *list)
    tmp = tmp->next;
  tmp->next = ptr->next;
  ptr->next = save;
  return (save->next);
}

int		token_dir_ord_current(t_token *current)
{
  t_token	*ptr;
  t_token	*save;
  t_token	*tmp;
  int		ret;

  save = current->next;
  ptr = current->next;
  ret = type_is_good(ptr->type);
  while (ptr && ret != 0 && ret == 1)
    {
      ret = type_is_good(ptr->type);
      if (ret != 2)
	ptr = ptr->next;
    }
  if (ptr == NULL || ptr->type != WORD)
    return (EXIT_SUCCESS);
  current->next = ptr;
  while (ptr->next && ptr->next->type == SPACE)
    ptr = ptr->next;
  tmp = save;
  while (tmp->next != current->next)
    tmp = tmp->next;
  tmp->next = ptr->next;
  ptr->next = save;
  return (EXIT_SUCCESS);
}

int		token_dirfile_check_current(t_token *tmp)
{
  t_token	*ptr;
  t_token	*type;

  type = tmp;
  ptr = tmp;
  while (ptr->next &&
         ((ptr->next->type != RED_R && ptr->next->type != D_RED_R &&
           ptr->next->type != RED_L && ptr->next->type != D_RED_L)))
    {
      if (ptr->type != SPACE)
        type = ptr;
      ptr = ptr->next;
    }
  tmp = ptr->next;
  if (ptr->next && type->type != WORD &&
      ((ptr->next->type == RED_R || ptr->next->type == D_RED_R ||
        ptr->next->type == RED_L || ptr->next->type == D_RED_L)))
    token_dir_ord_current(ptr);
  return (EXIT_SUCCESS);
}

int		token_dirfile_ord(t_token **list)
{
  t_token	*tmp;

  tmp = *list;
  while (tmp)
    {
      if (tmp == *list && (tmp->type == RED_R || tmp->type == D_RED_R ||
                           tmp->type == RED_L || tmp->type == D_RED_L))
        tmp = token_dir_ord_first(list);
      else
        token_dirfile_check_current(tmp);
      if (tmp)
        tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}
