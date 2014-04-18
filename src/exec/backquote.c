
#include	<stdlib.h>
#include	<unistd.h>
#include	"token.h"
#include	"tokeniser.h"
#include	"node.h"
#include	"tree.h"
#include	"token_to_tab.h"
#include	"exec.h"
#include	"backquote.h"

int		backquote(t_node *this, t_shell *sh)
{
  int		newfds[2];
  t_node	*tree;
  t_token	*iterator;

  if (this == NULL)
    return (EXIT_FAILURE);
  if (token_secondary(&(this->content->value.list)))
    return (EXIT_FAILURE);
  iterator = this->content->value.list;
  if (pipe(newfds) == -1)
    return (EXIT_FAILURE);
  dup2(1, newfds[1]);
  dup2(0, newfds[0]);
  while (iterator != NULL)
    {
      if ((tree = tree_build(this->content->value.list->value.list)) == NULL)
	return (EXIT_FAILURE);
      exec_tree(tree, sh);
      tree_free(tree);
      iterator = iterator->next;
    }
  return (EXIT_SUCCESS);
}
