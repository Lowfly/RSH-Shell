
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

int	end()
{
  printf("exit");
  return (-3);
}

void	rm_line(t_elem *e)
{
  bol(e);
  my_tputs(e->cap[CD]);
}

int	bol(t_elem *e)
{
  my_tputs(e->cap[VI]);
  while (move_left(e) != -1);
  my_tputs(e->cap[VE]);
  return (0);
}

int	eol(t_elem *e)
{
  my_tputs(e->cap[VI]);
  while (move_right(e) != -1);
  my_tputs(e->cap[VE]);
  return (0);
}

