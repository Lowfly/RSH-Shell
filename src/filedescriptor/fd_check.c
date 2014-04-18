
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "fd_check.h"

int		fd_check_access(char *path, int mode)
{
  if (access(path, mode) == -1)
    {
      fd_err_check(path);
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

static int		init_ptr(t_fdtype (*check_mode[])(mode_t))
{
  check_mode[0] = &fd_is_reg;
  check_mode[1] = &fd_is_dir;
  check_mode[2] = &fd_is_chr;
  check_mode[3] = &fd_is_blk;
  check_mode[4] = &fd_is_fifo;
  check_mode[5] = &fd_is_lnk;
  check_mode[6] = &fd_is_sock;
  check_mode[7] = NULL;
  return (0);
}

t_fdtype	fd_check_type(char *path)
{
  struct stat	s;
  t_fdtype	(*check_mode[8])(mode_t);
  int		i;
  t_fdtype	type;

  init_ptr(check_mode);
  if (fd_check_access(path, F_OK) == EXIT_FAILURE)
    return (ERR);
  if (stat(path, &s) == -1)
    {
      fd_err_check(path);
      return (ERR);
    }
  type = UNKNOW;
  i = 0;
  while (i < 8 && type == UNKNOW)
    {
      type = (check_mode[i])(s.st_mode);
      i++;
    }
  return (type);
}
