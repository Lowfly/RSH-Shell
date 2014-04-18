
#include <stdlib.h>
#include "tokeniser.h"

int	token_sequences_begin(t_token **list)
{
  t_token	*begin;

  begin = NULL;
  if ((begin = malloc(sizeof(*begin))) == NULL)
    return (EXIT_FAILURE);
  begin->type = SEPARATOR;
  begin->value_type = LIST;
  begin->value.list = *list;
  begin->next = NULL;
  *list = begin;
  return (EXIT_SUCCESS);
}

int	token_sequences_exam(t_token **list)
{
  t_token	*root;
  t_token	*tmp;
  t_token	*prev;

  tmp = (*list)->value.list;
  prev = tmp;
  root = *list;
  while (tmp)
    {
      if (tmp->type == SEPARATOR)
  	{
	  (prev != tmp) ? (prev->next = NULL) : (root->value.list = NULL);
	  root->next = tmp;
	  tmp->value_type = LIST;
	  tmp->value.list = tmp->next;
	  root = tmp;
	  tmp = tmp->next;
	  root->next = NULL;
  	}
      prev = tmp;
      if (tmp && tmp->type != SEPARATOR)
	tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}

int		token_sequences(t_token **list)
{
  t_token	*tmp;
  t_token	*ptr;
  t_token	*del;

  if ((token_sequences_begin(list) == EXIT_FAILURE) ||
      (token_sequences_exam(list) == EXIT_FAILURE))
    return (EXIT_FAILURE);
  tmp = *list;
  ptr = tmp;
  while (tmp)
    {
      if (tmp->type == SEPARATOR && tmp->value.list == NULL)
  	{
  	  (*list != tmp && ptr) ? (ptr->next = tmp->next) : (*list = tmp->next);
  	  del = tmp;
  	  tmp = tmp->next;
    	  token_delete(del);
  	}
      else
  	{
  	  ptr = tmp;
  	  tmp = tmp->next;
  	}
    }
  return (EXIT_SUCCESS);
}
