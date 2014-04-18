
#ifndef EXEC_H_
# define EXEC_H_

#define	EXEC_FUNC_N	9

typedef struct s_env		t_env;
typedef struct s_path		t_path;
typedef struct s_shell		t_shell;
typedef struct s_parsedline	t_parsedline;
typedef struct s_node		t_node;

int	exec_in_path(char **cmd, t_shell *sh, t_node *this);
int	exec_direct(char **cmd, t_node *this, t_shell *sh);
int	exec_tree(t_node *tree, t_shell *sh);
int	exec_convert(t_node *this, t_shell *sh);
int	exec_close(t_node *tree);
int	exec(t_node *this, t_shell *sh, char **cmd);

#endif
