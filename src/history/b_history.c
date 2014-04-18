
#include <stdlib.h>
#include <stdio.h>
#include "history.h"
#include "b_history.h"
#include "shell.h"
#include "token.h"
#include "node.h"
#include "my.h"

int     check_number(t_shell *shell, char **cmd)
{
  if (is_numeric(cmd[0]) == EXIT_FAILURE)
    {
      fprintf(stderr, "rsh: history: %s: numeric argument required\n", cmd[0]);
      return (EXIT_FAILURE);
    }
  if (my_getnbr(cmd[0]) != 0)
    show_history(shell->history_last, size_history(shell->history_last),
                 size_history(shell->history_last) - (my_getnbr(cmd[0]) - 1));
  return (EXIT_FAILURE);
}

int	history_options(t_shell *shell, char **cmd)
{
  if (cmd[0][0] == '-')
    {
      if (my_strcmp(cmd[0], "-c") == 0)
	op_c(shell);
      else if (my_strcmp(cmd[0], "-d") == 0)
	return (op_d(shell, cmd[1]));
      else if (my_strcmp(cmd[0], "--help") == 0)
	return (history_usage());
      else if (my_strcmp(cmd[0], "-s") == 0)
	return (op_s(shell, cmd[1]));
      else if (my_strcmp(cmd[0], "--version") == 0)
	return (history_version());
      else
	{
	  fprintf(stderr, "rsh: history: %s: invalid option\n", cmd[0]);
	  return (-1);
	}
    }
  else
    return (check_number(shell, cmd));
  return (EXIT_FAILURE);
}

int	b_history(t_shell *shell, char **cmd)
{
  if (!cmd[0])
    show_history(shell->history_last, size_history(shell->history_last), 1);
  else
    return (history_options(shell, cmd));
  if (cmd[0])
    free_dtab(cmd - 1, 0);
  return (EXIT_FAILURE);
}
