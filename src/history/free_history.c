
#include <stdlib.h>
#include "history.h"
#include "edit.h"

void	free_string(t_string *list)
{
  if (list)
    {
      if (list->next)
        free_string(list->next);
      free(list);
    }
}

int     del_elem_history(t_cmd_list *tmp)
{
  t_cmd_list    *bef;
  t_cmd_list    *aft;

  free_string(tmp->cmd);
  free(tmp->str);
  bef = tmp->prev;
  aft = tmp->next;
  free(tmp);
  tmp = NULL;
  if (bef)
    bef->next = aft;
  if (aft)
    aft->prev = bef;
  return (EXIT_SUCCESS);
}

void	free_history(t_cmd_list *list)
{
  if (list)
    {
      if (list->next)
        free_history(list->next);
      free_string(list->cmd);
      free(list->str);
      free(list);
    }
}
