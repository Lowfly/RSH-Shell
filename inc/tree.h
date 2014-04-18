
#ifndef TREE_H_
# define TREE_H_

typedef struct s_node	t_node;
typedef struct s_token	t_token;

t_node	*tree_build(t_token *list);
int	tree_free(t_node *tree);

#endif
