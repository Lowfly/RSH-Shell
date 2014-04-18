
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "edit.h"
#include "prompt.h"
#include "cap.h"

void	move_tmp(t_string *tmp, const t_elem *e)
{
  int	size;

  size = e->x;
  while (size--)
    tmp = tmp->prev;
}

void	move_cursor_line(t_elem *e, t_string *tmp)
{
  int	size;

  size = e->x;
  tmp = e->cursor;
  while (size--)
    tmp = tmp->prev;
}

void	move_cursor_prompt(t_elem *e, t_string *tmp)
{
  int	size;

  size = e->x - e->taille_prompt;
  tmp = e->cursor;
  while (size--)
    tmp = tmp->prev;
}

int	move_left(t_elem *e)
{
  int		total;
  t_string	*tmp;

  total = taille_cursor(e) + e->taille_prompt;
  tmp = e->s;
  get_nb_line(e);
  if (e->cursor->prev)
    {
      e->cursor = e->cursor->prev;
      if (!((total - 1) % e->x))
	{
	  my_tputs(tgetstr("up", NULL));
	  last_line(e, tmp);
	}
      else
	my_tputs(tgetstr("le", NULL));
      return (0);
    }
  return (-1);
}

int	move_right(t_elem *e)
{
  int	total;

  total = taille_cursor(e) + e->taille_prompt;
  if (e->cursor->next)
    {
      e->cursor = e->cursor->next;
      if (!(total % e->x))
	{
	  my_tputs(e->cap[DO]);
	  my_tputs(e->cap[CR]);
	  e->ligne++;
	}
      else
	my_tputs(e->cap[ND]);
      return (0);
    }
  return (-1);
}
