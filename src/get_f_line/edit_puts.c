
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glob.h>
#include <sys/ioctl.h>
#include "edit.h"

int	my_putc(int c)
{
  if (write(1, &c, 1) != 1)
    return (-1);
  return (0);
}

void	my_tputs(char *s)
{
  tputs(s, 1, my_putc);
}

