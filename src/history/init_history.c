
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "get_next_line.h"
#include "history.h"
#include "shell.h"
#include "fd_check.h"
#include "my.h"

int	init_history_err(char *filename)
{
  if (errno == EIO)
    {
      fprintf(stderr, "%s: An I/O result has occured\n", filename);
      return (-1);
    }
  else if (errno == EBADF)
    {
      fprintf(stderr, "%s: isn't a valid open file descriptor.\n", filename);
      return (-1);
    }
  else if (errno == EINTR)
    {
      fprintf(stderr, "%s:The close() call", filename);
      fprintf(stderr, " was interrupted by a signal.\n");
      return (-1);
    }
  return (0);
}

int	init_history_limit(t_cmd_list *history, int limit)
{
  t_cmd_list	*tmp;
  t_cmd_list	*ptr;
  int		i;

  i = 0;
  tmp = history;
  while (tmp && i <= limit)
    {
      tmp = tmp->next;
      i++;
    }
  if (tmp)
    {
      ptr = tmp->next;
      tmp->next = NULL;
      free_history(ptr);
    }
  return (EXIT_SUCCESS);
}

int	init_history_read(t_shell *sh, int fd)
{
  t_string	*cmd;
  char		*str;

  str = NULL;
  while ((str = get_next_line(fd)))
    {
      cmd = NULL;
      if ((cmd = history_convert_str_to_cmd(str)) == NULL)
	return (EXIT_FAILURE);
      if (put_in_history(&(sh->history), cmd, str) == EXIT_FAILURE)
	return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

int	init_history_exec(t_shell *sh, char *filename)
{
  int		fd;

  if (fd_check_access(filename, F_OK) == EXIT_FAILURE)
    return (HISTORY_INIT_FAIL);
  if (fd_check_type(filename) != REG)
    {
      fprintf(stderr, "%s: is not a regular file.\n", filename);
      return (HISTORY_INIT_FAIL);
    }
  if ((fd = open(filename, O_RDONLY)) == -1)
    {
      fd_err_check(filename);
      return (HISTORY_OPEN_FAIL);
    }
  if (init_history_read(sh, fd) == EXIT_FAILURE)
    return (HISTORY_INIT_FAIL);
  if (close(fd) == -1)
    {
      init_history_err(filename);
      return (HISTORY_CLOSE_FAIL);
    }
  return (HISTORY_SUCCESS);
}

int	init_history(t_shell *sh, char *filename)
{
  int		ret;
  char		*get_limit;
  int		limit;

  if ((get_limit = explor_env(sh->local, "history_limit")) == NULL)
    limit = 100;
  else
    {
      if (is_numeric(get_limit) == EXIT_SUCCESS)
	limit = my_getnbr(get_limit);
      else
	{
	  fprintf(stderr, "Warning: history_limit is not a number.\n");
	  limit = 100;
	}
    }
  if (limit <= 0 || filename == NULL)
    return (HISTORY_SUCCESS);
  ret = init_history_exec(sh, filename);
  if (ret != HISTORY_SUCCESS)
    return (ret);
  init_history_limit(sh->history, limit);
  sh->history_last = sh->history;
  return (HISTORY_SUCCESS);
}
