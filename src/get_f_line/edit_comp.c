
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glob.h>
#include "edit.h"
#include "history.h"
#include "prompt.h"
#include "cap.h"
#include "my.h"

int	complete(t_elem *e)
{
  char			*str;
  glob_t		i;
  unsigned int		j;

  str = list_last_word(e);
  str = realloc(str, my_strlen(str) + 2);
  str[my_strlen(str) + 1] = '\0';
  str[my_strlen(str)] = '*';
  if (glob(str, GLOB_TILDE, NULL, &i) != -1)
    {
      j = 0;
      my_putstr("\n");
      while (j < i.gl_pathc)
	{
	  my_putstr(i.gl_pathv[j]);
	  my_putstr("\n");
	  j++;
	}
      globfree(&i);
      free(str);
      print_prompt(NULL, e->shell->local, 0);
      print_str(e);
    }
  return (0);
}

