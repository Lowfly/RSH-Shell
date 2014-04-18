
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glob.h>
#include <sys/ioctl.h>
#include "edit.h"
#include "history.h"
#include "prompt.h"
#include "my.h"

t_string	*string_dup(t_elem *e)
{
  t_string	*copy;

  copy = e->cursor;
  while (e->cursor->next)
    {
      my_put_in_clip(e, e->cursor->c);
      e->cursor = e->cursor->next;
    }
  e->cursor = copy;
  return (copy);
}

int	free_my_string(t_string *s)
{
  if (s->next)
    free_my_string(s->next);
  free(s);
  return (0);
}

int		dup_add(t_string **e, int c)
{
  t_string	*elem;

  elem = malloc(sizeof(t_string));
  elem->next = NULL;
  elem->prev = NULL;
  elem->c = c;
  if (e && *e)
    {
      elem->next = *e;
      (*e)->prev = elem;
    }
  *e = elem;
  return (0);
}

t_string	*dup_str(t_string *e)
{
  t_string	*ret;

  if (e == NULL)
    return (NULL);
  ret = NULL;
  while (e->next)
    e = e->next;
  while (e->prev)
    {
      dup_add(&ret, e->c);
      e = e->prev;
    }
  dup_add(&ret, e->c);
  return (ret);
}
