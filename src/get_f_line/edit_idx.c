
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

int	suppr(t_elem *e)
{
  t_string	*tmp;

  if (e->cursor->next && e->cursor->prev)
    {
      e->cursor->prev->next = e->cursor->next;
      e->cursor->next->prev = e->cursor->prev;
      tmp = e->cursor;
      e->cursor = e->cursor->next;
      free(tmp);
    }
  else if (!e->cursor->prev && e->cursor->next)
    {
      e->cursor = e->cursor->next;
      e->s = e->cursor;
     free(e->s->prev);
      e->s->prev = NULL;
    }
  --e->len;
  write_all(e, 0,  0, 0);
  return (0);

}

void	init_ptr(int (**ptr)())
{
  ptr[0] = up;
  ptr[1] = down;
  ptr[2] = move_right;
  ptr[3] = move_left;
  ptr[4] = delete;
  ptr[5] = end;
  ptr[6] = clrscr;
  ptr[7] = eol;
  ptr[8] = bol;
  ptr[9] = complete;
  ptr[10] = ctrl_k;
  ptr[11] = ctrl_y;
  ptr[12] = suppr;
}

void	get_idx2(char **touch, long int *key)
{
  touch[0] = strndup((char*)&key[0], 8);
  touch[1] = strndup((char*)&key[1], 8);
  touch[2] = strndup((char*)&key[2], 8);
  touch[3] = strndup((char*)&key[3], 8);
  touch[4] = strndup((char*)&key[4], 8);
  touch[5] = strndup((char*)&key[5], 8);
  touch[6] = strndup((char*)&key[6], 8);
  touch[7] = strndup((char*)&key[7], 8);
  touch[8] = strndup((char*)&key[8], 8);
  touch[9] = strndup((char*)&key[9], 8);
  touch[10] = strndup((char*)&key[10], 8);
  touch[11] = strndup((char*)&key[11], 8);
  touch[12] = strndup((char*)&key[12], 8);
}

char	**get_idx(void)
{
  long	int key[13];
  char	**touch;

  key[0] = 4283163;
  key[1] = 4348699;
  key[2] = 4414235;
  key[3] = 4479771;
  key[4] = 127;
  key[5] = 4;
  key[6] = 12;
  key[7] = 5;
  key[8] = 1;
  key[9] = '\t';
  key[10] = 11;
  key[11] = 25;
  key[12] = 2117294875;
  if ((touch = malloc(sizeof(char*) * 13)) == NULL)
    return (NULL);
  get_idx2(touch, key);
  return (touch);
}

