
#include <stdlib.h>
#include "tokeniser.h"

t_token		*token_concat_by_pair(t_token *tmp, char *def, t_ttype token_id)
{
  t_token	*ptr;

  if ((tmp == NULL) || (tmp && tmp->next == NULL))
    return (NULL);
  ptr = tmp->next;
  tmp->next = ptr->next;
  free(ptr);
  tmp->value.str = def;
  tmp->value_type = STRING;
  tmp->type = token_id;
  return (tmp);
}

t_token		*token_concat_by_type(t_token *current, t_ttype define)
{
  t_token	*ptr;
  char		*concat;
  int		i;

  if (current == NULL)
    return (NULL);
  i = lexer_find_occurences(current, define);
  ptr = lexer_find_last_occurences(current, define);
  concat = NULL;
  concat = token_concat_string(current, ptr, i);
  current->value.str = concat;
  current->type = define;
  current->value_type = STRING;
  return (current);
}

int	token_concat_op(t_token **list,
			char *new_define,
			t_ttype token_id,
			t_ttype op_id)
{
  t_token	*tmp;

  tmp = *list;
  if (tmp == NULL)
    return (EXIT_FAILURE);
  while (tmp && tmp->next)
    {
      if (tmp->type == op_id && tmp->next->type == op_id)
	if ((tmp = token_concat_by_pair(tmp, new_define, token_id)) == NULL)
	  return (EXIT_FAILURE);
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}

int	token_concat_define(t_token **list,
			    char *new_define,
			    t_ttype token_id,
			    char define)
{
  t_token	*tmp;

  tmp = *list;
  if (tmp == NULL)
    return (EXIT_FAILURE);
  while (tmp && tmp->next)
    {
      if (tmp->value.define == define && tmp->next->value.define == define)
	{
	  if ((tmp = token_concat_by_pair(tmp, new_define, token_id)) == NULL)
	    return (EXIT_FAILURE);
	}
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}
