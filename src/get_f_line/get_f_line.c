
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

t_elem g_elem;

int	init_main_loop(t_elem *e, t_shell *shell, int (**ptr)(), char *c)
{
  init_ptr(ptr);
  e->cursor = e->s;
  e->shell = shell;
  e->len = 0;
  if (!(e->cap = load_capacity()))
    return (-1);
  memset(c, 0, 8);
  update_coord(e);
  return (0);
}

char	*main_loop(t_elem *e, t_shell *shell)
{
  char		c[8];
  int		(*ptr[13])();
  int		ret;

  if (init_main_loop(e, shell, ptr, c) == -1)
    return (NULL);
  ret = 0;
  while (c[0] != '\n' && ret != -3)
    {
      memset(c, 0, 8);
      if (read(0, c, 8) == -1)
	return (NULL);
      if (gest_rezise(e))
	return (NULL);
      ret = gere_key(c, e, ptr);
      if (!(ret != 0 || ret == -3 ) && c[0] != 10)
	{
	  if (is_printable(c))
	    push_char(e, c[0], 1);
	}
    }
  if (ret == -3)
    return (NULL);
  return (list_to_char(e));
}

char	*get_f_line(t_shell *shell)
{
  struct termios	t;
  struct termios	cpy;
  char			*debug;

  signal(SIGWINCH, update_p);
  g_elem.s = NULL;
  g_elem.clipboard = NULL;
  g_elem.taille_prompt = print_prompt(shell->env, shell->local, 0) + 2;
  tcgetattr(0, &cpy);
  add_cursor(&g_elem);
  if (init_termcaps(&t) == -1)
    {
      destroy(&t);
      return (get_next_line(0));
    }
  debug = main_loop(&g_elem, shell);
  destroy(&cpy);
  free_list(&g_elem);
  free_string_edit((&g_elem)->clipboard);
  printf("\n");
  if (debug == NULL)
    free_capacity(g_elem.cap);
  return (debug);
}
