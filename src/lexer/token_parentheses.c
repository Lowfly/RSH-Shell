
#include <stdlib.h>
#include "lexer.h"
#include "token.h"
#include "my.h"

t_token		*token_find_closing_pc(t_token *current)
{
  t_token	*tmp;
  int		count_po;

  count_po = 0;
  tmp = current;
  if (current == NULL)
    return (NULL);
  while (tmp && (tmp->type != PC || count_po))
    {
      if (tmp->type == PO)
	count_po += 1;
      else if (tmp->type == PC)
	count_po -= 1;
      tmp = tmp->next;
    }
  return (tmp);
}

t_token		*token_group_parentheses(t_token *begin, t_token *end)
{
  t_token	*ptr;

  if (begin == NULL || end == NULL || begin->next == NULL)
    return (NULL);
  ptr = begin->next;
  begin->next = end->next;
  (ptr != end) ? (begin->value.list = ptr) : (begin->value.list = NULL);
  while (ptr && ptr->next != end)
    ptr = ptr->next;
  if (ptr)
    ptr->next = NULL;
  begin->value_type = LIST;
  token_delete(end);
  return (begin);
}

int	token_parentheses(t_token **list)
{
  t_token	*tmp;
  t_token	*end;

  tmp = *list;
  if (tmp == NULL)
    return (EXIT_FAILURE);
  while (tmp)
    {
      if (tmp->type == PO)
  	{
  	  if ((end = token_find_closing_pc(tmp->next)) == NULL)
  	    return (lexer_err(TOO_MANY, PO));
  	  if ((tmp = token_group_parentheses(tmp, end)) == NULL)
  	    return (EXIT_FAILURE);
  	}
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}
