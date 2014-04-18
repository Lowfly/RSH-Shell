
#ifndef HISTORY_H_
# define HISTORY_H_

#define HISTORY_SUCCESS 0
#define HISTORY_INIT_FAIL 1
#define HISTORY_OPEN_FAIL 2
#define HISTORY_CLOSE_FAIL 3

typedef struct s_string t_string;
typedef struct s_cmd_list t_cmd_list;
typedef struct s_shell t_shell;

struct s_cmd_list
{
  t_string		*cmd;
  char			*str;
  struct s_cmd_list	*next;
  struct s_cmd_list	*prev;
};

void		free_history(t_cmd_list *);
int		show_history(t_cmd_list *, int, int);
int		put_in_history(t_cmd_list **, t_string *, char *);
t_string	*history_convert_str_to_cmd(char *);
int		history_put_in_file(t_cmd_list *, char *);
int		init_history(t_shell *, char *);
int		size_history(t_cmd_list *);

#endif /* HISTORY_H_ */
