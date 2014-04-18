
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include "edit.h"
#include "get_next_line.h"
#include "cap.h"
#include "prompt.h"

void	update_p()
{
  struct winsize	my_win;

  if (ioctl(0, TIOCGWINSZ, &my_win) == -1)
    return ;
  g_elem.x = my_win.ws_col;
}

int	lock(t_elem *e)
{
  char	c[8];
  char	**idx;

  idx = get_idx();
  if (!idx)
    return (-1);
  while (e->x <= e->taille_prompt)
    {
      memset(c, 0, 8);
      if (read(0, c, 8) == -1)
	return (-1);
      if (!strncmp(idx[5], c, 8))
	{
	  free_tab(idx);
	  xwrite(1, "exit\n", 6);
	  my_tputs(e->cap[CD]);
	  return (1);
	}
    }
  free_tab(idx);
  my_tputs(e->cap[CD]);
  return (0);
}

int	gest_rezise(t_elem *e)
{
  if (e->x <= e->taille_prompt)
    {
      my_tputs(e->cap[CL]);
      printf("please, resize\n");
      if (lock(e))
	return (1);
    }
  return (0);
}

int	update_coord(t_elem *e)
{
  struct winsize	my_win;

  if (ioctl(0, TIOCGWINSZ, &my_win) == -1)
    return (-1);
  e->x = my_win.ws_col;
  return (0);
}
