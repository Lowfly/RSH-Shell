
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

int	raw_mode(struct termios *t)
{
  t->c_lflag &= ~ICANON;
  t->c_cc[VMIN] = 1;
  t->c_cc[VTIME] = 0;
  if (tcsetattr(0, 0, t) == -1)
    {
      fprintf(stderr, TERMCAP_ERR);
      return (-1);
    }
  return (0);
}

int	d_echo(struct termios *t)
{
  t->c_lflag &= ~ECHO;
  if (tcsetattr(0, 0, t) == -1)
    {
      fprintf(stderr, TERMCAP_ERR);
      return (-1);
    }
  return (0);
}

int	init_begin()
{
  if (tgetent(NULL, NULL) <= 0)
    return (-1);
  return (0);
}

int	init_termcaps(struct termios *t)
{
  if (tcgetattr(0, t) == -1)
    return (-1);
 if (raw_mode(t) == -1)
    return (-1);
  if (d_echo(t) == -1)
    return (-1);
  my_tputs(tgetstr("im", NULL));
  return (0);
}

