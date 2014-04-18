
#include	<stdlib.h>
#include	"tokeniser.h"
#include	"node.h"
#include	"tree.h"
#include	"exec.h"
#include	"shell.h"
#include	"wait.h"
#include	"logic.h"

int	logic_and(t_node *this, t_shell *sh)
{
  int	ret;

  if (this == NULL || sh == NULL)
    return (EXIT_FAILURE);
  ret = EXIT_SUCCESS;
  if (this->left != NULL)
    {
      ret = exec_tree(this->left, sh);
      ret += wait_node(this->left, sh);
      if (this->left->type == node_or && ret)
	ret = EXIT_SUCCESS;
    }
  if ((ret == EXIT_SUCCESS && this->right != NULL))
    ret += exec_tree(this->right, sh);
  return (ret);
}

int	logic_or(t_node *this, t_shell *sh)
{
  int	ret;

  if (this == NULL || sh == NULL)
    return (EXIT_FAILURE);
  ret = EXIT_FAILURE;
  if (this->left != NULL)
    {
      ret = exec_tree(this->left, sh);
      ret += wait_node(this->left, sh);
    }
  if (ret && this->right != NULL)
    ret += exec_tree(this->right, sh);
  return (ret);
  return (0);
}
