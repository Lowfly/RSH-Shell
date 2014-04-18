
#include	<stdlib.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	<stdio.h>
#include	"my.h"
#include	"proc_signal.h"
#include	"token.h"
#include	"node.h"
#include	"shell.h"
#include	"job_control.h"
#include	"fd_check.h"
#include	"fork.h"

int		fork_ex_stat(char *bin)
{
  t_fdtype	type;

  if ((type = fd_check_type(bin)) != REG)
    {
      if (type == DIR)
	fprintf(stderr, "%s: Command not found.\n", bin);
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

static void	fork_close(t_node *this)
{
  if (this->fdtoclose != -1)
    close(this->fdtoclose);
  this->fdtoclose = -1;
}

void	fork_dup(t_node *this)
{
  if (this->in != 0)
    dup2(this->in, 0);
  if (this->out != 1)
    dup2(this->out, 1);
}

static void	set_signal(void)
{
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);
}

int	fork_ex(char *bin, char **argv, t_node *this, t_shell *sh)
{
  int	pid;
  char	**environ;

  if (bin == NULL || argv == NULL || this == NULL || sh == NULL)
    return (EXIT_FAILURE);
  if (fork_ex_stat(bin) || (environ = gen_env(sh)) == NULL)
    return (EXIT_SUCCESS);
  if ((pid = fork()) == -1)
    return (EXIT_FAILURE);
  set_signal();
  if (pid == 0)
    {
      fork_close(this);
      fork_dup(this);
      if (execve(bin, argv, environ))
	return (EXIT_FAILURE);
    }
  else
    {
      this->pid = pid;
      job_change_group(pid, sh);
      tcsetpgrp(0, sh->process_group);
    }
  free_dtab(environ, 1);
  return (EXIT_SUCCESS);
}
