
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "edit.h"

int	xwrite(int fd, char *s, unsigned int len)
{
  int	ret;

  ret = write(fd, s, len);
  return (ret);
}

int	add_cursor(t_elem *e)
{
  t_string	*elem;

  if (!(elem = malloc(sizeof(t_string))))
    return (-1);
  e->s = elem;
  elem->c = 0;
  elem->next = NULL;
  elem->prev = NULL;
  return (0);
}

void	swap(t_elem *e, t_string *elem, t_string *cpy)
{
  elem->next = e->s;
  elem->prev = e->s->prev;
  elem->next->prev = elem;
  if (elem->prev)
    {
      elem->prev->next = elem;
      e->s = cpy;
    }
  else
    e->s = elem;
  e->cursor = elem->next;
}

int	first(t_elem *e, t_string *elem, int rewrite, char c)
{
   if (!e->s->next)
    {
      elem->next = e->s;
      e->s->prev = elem;
      e->s = elem;
      if (rewrite)
	xwrite(1, &c, 1);
      return (1);
    }
   return (0);
}

int	push_char(t_elem *e, char c, int rewrite)
{
  t_string	*elem;
  t_string	*cpy;

  if (e->len > 1500)
    return (0);
  e->len++;
  cpy = e->s;
  my_tputs(tgetstr("in", NULL));
  if (!(elem = malloc(sizeof(t_string))))
    return (-1);
  elem->c = c;
  elem->next = NULL;
  elem->prev = NULL;
  if (first(e, elem, rewrite, c))
    return (0);
  while ((e->s) != e->cursor)
    e->s = e->s->next;
  swap(e, elem, cpy);
  if (rewrite)
    write_all(e, -1, 0, 1);
  return (0);
}
