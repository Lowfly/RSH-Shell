
#include <stdlib.h>
#include "tokeniser.h"
#include "shell.h"

int	token_save_cpy(t_token **begin, t_token *elem)
{
  t_token	*cpy;

  cpy = NULL;
  if ((cpy = malloc(sizeof(*elem))) == NULL)
    return (EXIT_FAILURE);
  cpy->type = SAVE;
  cpy->value.list = elem;
  cpy->value_type = LIST;
  cpy->next = *begin;
  *begin = cpy;
  return (EXIT_SUCCESS);
}

int	token_save(t_shell *sh, t_token *list)
{
  t_token	*tmp;

  tmp = list;
  while (tmp)
    {
      if (tmp->value_type == LIST)
	token_save(sh, tmp->value.list);
      if (token_save_cpy(&(sh->list), tmp) == EXIT_FAILURE)
	return (EXIT_FAILURE);
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}

int	token_save_free(t_shell *sh)
{
  t_token	*tmp;
  t_token	*save;

  tmp = sh->list;
  show_token_list(tmp);
  sh->list = NULL;
  save = tmp;
  while (tmp)
    {
      free(tmp->value.list);
      tmp = tmp->next;
      free(save);
      save = tmp;
    }
  return (EXIT_SUCCESS);
}
