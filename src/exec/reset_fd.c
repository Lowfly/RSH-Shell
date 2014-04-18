
#include	<stdlib.h>
#include	<unistd.h>
#include	"shell.h"
#include	"reset_fd.h"

int	reset_fd_save(t_shell *sh)
{
  if (sh == NULL)
    return (EXIT_FAILURE);
  if (sh->fdin != -1 && sh->fdout != -1)
    return (EXIT_SUCCESS);
  sh->fdin = dup(0);
  sh->fdout = dup(1);
  return (EXIT_SUCCESS);
}

int	reset_fd_restore(t_shell *sh)
{
  if (sh == NULL)
    return (EXIT_FAILURE);
  dup2(sh->fdin, 0);
  dup2(sh->fdout, 1);
  return (EXIT_SUCCESS);
}
