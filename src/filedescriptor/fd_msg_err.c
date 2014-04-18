
#include <stdlib.h>
#include "fd_check.h"

void    fd_init_msg(int (**msg_error)(char *))
{
  msg_error[0] = &fd_err_access;
  msg_error[1] = &fd_err_efaults;
  msg_error[2] = &fd_err_io;
  msg_error[3] = &fd_err_loop;
  msg_error[4] = &fd_err_too_long;
  msg_error[5] = &fd_err_enoent;
  msg_error[6] = &fd_err_enomem;
  msg_error[7] = &fd_err_enotdir;
}

int     fd_err_check(char *file)
{
  int   (*msg_error[8])(char *);
  int   i;

  i = 0;
  fd_init_msg(msg_error);
  while (i < 8)
    {
      if ((msg_error[i](file)) == -1)
	return (-1);
      i++;
    }
  free(file);
  return (0);
}
