
#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<string.h>
#include	<stdio.h>
#include	<unistd.h>
#include	"get_next_line.h"
#include	"exec_parsed.h"
#include	"proc_signal.h"
#include	"parser.h"
#include	"shell.h"
#include	"edit.h"
#include	"fd_check.h"
#include	"my.h"

int		exec_parsing(char *line, int nb_line, t_shell *sh)
{
  t_parsedline	*parsed;

  if ((parsed = parser(line, sh, 0)) != NULL)
    {
      if (exec_parsed(parsed, sh))
	{
	  fprintf(stderr, "Error in .rshrc at line %d.\n", nb_line);
	  return (EXIT_FAILURE);
	}
      exec_parsed_free(parsed);
      if (sh->alive == False)
	return (EXIT_SUCCESS);
    }
  else
    {
      fprintf(stderr, "Error in .rshrc at line %d.\n", nb_line);
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

int		parse_file_conf(t_shell *sh, int fd)
{
  char		*line;
  int		nb_line;

  nb_line = 0;
  while ((line = get_next_line(fd)) != NULL)
    {
      if (line && my_strlen(line) > 0 && line[0] != '#')
	exec_parsing(line, nb_line, sh);
      else
	free(line);
      nb_line++;
    }
  return (EXIT_SUCCESS);
}

int	conf_file_open(char *path, int *fd)
{
  int	tmp;

  if (fd_check_access(path, F_OK) == EXIT_FAILURE)
    {
      fprintf(stderr, "Warning: no config file needed by rsh at %s.\n", path);
      return (EXIT_FAILURE);
    }
  if (fd_check_type(path) != REG)
    {
      fprintf(stderr, "%s: is not a regular file.\n", path);
      return (EXIT_FAILURE);
    }
  if ((tmp = open(path, O_RDONLY)) == -1)
    {
      fd_err_check(path);
      return (EXIT_FAILURE);
    }
  *fd = tmp;
  return (EXIT_SUCCESS);
}

int		conf(t_shell *sh)
{
  char		*str;
  char		*path;
  int		fd;

  if (((str = my_strdup(explor_env(sh->env, "HOME"))) == NULL) ||
      ((path = my_strcat(str, "/.rshrc")) == NULL))
    return (EXIT_FAILURE);
  if (conf_file_open(path, &fd) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  free(path);
  free(str);
  parse_file_conf(sh, fd);
  if (close(fd) == -1)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
