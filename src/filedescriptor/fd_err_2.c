
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int	fd_err_enoent(char *p)
{
  if (errno == ENOENT)
    {
      fprintf(stderr, "%s: No such file or directory.\n", p);
      return (-1);
    }
  return (0);
}

int	fd_err_enomem(char *p)
{
  if (errno == ENOENT)
    {
      fprintf(stderr, "%s: Insufficient kernel memory was available\n", p);
      return (-1);
    }
  return (0);
}

int	fd_err_enotdir(char *p)
{
  if (errno == ENOTDIR)
    {
      fprintf(stderr, "%s: Is not a directory.\n", p);
      return (-1);
    }
  return (0);
}
