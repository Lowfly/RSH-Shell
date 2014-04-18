
#include <stdlib.h>
#include "lexer.h"
#include "tokeniser.h"

int	is_cmd(t_ttype id_token)
{
  if (id_token == WORD || id_token == SPACE || id_token == S_QUOTE
      || id_token == D_QUOTE)
    return (1);
  return (0);
}

t_token	*token_cmd_clean(t_token *box)
{
  t_token	*tmp;
  t_token	*link;

  tmp = box->value.list;
  while (tmp)
    {
      link = tmp;
      if (tmp->next && tmp->next->type == SPACE)
	{
	  tmp = tmp->next->next;
	  token_delete(link->next);
	  link->next = tmp;
	}
      else if (tmp->type == SPACE)
        {
          box->value.list = tmp->next;
          token_delete(tmp);
          tmp = box->value.list;
        }
      else
	tmp = tmp->next;
    }
  return (box);
}

t_token	*token_cmd_concate(t_token *begin)
{
  t_token	*end;
  t_token	*ptr;
  t_token	*new;

  if (begin == NULL || begin->type != WORD)
    return (NULL);
  if ((new = malloc(sizeof(*new))) == NULL)
    return (NULL);
  new->value.str = begin->value.str;
  new->type = begin->type;
  new->value_type = begin->value_type;
  new->next = begin->next;
  begin->value.list = new;
  ptr = new;
  end = ptr;
  while (end && is_cmd(end->type))
    end = end->next;
  begin->next = end;
  while (ptr && ptr->next != end)
    ptr = ptr->next;
  ptr->next = NULL;
  begin->type = CMD;
  begin->value_type = LIST;
  return (begin);
}

int	token_cmd(t_token **list)
{
  t_token	*tmp;

  tmp = *list;
  if (tmp == NULL)
    return (EXIT_FAILURE);
  while (tmp)
    {
      if (tmp->type == WORD)
  	{
  	  if ((tmp = token_cmd_concate(tmp)) == NULL)
  	    return (EXIT_FAILURE);
	  if ((tmp = token_cmd_clean(tmp)) == NULL)
  	    return (EXIT_FAILURE);
  	}
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}
