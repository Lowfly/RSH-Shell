/*
** builtins.h for 42sh in /home/roche_d//projets/42sh-2017-creach_a
**
** Made by clement roche
** Login   <roche_d@epitech.net>
**
** Started on  Fri Apr 26 14:36:09 2013 clement roche
** Last update Sun May 26 11:36:20 2013 alexandre paillier
*/

#ifndef BUILTINS_H_
# define BUILTINS_H_

# include	"b_env.h"
# include	"b_unsetenv.h"
# include	"b_setenv.h"
# include	"b_history.h"

typedef struct s_shell	t_shell;
typedef struct s_node	t_node;

int	builtins(char **, t_shell *, t_node *);
int	my_exit(char **, t_shell *);
int	return_value(t_shell *);
int	is_builtins(char *);

#endif
