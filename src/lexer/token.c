
#include	<stdlib.h>
#include	"token.h"

static t_token	*token_new(t_ttype type, char content)
{
  t_token	*new;

  new = NULL;
  if ((new = malloc(sizeof(*new))) == NULL)
    return (NULL);
  new->type = type;
  new->value.str = NULL;
  new->value.define = content;
  new->value_type = DEFINE;
  new->next = NULL;
  return (new);
}

int		token_insert(t_token **list, t_ttype type, char content)
{
  t_token	*new;
  t_token	*iterator;

  if (list == NULL)
    return (EXIT_FAILURE);
  if ((new = token_new(type, content)) == NULL)
    return (EXIT_FAILURE);
  if (*list == NULL)
    *list = new;
  else
    {
      iterator = *list;
      while (iterator && iterator->next != NULL)
	iterator = iterator->next;
      iterator->next = new;
    }
  return (EXIT_SUCCESS);
}
