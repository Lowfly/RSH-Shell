
#include	<stdlib.h>
#include	<unistd.h>
#include	"tokeniser.h"
#include	"node.h"
#include	"tree.h"
#include	"redirect.h"
#include	"pipes.h"
#include	"backquote.h"
#include	"shell.h"
#include	"logic.h"
#include	"reset_fd.h"
#include	"wait.h"
#include	"exec.h"

static int	exec_simple_node(t_node *tree, t_shell *sh)
{
  int		ret;

  ret = exec_convert(tree, sh);
  if (tree->fdtoclose == -1)
    ret += wait_node(tree, sh);
  exec_close(tree);
  return (ret);
}

static void	init_tab(t_ntype types[], int (*func[])(t_node *, t_shell *))
{
  types[0] = node_cmd;
  types[1] = node_redirect_r;
  types[2] = node_redirect_dr;
  types[3] = node_redirect_l;
  types[4] = node_redirect_dl;
  types[5] = node_pipe;
  types[6] = node_backquote;
  types[7] = node_and;
  types[8] = node_or;
  func[0] = &exec_simple_node;
  func[1] = &redirect_right;
  func[2] = &redirect_double_right;
  func[3] = &redirect_left;
  func[4] = &redirect_double_left;
  func[5] = &pipes;
  func[6] = &backquote;
  func[7] = &logic_and;
  func[8] = &logic_or;
}

int	exec_close(t_node *tree)
{
  if (tree->in != 0)
    close(tree->in);
  if (tree->out != 1)
    close(tree->out);
  return (EXIT_SUCCESS);
}

int	exec_node(t_node *tree, t_shell *sh)
{
  t_ntype	types[EXEC_FUNC_N];
  int		(*func[EXEC_FUNC_N])(t_node *, t_shell *);
  int		i;

  if (tree->type == node_filename)
    return (exec_close(tree));
  init_tab(types, func);
  exec_convert(NULL, sh);
  i = 0;
  while (i < EXEC_FUNC_N)
    {
      if (tree->type == types[i])
	return (func[i](tree, sh));
      i++;
    }
  return (EXIT_FAILURE);
}

int		exec_tree(t_node *tree, t_shell *sh)
{
  int		ret;

  if (tree == NULL || sh == NULL || tree->pid != -1)
    return (EXIT_SUCCESS);
  reset_fd_save(sh);
  ret = exec_node(tree, sh);
  if (tree->type >= node_redirect_r && tree->type <= node_redirect_dl)
    {
      if (tree->left != NULL && tree->left->pid == -1)
	ret += exec_node(tree->left, sh);
      if (tree->right != NULL && tree->right->pid == -1)
	ret += exec_node(tree->right, sh);
    }
  exec_close(tree);
  reset_fd_restore(sh);
  if (ret)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
