
#include <stdlib.h>
#include "edit.h"
#include "cap.h"

int		my_put_in_clip(t_elem *e, char c)
{
  t_string	*elem;
  t_string	*cpy;

  cpy = e->clipboard;
  if (!(elem = malloc(sizeof(t_elem))))
    return (-1);
  elem->prev = NULL;
  elem->next = NULL;
  elem->c = c;
  if (e->clipboard == NULL)
    {
      e->clipboard = elem;
      return (0);
    }
  while (e->clipboard->next)
    e->clipboard = e->clipboard->next;
  e->clipboard->next = elem;
  elem->prev = e->clipboard;
  e->clipboard = cpy;
  return (0);
}

int	taille_clip(t_elem *e)
{
  int		i;
  t_string	*cpy;

  i = 0;
  cpy = e->clipboard;
  while (cpy)
    {
      i++;
      cpy = cpy->next;
    }
  return (i);
}

int	past(t_elem *e, t_string *cpy, t_string *save)
{
  if (e->clipboard)
    {
      while (cpy)
	{
	  my_tputs(e->cap[VI]);
	  push_char(e, cpy->c, 0);
	  cpy = cpy->next;
	}
      e->cursor = e->s;
      my_tputs(e->cap[VI]);
      while (move_right_write(e) != -1);
      my_tputs(e->cap[VI]);
      _bol(e, 0);
      my_tputs(e->cap[VI]);
      while (e->cursor != save)
	move_right(e);
    }
  return (0);
}

int	ctrl_y(t_elem *e)
{
  t_string	*cpy;
  t_string	*save;

  if (taille_clip(e) < 1)
    return (0);
  save = e->cursor;
  cpy = e->clipboard;
  my_tputs(e->cap[VI]);
  _bol(e, 0);
  while (e->cursor != save)
    e->cursor = e->cursor->next;
  past(e, cpy, save);
  my_tputs(e->cap[VE]);
  return (0);
}

int	ctrl_k(t_elem *e)
{
  free_string_edit(e->clipboard);
  e->clipboard = NULL;
  string_dup(e);
  my_tputs(e->cap[CD]);
  if (e->cursor->next)
    free_end_of_clip(e->cursor->next);
  e->cursor->c = 0;
  e->cursor->next = NULL;
  e->len -= taille_clip(e);
  return (0);
}
