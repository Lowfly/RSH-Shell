
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "env.h"

int	separator(char *var)
{
  int	i;

  i = -1;
  while (var[++i] != '\n')
    {
      if (var[i] == '=')
        return (EXIT_SUCCESS);
    }
  return (EXIT_FAILURE);
}

int	control_environ(char **environ)
{
  int	i;

  i = -1;
  while (environ[++i] != NULL)
    if (separator(environ[i]) == EXIT_FAILURE)
      return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

t_env	*basic_env(t_env *env)
{

  return (env);
}
