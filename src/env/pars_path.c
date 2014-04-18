
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my.h"
#include "env.h"
#include "path.h"

int		put_path_in_list(t_path **path, char *name)
{
  t_path	*elem;

  if ((elem = malloc(sizeof(*elem))) == NULL)
    {
      fprintf(stderr, "malloc fail\n");
      return (EXIT_FAILURE);
    }
  elem->path = my_strdup(name);
  elem->next = *path;
  *path = elem;
  return (EXIT_SUCCESS);
}

t_path		*pars_path(t_env *env)
{
  t_env		*tmp;
  t_path	*path;
  int		i;
  char		**tab_path;

  tmp = env;
  i = -1;
  path = NULL;
  while (tmp != NULL && strcmp(tmp->name, "PATH"))
    tmp = tmp->next;
  if (tmp == NULL)
    return (NULL);
  tab_path = my_str_to_wordtab(tmp->value, ':');
  while (tab_path[++i] != NULL)
    if (put_path_in_list(&path, tab_path[i]) == EXIT_FAILURE)
      return (NULL);
  free_dtab(tab_path, 1);
  return (path);
}
