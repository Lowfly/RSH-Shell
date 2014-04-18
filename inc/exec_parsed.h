
#ifndef EXEC_PARSED_H_
# define EXEC_PARSED_H_

typedef struct s_parsedline	t_parsedline;
typedef struct s_shell		t_shell;

int	exec_parsed(t_parsedline *exec, t_shell *sh);
int	exec_parsed_free(t_parsedline *exec);

#endif
