
#include <stdlib.h>
#include "lexer.h"
#include "token.h"
#include "my.h"

t_token	*token_group_find_pair(t_token *current, t_ttype define)
{
  t_token	*tmp;

  tmp = current;
  if (current == NULL)
    return (NULL);
  while (tmp && tmp->type != define)
    tmp = tmp->next;
  return (tmp);
}

t_token	*token_group_concate(t_token *begin, t_token *end, t_ttype define)
{
  t_token	*ptr;

  if (begin == NULL || end == NULL || begin->next == NULL)
    return (NULL);
  else if (begin->type != define || end->type != define)
    return (NULL);
  ptr = begin->next;
  begin->next = end->next;
  (ptr != end) ? (begin->value.list = ptr) : (begin->value.list = NULL);
  while (ptr && ptr != end && ptr->next != end)
    ptr = ptr->next;
  if (ptr)
    ptr->next = NULL;
  begin->value_type = LIST;
  token_delete(end);
  return (begin);
}

int	token_group_by_type(t_token **list, t_ttype define)
{
  t_token	*tmp;
  t_token	*end;

  tmp = *list;
  if (tmp == NULL)
    return (EXIT_FAILURE);
  while (tmp)
    {
      if (tmp->type == define)
  	{
  	  if ((end = token_group_find_pair(tmp->next, define)) == NULL)
  	    return (lexer_err(UNMATCHED, define));
  	  if ((tmp = token_group_concate(tmp, end, define)) == NULL)
  	    return (EXIT_FAILURE);
  	}
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}
