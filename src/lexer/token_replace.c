
#include <stdlib.h>
#include "lexer.h"
#include "my.h"

int	token_replace_home(t_token **list, t_shell *sh)
{
  t_token	*tmp;
  char		*home;
  char		*replace;

  tmp = *list;
  home = explor_env(sh->env, "HOME");
  while (tmp)
    {
      if (tmp->type == WORD && tmp->value_type == STRING
  	  && tmp->value.str[0] == HOME_C)
  	{
  	  if ((replace = my_concat(home, &(tmp->value.str)[1])) == NULL)
	    return (EXIT_FAILURE);
  	  free(tmp->value.str);
  	  tmp->value.str = replace;
  	}
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}

int	token_replace_exec(t_token **list, t_shell *sh)
{
  t_token	*tmp;
  t_token	*link;
  int		i;

  tmp = *list;
  i = 0;
  link = tmp;
  while (tmp)
    {
      if ((tmp = token_var_replace(tmp, sh)) == NULL)
	return (EXIT_FAILURE);
      if (i == 0)
	*list = tmp;
      else
	link->next = tmp;
      link = tmp;
      tmp = tmp->next;
      i++;
    }
  return (EXIT_SUCCESS);
}

int	token_replace(t_token **list, t_shell *sh)
{
  if (token_replace_exec(list, sh) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (token_replace_home(list, sh) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
