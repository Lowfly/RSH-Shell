
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glob.h>
#include <sys/ioctl.h>
#include "edit.h"

void	free_capacity(char **cap)
{
  free(cap);
  cap = NULL;
}

char	**load_capacity(void)
{
  static char **ret;

  if (ret == NULL)
    {
      if (!(ret = malloc(sizeof(char *) * 15)))
	return (NULL);
      ret[0] = tgetstr("vi", NULL);
      ret[1] = tgetstr("in", NULL);
      ret[2] = tgetstr("ve", NULL);
      ret[3] = tgetstr("cd", NULL);
      ret[4] = tgetstr("rs", NULL);
      ret[5] = tgetstr("im", NULL);
      ret[6] = tgetstr("sc", NULL);
      ret[7] = tgetstr("rc", NULL);
      ret[8] = tgetstr("nd", NULL);
      ret[9] = tgetstr("up", NULL);
      ret[10] = tgetstr("do", NULL);
      ret[11] = tgetstr("cr", NULL);
      ret[12] = tgetstr("cl", NULL);
      ret[13] = tgetstr("ei", NULL);
      ret[14] = tgetstr("le", NULL);
    }
  return (ret);
}
