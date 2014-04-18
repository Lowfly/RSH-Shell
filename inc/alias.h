#ifndef ALIAS_H_
#define ALIAS_H_

typedef struct s_alias
{
  char		*name;
  char		*value;
  int		bool;
  struct s_alias *next;
} t_alias;

int	b_alias(t_alias **, char **, int);
int	b_unalias(t_alias **, char **, int);
void	free_alias(t_alias *);

#endif /* ALIAS_H_ */
