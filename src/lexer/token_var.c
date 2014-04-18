
#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"
#include "my.h"

t_token	*token_var_is_bad(t_token *current)
{
  if (current->next->type == WORD)
    current = token_concat_by_pair(current, current->next->value.str, VAR);
  else
    current->value.str = NULL;
  return (current);
}

t_token	*token_var_is_good(t_token *current)
{
  t_token	*ptr;

  if (current->next->type == VAR &&
      current->next->next->type == WORD)
    {
      ptr = current->next;
      ptr = token_concat_by_pair(ptr, ptr->next->value.str, VAR);
      current->next = ptr;
    }
  else
    current->next->value.str = NULL;
  return (current);
}

int	token_var(t_token **list)
{
  t_token	*tmp;

  tmp = *list;
  while (tmp)
    {
      if (tmp->type == WORD && tmp->next && tmp->next->type == VAR &&
	  tmp->next->next && tmp->next->next->type == WORD)
	{
	  if ((tmp = token_var_is_good(tmp)) == NULL)
	    return (EXIT_FAILURE);
	  tmp = tmp->next;
	}
      else if (tmp->type == VAR && tmp->next)
	{
	  if ((tmp = token_var_is_bad(tmp)) == NULL)
	    return (EXIT_FAILURE);
	}
      else if (tmp->type == VAR)
	  tmp->value.str = NULL;
      if (tmp)
	tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}

t_token		*token_var_replace_search(t_token *current, t_shell *sh)
{
  t_token	*new;
  t_token	*save;
  char		*replace;

  if ((replace = explor_env(sh->env, current->value.str)) == NULL)
    replace = explor_env(sh->local, current->value.str);
  if ((replace == NULL) || ((new = tokeniser(replace)) == NULL))
    {
      if (current->value.str)
	fprintf(stderr, "%s", current->value.str);
      lexer_err(UNDIF_VAR, VAR);
      return (NULL);
    }
  save = current;
  current = new;
  while (new->next)
    new = new->next;
  new->next = save->next;
  save->next = NULL;
  token_delete(save);
  return (current);
}

t_token		*token_var_replace(t_token *current, t_shell *sh)
{
  if (current->type == VAR)
    {
      if ((current = token_var_replace_search(current, sh)) == NULL)
	return (NULL);
    }
  return (current);
}
