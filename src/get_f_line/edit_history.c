
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
#include "cap.h"
#include "my.h"

int	up(t_elem *e)
{
  t_string	*tmp;

  if (e && e->shell && e->shell->history)
    {
      rm_line(e);
      e->s = dup_str(e->shell->history->cmd);
      tmp = e->s;
      while (tmp->next)
	tmp = tmp->next;
      e->cursor = tmp;
      print_str(e);
      if (e->shell->history->next)
	e->shell->history = e->shell->history->next;
    }
  return (0);
}

int	down(t_elem *e)
{
  t_string	*tmp;

  if (e && e->shell && e->shell->history && e->shell->history->cmd)
    {
      rm_line(e);
      e->s = dup_str(e->shell->history->cmd);
      tmp = e->s;
      while (tmp && tmp->next)
	tmp = tmp->next;
      e->cursor = tmp;
      print_str(e);
      if (e->shell->history->prev)
	e->shell->history = e->shell->history->prev;
    }
  return (0);
}
