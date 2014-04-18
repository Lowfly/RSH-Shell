/*
** edit_free.c for 42sh in /home/titouan/Code/42sh
**
** Made by titouan creach
** Login   <creach_a@epitech.net>
**
** Started on  Tue Apr 30 15:20:31 2013 titouan creach
** Last update Sun May 26 15:55:18 2013 titouan creach
*/

#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "edit.h"

int	destroy(struct termios *t)
{
  if (tcsetattr(0, 0, t) == -1)
    {
      fprintf(stderr, TERMCAP_ERR);
      return (-1);
    }
  my_tputs(tgetstr("is", NULL));
  my_tputs(tgetstr("rs", NULL));
  return (0);
}

void	free_list(t_elem *e)
{
  t_string	*tmp;

  tmp = NULL;
  if (e->s)
    {
      tmp = e->s;
      e->s = e->s->next;
      free_list(e);
    }
  free(tmp);
  e->s = NULL;
}

void	free_string_edit(t_string *s)
{
  if (s)
    {
      if (s->next)
	free_string(s->next);
      free(s);
    }
}

void	free_tab(char **touch)
{
  int	i;

  i = 0;
  while (i < 13)
    {
      free(touch[i]);
      touch[i] = NULL;
      i++;
    }
  free(touch);
  touch = NULL;
}

