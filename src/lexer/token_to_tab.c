
#include <stdlib.h>
#include "tokeniser.h"
#include "my.h"

int	token_to_tab_len(t_token *begin)
{
  t_token	*ptr;
  int		len;

  ptr = begin;
  len = 0;
  while (ptr)
    {
      if (ptr->value_type != STRING)
	return (-1);
      ptr = ptr->next;
      len++;
    }
  return (len);
}

char	**token_to_tab(t_token *list)
{
  t_token	*root;
  t_token	*ptr;
  char		**tab;
  int		len;
  int		i;

  tab = NULL;
  if (list == NULL)
    return (NULL);
  (list->value_type == LIST) ? (root = list->value.list) : (root = list);
  if ((len = token_to_tab_len(root)) <= 0)
    return (NULL);
  if ((tab = malloc(sizeof(*tab) * (len + 1))) == NULL)
    return (NULL);
  i = 0;
  ptr = root;
  while (ptr)
    {
      tab[i++]= my_strdup(ptr->value.str);
      ptr = ptr->next;
    }
  tab[i] = NULL;
  return (tab);
}
