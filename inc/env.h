
#ifndef ENV_H_
#define ENV_H_

typedef struct	s_env
{
  char		*name;
  char		*value;
  struct s_env	*next;
} t_env;

t_env	*init_env(char **);
t_env	*put_env_in_list(t_env *, char **);
int     put_in_env(t_env **, char *, char *);
int     put_in_rev_env(t_env **, char *, char *);
int     env_printenv(t_env *);
char	*cut_name(char *);
char	*cut_value(char *);
int	control_environ(char **);
t_env	*basic_env(t_env *);
char	*explor_env(t_env *, char *);
t_env	*find_in_env(t_env *, char *);

#endif /* ENV_H_ */
