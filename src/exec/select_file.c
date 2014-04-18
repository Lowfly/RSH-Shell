
#include	<stdlib.h>
#include	"token.h"
#include	"node.h"
#include	"redirect.h"

static t_node	*find_next_file(t_node *this)
{
  t_node	*next;

  if (this != NULL && this->type == node_filename)
    return (this);
  if (this->left != NULL && ((next = find_next_file(this->left)) != NULL))
    return (next);
  if (this->right != NULL && ((next = find_next_file(this->right)) != NULL))
    return (next);
  return (NULL);
}

t_node	*select_file(t_node *this)
{
  if (this == NULL)
    return (NULL);
  if (this->right != NULL)
    {
      if (this->right->type == node_filename)
	return (this->right);
    }
  return (find_next_file(this));
  return (NULL);
}

t_node		*select_other(t_node *this, t_node *file)
{
  t_node	*other;

  if (this == NULL)
    return (NULL);
  if (this != file && this->type != node_filename
      && this->pid == -1)
    return (this);
  if (this->type == node_cmd)
    return (this);
  if ((other = select_other(this->right, file)) != NULL)
    return (other);
  if ((other = select_other(this->left, file)) != NULL)
    return (other);
    return (NULL);
}
