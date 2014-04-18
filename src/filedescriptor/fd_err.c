
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int	fd_err_access(char *p)
{
  if (errno == EACCES)
    {
      fprintf(stderr, "%s: Permission denied.\n", p);
      return (-1);
    }
  return (0);
}

int	fd_err_efaults(char *p)
{
  if (errno == EFAULT)
    {
      fprintf(stderr, "%s: Path points outside", p);
      fprintf(stderr, "your accessible adress space.\n");
      return (-1);
    }
  return (0);
}

int	fd_err_io(char *p)
{
  if (errno == EIO)
    {
      fprintf(stderr, "%s: An I/O result has occured\n", p);
      return (-1);
    }
  return (0);
}

int	fd_err_loop(char *p)
{
  if (errno == ELOOP)
    {
      fprintf(stderr, "%s: Too many symolic links.\n", p);
      return (-1);
    }
  return (0);
}

int	fd_err_too_long(char *p)
{
  if (errno == ENAMETOOLONG)
    {
      fprintf(stderr, "%s: Too long.", p);
      return (-1);
    }
  return (0);
}
