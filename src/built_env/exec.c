
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "token.h"
#include "node.h"
#include "b_env.h"
#include "exec.h"
#include "path.h"
#include "my.h"

int     execution(t_shell *shell, t_node *node, char **args)
{
  if (!args || !args[0])
    return (-1);
  exec(node, shell, args);
  return (EXIT_SUCCESS);
}

int     prepare_exec(int ret, t_benv *benv, t_shell *shell, t_node *node)
{
  int	ret_null;

  if (ret != 3 && (ret_null = check_null(benv->args)) == EXIT_SUCCESS)
    execution(shell, node, &benv->args[benv->i[0]]);
  if (ret_null == EXIT_FAILURE)
    return (EXIT_FAILURE);
  else if (my_strcmp(benv->args[benv->i[0]], "-") == 0)
    {
      if (benv->args[benv->i[0] + 1])
        execution(shell, node, &benv->args[benv->i[0] + 1]);
    }
  else if (benv->i[0] > 0 && my_strcmp(benv->args[benv->i[0] - 1], "--") == 0)
    execution(shell, node, &benv->args[benv->i[0]]);
  else if (my_strcmp(benv->args[benv->i[0]], "--") == 0)
    execution(shell, node, &benv->args[benv->i[0] + 1]);
  return (EXIT_SUCCESS);
}
