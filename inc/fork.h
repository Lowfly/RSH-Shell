
#ifndef FORK_H_
# define FORK_H_

typedef struct s_node	t_node;
typedef struct s_shell	t_shell;

int	fork_ex(char *bin, char **argv, t_node *this, t_shell *sh);
void	fork_dup(t_node *);
char    **gen_env(t_shell *shell);

#endif
