
#include	<stdlib.h>
#include	"token.h"
#include	"node.h"
#include	"tree.h"

int             tree_free(t_node *tree)
{
  if (tree == NULL)
    return (EXIT_FAILURE);
  if (tree->left != NULL)
    tree_free(tree->left);
  if (tree->right != NULL)
    tree_free(tree->right);
  free(tree);
  return (EXIT_SUCCESS);
}
