
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "env.h"
#include "path.h"
#include "b_unsetenv.h"
#include "prompt.h"
#include "my.h"

int	unset_else(t_env *env)
{
  t_env	*to_rm;

  to_rm = env->next;
  free(env->next->name);
  free(env->next->value);
  env->next = to_rm->next;
  free(to_rm);
  print_prompt(NULL, NULL, 1);
  return (0);
}

int	unset_first(t_env **env)
{
  t_env	*first;

  first = *env;
  *env = (*env)->next;
  free(first->name);
  free(first->value);
  free(first);
  print_prompt(NULL, NULL, 1);
  return (0);
}

int	unset_all(t_env **env)
{
  t_env	*tmp;
  t_env	*save;

  tmp = *env;
  *env = NULL;
  while (tmp)
    {
      save = tmp;
      tmp = tmp->next;
      free(save->name);
      free(save->value);
      free(save);
      save = NULL;
    }
  print_prompt(NULL, NULL, 1);
  return (0);
}

int	check_it(t_env **env, char *var)
{
  t_env	*tmp;

  if (strcmp("*", var) == 0)
    return (unset_all(env));
  tmp = *env;
  while (tmp)
    {
      if (tmp->next && my_strcmp(tmp->next->name, var) == 0)
	return (unset_else(tmp));
      else if (my_strcmp(tmp->name, var) == 0)
	return (unset_first(env));
      tmp = tmp->next;
    }
  return (-1);
}

int	b_unsetenv(t_env **env, t_path **path, char **variables, int befree)
{
  int	i;

  i = 0;
  if (!variables || !env || !*env)
    return (-1);
  if (path && (my_strcmp("*", variables[0]) == 0 ||
	       my_strcmp("PATH", variables[0]) == 0))
    {
      free_path(*path);
      *path = NULL;
    }
  while (variables[i])
    if (check_it(env, variables[i++]) == -1)
      {
	if (befree == 1)
	  free_dtab(variables, 1);
	return (EXIT_FAILURE);
      }
  if (befree == 1)
    free_dtab(variables, 1);
  return (EXIT_SUCCESS);
}
