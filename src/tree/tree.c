
#include	<stdlib.h>
#include	<stdio.h>
#include	"token.h"
#include	"node.h"
#include	"split.h"
#include	"tree.h"

int		tree_insert(t_node **tree, t_node *new)
{
  if (tree == NULL || new == NULL)
    return (EXIT_FAILURE);
  if (*tree == NULL)
    *tree = new;
  else if ((*tree)->type < new->type &&
	   (*tree)->left == NULL && (*tree)->right == NULL)
    return (tree_insert(&((*tree)->left), new));
  else
    return (tree_insert(&((*tree)->right), new));
  return (EXIT_SUCCESS);
}

static int		get_height(t_ttype type)
{
  if (type == FILENAME)
    return (WORD);
  if (type == OR)
    return (AND);
  return (type);
}

t_token		*tree_get_higher(t_token *list)
{
  t_token	*iterator;

  if (list == NULL)
    return (NULL);
  while (list != NULL && list->type == 42)
    list = list->next;
  iterator = list;
  while (iterator != NULL)
    {
      if (iterator->type == 42)
	while (iterator != NULL && iterator->type == 42)
	  iterator = iterator->next;
      else if ((get_height(list->type) > get_height(iterator->type)
	     && iterator->type != 42)
	       || (get_height(list->type) == AND
		 && get_height(iterator->type) == AND))
	  list = iterator;
      if (iterator != NULL)
	iterator = iterator->next;
    }
  return (list);
}

int		tree_builder(t_node **tree, t_token *list)
{
  t_node	*new;
  t_token	*left;
  t_token	*right;

  if (tree == NULL || list == NULL)
    return (EXIT_FAILURE);
  left = list;
  if ((list = tree_get_higher(list)) == NULL)
    return (EXIT_FAILURE);
  if ((new = node_new(node_get_type(list->type), list)) == NULL)
    return (EXIT_FAILURE);
  *tree = new;
  if (list->next == NULL)
    return (EXIT_SUCCESS);
  if (split(list, &left, &right))
    return (EXIT_SUCCESS);
  tree_builder(&(new->left), left);
  tree_builder(&(new->right), right);
  return (EXIT_SUCCESS);
}

t_node		*tree_build(t_token *list)
{
  t_node	*tree;

  if (list == NULL)
    return (NULL);
  tree = NULL;
  tree_builder(&tree, list);
  return (tree);
}
