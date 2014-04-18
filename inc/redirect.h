
#ifndef REDIRECT_H_
# define REDIRECT_H_

#define FILE_PERMISSION S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
#define	O_FLAGS		O_CREAT | O_WRONLY

typedef struct s_node	t_node;
typedef struct s_shell	t_shell;

int	rec_redirect(t_node *this, t_shell *sh);
int	redirect_right(t_node *this, t_shell *sh);
int	redirect_left(t_node *this, t_shell *sh);
int	redirect_double_right(t_node *this, t_shell *sh);
int	redirect_double_left(t_node *this, t_shell *sh);
t_node	*select_file(t_node *this);
t_node	*select_other(t_node *this, t_node *file);

#endif
