
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "tokeniser.h"
#include "alias.h"
#include "my.h"

int	token_alias_init(t_alias *list)
{
  t_alias	*tmp;

  tmp = list;
  while (tmp)
    {
      tmp->bool = 0;
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}

char		*token_alias_search(char *search, int *stop, t_alias *alias)
{
  t_alias	*tmp;
  char		*find;

  find = NULL;
  tmp = alias;
  while (tmp)
    {
      if (my_strcmp(search, tmp->name) == 0)
	{
	  if (tmp->bool == 1)
	    {
	      fprintf(stderr, "Warning: alias loop\n");
	      *stop = 0;
	      return (NULL);
	    }
	  find = tmp->value;
	  tmp->bool = 1;
	  return (find);
	}
      tmp = tmp->next;
    }
  return (NULL);
}

char	*token_alias_explore(char *search, int *stop, t_alias *alias)
{
  char	*replace;
  char	*save_result;
  int	i;

  i = 1;
  replace = NULL;
  save_result = replace;
  while (i || (replace && (*stop)))
    {
      replace = token_alias_search(search, stop, alias);
      if (replace)
	{
	  save_result = replace;
	  search = replace;
	}
      i = 0;
    }
  return (save_result);
}

char		**token_alias_rebuild(char *replace, char **cmd)
{
  char	**new;
  char	**tab;
  int	len;
  int	i;

  i = 0;
  if ((tab = my_str_to_wordtab(replace, ' ')) == NULL)
    return (NULL);
  len = tab_len(tab) + tab_len(cmd) + 1;
  if ((new = malloc(sizeof(*new) * len)) == NULL)
    return (NULL);
  len = 0;
  while (tab[i])
    new[len++] = tab[i++];
  i = 1;
  while (cmd[i])
    new[len++] = cmd[i++];
  new[len] = NULL;
  free(tab);
  free(cmd);
  return (new);
}

char		**token_alias_replace(char **cmd, t_shell *sh)
{
  char		*replace;
  int		stop;

  stop = 1;
  if (cmd && cmd[0] &&
      my_strcmp("alias", cmd[0]) && my_strcmp("unalias", cmd[0]))
    {
      token_alias_init(sh->alias);
      if ((replace = token_alias_explore(cmd[0], &stop, sh->alias)) == NULL)
	return (cmd);
      if ((cmd = token_alias_rebuild(replace, cmd)) == NULL)
	return (NULL);
    }
  return (cmd);
}
