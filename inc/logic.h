
#ifndef LOGIC_H_
# define LOGIC_H_

typedef struct s_node	t_node;
typedef struct s_shell	t_shell;

int	logic_and(t_node *this, t_shell *sh);
int	logic_or(t_node *this, t_shell *sh);

#endif
