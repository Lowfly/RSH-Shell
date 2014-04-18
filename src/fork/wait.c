
#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	"proc_signal.h"
#include	"token.h"
#include	"node.h"
#include	"shell.h"
#include	"return.h"
#include	"wait.h"

int	wait_node(t_node *this, t_shell *sh)
{
  int	ret;
  int	status;

  if (this == NULL || sh == NULL)
    return (EXIT_FAILURE);
  if (this->pid <= 0)
    return (EXIT_SUCCESS);
  ret = waitpid(this->pid, &status, WUNTRACED | WCONTINUED);
  ret += process_statut(status, &ret);
  sh->return_value = ret;
  set_return(&(sh->local), ret);
  this->pid = 0;
  return (ret);
}

int	wait_piped_node(t_node *this, t_shell *sh)
{
  int	ret;
  int	status;

  if (this == NULL || sh == NULL)
    return (EXIT_FAILURE);
  if (this->pid <= 0)
    return (EXIT_SUCCESS);
  ret = waitpid(this->pid, &status, WUNTRACED | WNOHANG);
  process_statut(status, &ret);
  sh->return_value = ret;
  set_return(&(sh->local), ret);
  this->pid = 0;
  return (ret);
}
