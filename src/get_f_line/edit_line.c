
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "edit.h"
#include "prompt.h"
#include "cap.h"

int	get_nb_line(t_elem *e)
{
  int	total;

  total = taille_cursor(e) + e->taille_prompt;
  e->ligne = total / e->x;
  return (0);
}

int	taille_cursor(t_elem *e)
{
  int		ret;
  t_string	*tmp;

  tmp = e->s;
  ret  = 0;
  while (tmp != e->cursor)
    {
      ret++;
      tmp = tmp->next;
    }
  return (ret);
}

int	get_absolut(t_elem *e)
{
  int	total;

  total = string_size(e) + e->taille_prompt - 3;
  e->ligne = total / e->x;
  return (0);
}

void	deplace_promt(t_elem *e)
{
  int	size;

  size = e->taille_prompt;
  while (size--)
   my_tputs(e->cap[ND]);
}

