
#include	<stdlib.h>
#include	<unistd.h>
#include	"token.h"
#include	"node.h"
#include	"tree.h"
#include	"shell.h"
#include	"wait.h"
#include	"exec.h"
#include	"job_control.h"
#include	"pipes.h"

static int	pipes_exec(t_node *this, t_shell *sh)
{
  int		newfds[2];
  int		ret;

  ret = EXIT_SUCCESS;
  if (this->right != NULL && this->left != NULL)
    {
      if (pipe(newfds) == -1)
	return (EXIT_FAILURE);
      this->right->in = newfds[0];
      this->right->fdtoclose = newfds[1];
      this->right->out = this->out;
      this->left->in = this->in;
      this->left->out = newfds[1];
      this->left->fdtoclose = newfds[0];
      ret = exec_tree(this->left, sh);
      if (this->right->type != node_pipe)
	ret += exec_tree(this->right, sh);
      else
	ret += pipes_exec(this->right, sh);
      if (this->right->type != node_pipe)
	ret += wait_node(this->right, sh);
      ret += wait_node(this->left, sh);
    }
  return (ret);
}

int	pipes(t_node *this, t_shell *sh)
{
  int	ret;

  if (this == NULL)
    return (EXIT_FAILURE);
  if (this->left != NULL && this->left->pid != -1)
    return (EXIT_SUCCESS);
  ret = pipes_exec(this, sh);
  ret += wait_node(this->left, sh);
  return (ret);
}
