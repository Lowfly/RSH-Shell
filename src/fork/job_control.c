
#include	<stdlib.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	"shell.h"
#include	"job_control.h"

int	job_change_group(int pid, t_shell *sh)
{
  if (pid <= 0 || sh == NULL)
    return (EXIT_FAILURE);
  if (sh->process_group == 0)
    {
      if (setpgid(pid, 0) == -1)
        return (EXIT_FAILURE);
      if ((sh->process_group = getpgid(pid)) == -1)
        return (EXIT_FAILURE);
    }
  else
    {
      if (setpgid(pid, sh->process_group) == -1)
        return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
