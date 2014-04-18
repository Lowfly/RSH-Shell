
#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#include "shell.h"
#include "token.h"
#include "node.h"
#include "builtins.h"
#include "b_env.h"
#include "my.h"

int	check_equal(char *arg)
{
  int	i;

  i = 0;
  while (arg[i])
    {
      if (arg[i] == '=')
	return (EXIT_SUCCESS);
      i++;
    }
  return (EXIT_FAILURE);
}

int	extract_and_setenv(char *arg, t_env **env)
{
  int	i;
  char	*namevalue[3];

  i = 0;
  namevalue[2] = NULL;
  while (arg[i] && arg[i] != '=')
    i++;
  if ((namevalue[0] = my_strndup(arg, i)) == NULL)
    return (EXIT_FAILURE);
  if ((namevalue[1] = my_strdup(arg + i + 1)) == NULL)
    return (EXIT_FAILURE);
  if (b_setenv(env, NULL, namevalue, 0) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  free_dtab(namevalue, 0);
  return (EXIT_SUCCESS);
}

int	check_less_0(char **args)
{
  int	i;

  i = 0;
  while (args[i])
    {
      if (my_strcmp(args[i], "-0") == 0)
	return (EXIT_SUCCESS);
      i++;
    }
  return (EXIT_FAILURE);
}

int	check_name_value(t_benv *benv, t_shell *shell)
{
  if (!benv->args[benv->i[0]] || check_equal(benv->args[benv->i[0]]) != 0)
    return (EXIT_SUCCESS);
  while (benv->args[benv->i[0]] && check_equal(benv->args[benv->i[0]]) == 0)
    {
      if (extract_and_setenv(benv->args[benv->i[0]], &shell->env) == 1)
	return (EXIT_FAILURE);
      benv->i[0]++;
    }
  if (!benv->args[benv->i[0]])
    {
      if (check_less_0(benv->args) == EXIT_SUCCESS)
	no_option(&shell->env, 0);
      else
	no_option(&shell->env, '\n');
      return (3);
    }
  return (EXIT_SUCCESS);
}
