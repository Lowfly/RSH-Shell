
#include	<stdlib.h>
#include	"token.h"
#include	"node.h"

t_node		*node_new(t_ntype type, t_token *content)
{
  t_node	*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (NULL);
  new->type = type;
  new->content = content;
  new->in = 0;
  new->out = 1;
  new->fdtoclose = -1;
  new->pid = -1;
  new->left = NULL;
  new->right = NULL;
  return (new);
}

t_ntype		node_get_type(t_ttype type)
{
  t_ttype	convert_tab[NODE_TYPE_N];
  int		i;

  if (type == SPACE)
    return (42);
  convert_tab[0] = AND;
  convert_tab[1] = OR;
  convert_tab[2] = PIPE;
  convert_tab[3] = RED_R;
  convert_tab[4] = D_RED_R;
  convert_tab[5] = RED_L;
  convert_tab[6] = D_RED_L;
  convert_tab[7] = WORD;
  convert_tab[8] = FILENAME;
  convert_tab[9] = WORD;
  i = 0;
  while (i < NODE_TYPE_N && convert_tab[i] != type)
    i++;
  if (i >= NODE_TYPE_N)
    return (node_cmd);
  return ((t_ntype) i);
}

int	node_delete(t_node *this)
{
  if (this == NULL)
    return (EXIT_FAILURE);
  free(this);
  return (EXIT_SUCCESS);
}
