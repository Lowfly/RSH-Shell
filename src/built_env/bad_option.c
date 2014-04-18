
#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#include "shell.h"
#include "token.h"
#include "node.h"
#include "b_env.h"
#include "builtins.h"
#include "my.h"

int	check_tricky_options(char **args, int i[2], t_env **env)
{
  char	*tab[3];
  int	y[2];

  if (my_strncmp("--unset=", args[i[0]], 8) == 0)
    {
      tab[0] = args[i[0]] + 8;
      tab[1] = args[i[0] + 1];
      tab[2] = NULL;
      y[0] = -1;
      y[1] = 0;
      op_u(env, tab, y);
      return (EXIT_SUCCESS);
    }
  return (EXIT_FAILURE);
}

void	unrecognized_op(char *str)
{
  fprintf(stderr, UNRECOG_OP1, str);
  fprintf(stderr, UNRECOG_OP2);
}

void	invalid_op(char *str)
{
  fprintf(stderr, INVALID_OP1, str);
  fprintf(stderr, INVALID_OP2);
}

int     bad_option(char **args, int i[2], t_env **env)
{
  if (check_tricky_options(args, i, env) == EXIT_SUCCESS)
    return (EXIT_SUCCESS);
  if ((my_strlen(args[i[0]]) >= 3) && args[i[0]][1] == '-')
    unrecognized_op(args[i[0]] + 2);
  else if ((my_strlen(args[i[0]]) == 2) && args[i[0]][1] == '-')
    {
      if (!args[i[0] + 1])
        no_option(env, '\n');
      return (EXIT_FAILURE);
    }
  else
    if (my_strlen(args[i[0]]) > 1)
      invalid_op(args[i[0]] + 1);
    else
      {
        op_i(env, args, i);
        return (EXIT_FAILURE);
      }
  i[0]++;
  return (EXIT_FAILURE);
}
