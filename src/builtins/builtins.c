
#include	<stdlib.h>
#include	<stdio.h>
#include	"my.h"
#include	"alias.h"
#include	"shell.h"
#include	"token.h"
#include	"node.h"
#include	"b_setenv.h"
#include	"b_echo.h"
#include	"builtins.h"
#include	"fork.h"
#include	"cd.h"

int	my_exit(char **cmd, t_shell *sh)
{
  sh->alive = False;
  if (cmd[1] != NULL)
    {
      if (is_numeric(cmd[1]))
	sh->return_value = my_getnbr(cmd[1]);
      else
	{
	  fprintf(stderr, "exit error: %s is not a number.\n", cmd[1]);
	  sh->alive = True;
	}
    }
  return (EXIT_SUCCESS);
}

int	return_value(t_shell *sh)
{
  printf("last exit process statut:%d.\n", sh->return_value);
  return (EXIT_SUCCESS);
}

static int	builtins_duped(char **cmd, t_shell *shell, t_node *tree)
{
  if (my_strcmp(cmd[0], "env") == 0)
    {
      fork_dup(tree);
      return (b_env(shell, cmd + 1, tree));
    }
  else if (my_strcmp(cmd[0], "echo") == 0)
    {
      fork_dup(tree);
      b_echo(cmd);
    }
  else if (my_strcmp(cmd[0], "history") == 0)
    {
      fork_dup(tree);
      return (b_history(shell, cmd + 1));
    }
  else
    return (EXIT_SUCCESS);
  return (EXIT_FAILURE);
}

int	builtins(char **cmd, t_shell *shell, t_node *tree)
{
  if (cmd == NULL || shell == NULL || tree == NULL)
    return (EXIT_FAILURE);
  if (my_strcmp(cmd[0], "exit") == 0)
    my_exit(cmd, shell);
  else if (my_strcmp(cmd[0], "return_value") == 0)
    return_value(shell);
  else if (my_strcmp(cmd[0], "unsetenv") == 0)
    b_unsetenv(&(shell->env), &(shell->path), cmd + 1, 0);
  else if (my_strcmp(cmd[0], "setenv") == 0)
    b_setenv(&(shell->env), &(shell->path), cmd + 1, 0);
  else if (my_strcmp(cmd[0], "unset") == 0)
    b_unsetenv(&(shell->local), &(shell->path), cmd + 1, 0);
  else if (my_strcmp(cmd[0], "set") == 0)
    b_setenv(&(shell->local), &(shell->path), cmd + 1, 0);
  else if (my_strcmp(cmd[0], "alias") == 0)
    b_alias(&(shell->alias), cmd + 1, 0);
  else if (my_strcmp(cmd[0], "unalias") == 0)
    b_unalias(&(shell->alias), cmd + 1, 0);
  else if (my_strcmp(cmd[0], "cd") == 0)
    return (cd_change_dir(cmd[1], shell->env));
  else
    return (builtins_duped(cmd, shell, tree));
  return (EXIT_FAILURE);
}
