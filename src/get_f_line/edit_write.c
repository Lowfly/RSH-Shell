
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "edit.h"
#include "cap.h"

int	move_right_write(t_elem *e)
{
  int	total;

  total = taille_cursor(e) + e->taille_prompt;
  if (e->cursor->next)
    {
      my_tputs(e->cap[EI]);
      xwrite(1, &(e->cursor->c), 1);
      e->cursor = e->cursor->next;
      if (!((total) % e->x))
	{
	  my_tputs(e->cap[DO]);
	  my_tputs(e->cap[CR]);
	}
      return (0);
    }
  return (-1);
}

int	last_line(t_elem *e, t_string *tmp)
{
  if (e->ligne == 1)
    {
      move_cursor_prompt(e, tmp);
      deplace_promt(e);
      while (tmp != e->cursor )
	{
	  tmp = tmp->next;
	  my_tputs(e->cap[ND]);
	}
    }
  else
    {
      move_cursor_line(e, tmp);
      while (tmp != e->cursor)
	{
	  tmp = tmp->next;
	  my_tputs(e->cap[ND]);
	}
    }
  return (0);
}

int	move_left_befor(t_elem *e, int i)
{
  int		total;
  t_string	*tmp;

  total = taille_cursor(e) + e->taille_prompt + i;
  tmp = e->s;
  get_nb_line(e);
  if (e->cursor->prev)
    {
      e->cursor = e->cursor->prev;
      if (!((total - 1) % e->x))
	{
	  last_line(e, tmp);
	  my_tputs(e->cap[UP]);
	}
      else
	my_tputs(e->cap[LE]);
      return (0);
    }
  return (-1);
}

int	_bol(t_elem *e, int i)
{
  my_tputs(e->cap[VI]);
  while (move_left_befor(e, i) != -1);
  my_tputs(e->cap[VE]);
  return (0);
}

int	write_all(t_elem *e, int i, int j, int k)
{
  t_string	*save;

  save = e->cursor;
  my_tputs(e->cap[VI]);
  my_tputs(e->cap[EI]);
  _bol(e, i);
  my_tputs(e->cap[VI]);
  while (k--)
    my_tputs(e->cap[ND]);
  while (move_right_write(e) != -1);
  my_tputs(e->cap[CD]);
  _bol(e, j);
  my_tputs(e->cap[VI]);
  e->cursor = e->s;
  while (e->cursor != save)
    move_right(e);
  my_tputs(e->cap[VE]);
  return (0);
}

