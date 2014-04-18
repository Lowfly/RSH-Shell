
#ifndef NODE_H_
# define NODE_H_

#define	NODE_TYPE_N	10

typedef struct s_token	t_token;

typedef enum {node_and,
	      node_or,
	      node_pipe,
      	      node_redirect_r,
      	      node_redirect_dr,
      	      node_redirect_l,
      	      node_redirect_dl,
	      node_backquote,
	      node_filename,
	      node_cmd}	t_ntype;

typedef struct s_node
{
  t_ntype	type;
  t_token	*content;
  int		in;
  int		out;
  int		fdtoclose;
  int		pid;
  struct s_node	*left;
  struct s_node	*right;
}	t_node;

t_node	*node_new(t_ntype type, t_token *content);
t_ntype	node_get_type(t_ttype type);
int	node_delete(t_node *this);

#endif
