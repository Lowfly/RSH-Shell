
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "fd_check.h"

t_fdtype	fd_is_lnk(mode_t mode)
{
  if (S_ISLNK(mode))
    return (LNK);
  return (UNKNOW);
}

t_fdtype	fd_is_sock(mode_t mode)
{
  if (S_ISSOCK(mode))
    return (SOCK);
  return (UNKNOW);
}
