
#include	<stdlib.h>
#include	<unistd.h>
#include	<stdio.h>
#include	"my.h"
#include	"fork.h"
#include	"env.h"
#include	"path.h"
#include	"tokeniser.h"
#include	"parser.h"
#include	"node.h"
#include	"tree.h"
#include	"token_to_tab.h"
#include	"redirect.h"
#include	"shell.h"
#include	"builtins.h"
#include	"pipes.h"
#include	"exec.h"

int		exec_in_path(char **cmd, t_shell *sh, t_node *this)
{
  char		*slash;
  char		*fpath;
  t_path	*path;

  if (cmd == NULL || cmd[0] == NULL || this == NULL || sh == NULL)
    return (EXIT_FAILURE);
  path = sh->path;
  slash = my_concat("/", cmd[0]);
  while (path != NULL)
    {
      fpath = my_concat((path->path), slash);
      if ((access(fpath, X_OK)) == 0)
	{
	  if (fork_ex(fpath, cmd, this, sh))
	      return (-1);
	  free(fpath);
	  free(slash);
	  return (1);
	}
      free(fpath);
      path = path->next;
    }
  free(slash);
  return (0);
}

int	exec_direct(char **cmd, t_node *this, t_shell *sh)
{
  if (cmd == NULL || cmd[0] == NULL || this == NULL || sh == NULL)
    return (EXIT_FAILURE);
  if ((access(cmd[0], X_OK)) == 0)
    {
      if (fork_ex(cmd[0], cmd, this, sh))
	return (-1);
      return (1);
    }
  return (0);
}

int	exec(t_node *this, t_shell *sh, char **cmd)
{
  int	ret;

  if (this == NULL || sh == NULL || sh->alive == False)
    return (EXIT_FAILURE);
  if ((ret = builtins(cmd, sh, this)) == 1)
    return (EXIT_SUCCESS);
  else if (ret == 0 && (ret += exec_direct(cmd, this, sh)) == 1)
    return (EXIT_SUCCESS);
  else if (ret == 0 && (ret += exec_in_path(cmd, sh, this)) == 1)
    return (EXIT_SUCCESS);
  else if (ret == 0)
    {
      fprintf(stderr, "%s: Command not found.\n", cmd[0]);
      return (EXIT_FAILURE);
    }
  if (ret < 0)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int	exec_convert(t_node *this, t_shell *sh)
{
  char	**cmd;
  int	ret;

  if (this == NULL || sh == NULL || this->type != node_cmd)
    return (EXIT_FAILURE);
  if ((cmd = token_convert_cmd(this->content, sh, 0)) == NULL)
    return (EXIT_FAILURE);
  ret = exec(this, sh, cmd);
  free_dtab(cmd, 1);
  exec_close(this);
  return (ret);
}
