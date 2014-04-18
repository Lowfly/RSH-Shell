
#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#include "b_unsetenv.h"
#include "shell.h"
#include "token.h"
#include "node.h"
#include "b_env.h"

int     no_option(t_env **env, char c)
{
  t_env *tmp;

  tmp = *env;
  while (tmp)
    {
      printf("%s=%s%c", tmp->name, tmp->value, c);
      tmp = tmp->next;
    }
  if (c == 0 && *env)
    printf("\n");
  return (EXIT_SUCCESS);
}

int     op_i(t_env **env, char **args, int i[2])
{
  char  *var[2];

  var[0] = "*";
  var[1] = NULL;
  b_unsetenv(env, NULL, var, 0);
  if (!args[i[0] + 1])
    no_option(env, '\n');
  return (EXIT_SUCCESS);
}

int     op_0(t_env **env, char **args, int i[2])
{
  if (!args[i[0] + 1])
    no_option(env, 0);
  return (EXIT_SUCCESS);
}

int     op_u(t_env **env, char **args, int i[2])
{
  char  *var[2];

  i[0]++;
  if (!args[i[0]] || !args[i[0]][0])
    {
      fprintf(stderr, "%s%s", NEEDS_ARG1, NEEDS_ARG2);
      return (EXIT_FAILURE);
    }
  var[0] = args[i[0]];
  var[1] = NULL;
  b_unsetenv(env, NULL, var, 0);
  if (!args[i[0] + 1])
    no_option(env, '\n');
  return (EXIT_SUCCESS);
}
