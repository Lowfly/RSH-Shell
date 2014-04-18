
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "env.h"

t_env	*put_env_in_list(t_env *env, char **environ)
{
  int	i;
  char	*name;
  char	*value;

  i = -1;
  name = NULL;
  value = NULL;
  while (environ[++i] != NULL)
    {
      name = cut_name(environ[i]);
      value = cut_value(environ[i]);
      put_in_env(&env, name, value);
    }
  return (env);
}

int     put_in_env(t_env **env, char *name, char *value)
{
  t_env		*elem;
  t_env		*ptr;

  elem = NULL;
  if ((elem = malloc(sizeof(*elem))) == NULL)
    {
      fprintf(stderr, "Failed while trying to allocate memory.\n");
      return (EXIT_FAILURE);
    }
  elem->name = name;
  elem->value = value;
  elem->next = NULL;
  if (*env)
    {
      ptr = *env;
      while (ptr->next)
        ptr = ptr->next;
      ptr->next = elem;
    }
  else
    *env = elem;
  return (EXIT_SUCCESS);
}

t_env	*init_env(char **environ)
{
  t_env	*env;

  env = NULL;
  if (environ == NULL || environ[0] == NULL)
    return (NULL);
  else if (control_environ(environ) == EXIT_FAILURE)
    return (NULL);
  if ((env = put_env_in_list(env, environ)) == NULL)
    return (NULL);
  return (env);
}
