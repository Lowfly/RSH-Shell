
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

void	free_end_of_clip(t_string *s)
{
  t_string	*tmp;

  if (s)
    {
      tmp = s;
      if (tmp->next)
	tmp = tmp->next;
      while (tmp->next)
	{
	  free(tmp->prev);
	  tmp = tmp->next;
	}
      free(tmp);
    }
}
