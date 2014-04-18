
#ifndef PATH_H_
#define PATH_H_

#include "env.h"

typedef struct	s_path
{
  char		*path;
  struct s_path	*next;
} t_path;

t_path	*pars_path(t_env *env);
void	free_path(t_path *);

#endif /* PATH_H_ */
