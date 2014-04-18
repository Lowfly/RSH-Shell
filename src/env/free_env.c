
#include <stdlib.h>
#include "env.h"
#include "path.h"

void	free_path(t_path *list)
{
  if (list)
    {
      if (list->next)
	free_path(list->next);
      free(list->path);
      free(list);
    }
}

void	free_env(t_env *list)
{
  if (list)
    {
      if (list->next)
	free_env(list->next);
      free(list->name);
      free(list->value);
      free(list);
    }
}

