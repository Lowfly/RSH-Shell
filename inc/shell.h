
#ifndef SHELL_H_
# define SHELL_H_

#include "env.h"
typedef struct s_path t_path;
typedef struct s_alias t_alias;
typedef struct s_shell t_shell;
typedef struct s_cmd_list t_cmd_list;
typedef struct s_token t_token;

typedef enum {False, True}	t_bool;

struct s_shell
{
  int		process_group;
  int		fdin;
  int		fdout;
  t_bool	alive;
  int		return_value;
  t_env		*env;
  t_env		*local;
  t_path	*path;
  t_alias	*alias;
  t_cmd_list	*history_last;
  t_cmd_list	*history;
  char		*history_path;
  t_token	*list;
};

int		init_shell(t_shell *, char **);
void		free_env(t_env *);
void		free_path(t_path *);

#endif /* SHELL_H_ */
