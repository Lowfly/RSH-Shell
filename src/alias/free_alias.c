
#include <stdlib.h>
#include "alias.h"

void	free_alias(t_alias *list)
{
  if (list)
    {
      if (list->next)
	free_alias(list->next);
      free(list->name);
      free(list->value);
      free(list);
    }
}
