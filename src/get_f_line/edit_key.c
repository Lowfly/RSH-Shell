
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "edit.h"
#include "prompt.h"
#include "cap.h"

int	get_cursor(t_elem *e)
{
  int	total;

  total = taille_cursor(e) + e->taille_prompt - 2;
  return (total / e->x);
}

int	delete(t_elem *e)
{
  t_string	*tmp;

  if (!move_left(e))
    {
      if (e->cursor->prev)
	{
	  e->cursor->prev->next = e->cursor->next;
	  e->cursor->next->prev = e->cursor->prev;
	  tmp = e->cursor;
	  e->cursor = e->cursor->next;
	  free(tmp);
	}
      else if (e->cursor->next)
	{
	  e->cursor = e->cursor->next;
	  e->s = e->cursor;
	  free(e->s->prev);
	  e->s->prev = NULL;
	}
      --e->len;
      write_all(e, 0,  0, 0);
    }
  return (0);
}

void	print_str(t_elem *e)
{
  t_string	*tmp;

  tmp = e->s;
  while (tmp && tmp->next)
    {
      xwrite(1, &(tmp->c), 1);
      tmp = tmp->next;
    }
}

int	clrscr(t_elem *e)
{
  t_string	*tmp;

  tmp = e->s;
  while (tmp->next)
    tmp = tmp->next;
  e->cursor = tmp;
  my_tputs(e->cap[CL]);
  print_prompt(NULL, e->shell->local, 0);
  print_str(e);
  return (0);
}

int	gere_key(char *c, t_elem *e, int (**ptr)())
{
  int	ret;
  int	i;
  char	**idx;
  int	code;

  idx = get_idx();
  ret = 0;
  i = 0;
  code = 0;
  while (i < 13 && code != -3)
    {
      if (!strncmp(idx[i], c, 8))
	{
	  ret = 1;
	  code = ptr[i](e);
	}
      i++;
    }
  free_tab(idx);
  if (code == -3)
    return (-3);
  return (ret);
}
