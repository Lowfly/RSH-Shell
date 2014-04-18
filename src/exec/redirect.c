
#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	"my.h"
#include	"get_next_line.h"
#include	"token_to_tab.h"
#include	"fd_check.h"
#include	"token.h"
#include	"node.h"
#include	"shell.h"
#include	"exec.h"
#include	"redirect.h"

int             redirect_right(t_node *this, t_shell *sh)
{
  int           newfd;
  t_node        *to;

  if (this == NULL)
    return (EXIT_FAILURE);
  rec_redirect(this, sh);
  if ((to = select_file(this)) == NULL)
    return (EXIT_FAILURE);
  if ((newfd = open(to->content->value.str,
			 O_FLAGS | O_TRUNC, FILE_PERMISSION)) == -1)
    {
      fd_err_check(to->content->value.str);
      return (EXIT_FAILURE);
    }
  this->pid = 0;
  this->out = newfd;
  if ((to = select_other(this, to)) == NULL)
    return (EXIT_FAILURE);
  to->in = this->in;
  to->out = newfd;
  return (EXIT_SUCCESS);
}

int             redirect_left(t_node *this, t_shell *sh)
{
  int           newfd;
  t_node        *to;

  if (this == NULL)
    return (EXIT_FAILURE);
  rec_redirect(this, sh);
  if ((to = select_file(this)) == NULL)
    return (EXIT_FAILURE);
  if (fd_check_access(to->content->value.str, F_OK) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  else if ((newfd = open(to->content->value.str, O_RDONLY)) == -1)
    {
      fd_err_check(to->content->value.str);
      return (EXIT_FAILURE);
    }
  this->pid = 0;
  this->in = newfd;
  if ((to = select_other(this, to)) == NULL)
    return (EXIT_FAILURE);
  to->in = newfd;
  to->out = this->out;
  return (EXIT_SUCCESS);
}

int             redirect_double_right(t_node *this, t_shell *sh)
{
  int           newfd;
  t_node        *to;

  if (this == NULL)
   return (EXIT_FAILURE);
  rec_redirect(this, sh);
  if ((to = select_file(this)) == NULL)
    return (EXIT_FAILURE);
  if ((newfd = open(to->content->value.str,
		    O_FLAGS | O_APPEND, FILE_PERMISSION)) == -1)
    {
      fd_err_check(to->content->value.str);
      return (EXIT_FAILURE);
    }
  this->pid = 0;
  this->out = newfd;
  if ((to = select_other(this, to)) == NULL)
    return (EXIT_FAILURE);
  to->in = this->in;
  to->out = newfd;
  return (EXIT_SUCCESS);
}

static int	double_left_loop(int newfds[], char *pass)
{
  int		limit;
  char		*input;

  limit = 0;
  my_putstr("? ");
  while ((input = get_next_line(0)) != NULL && my_strcmp(pass, input))
    {
      my_putstr("? ");
      if ((limit + my_strlen(input)) < 65000)
	{
	  write(newfds[1], input, my_strlen(input));
	  write(newfds[1], "\n", 1);
	}
      else
	{
	  close(newfds[1]);
	  return (EXIT_FAILURE);
	}
      limit += my_strlen(input);
      free(input);
    }
  return (EXIT_SUCCESS);
}

int             redirect_double_left(t_node *this, t_shell *sh)
{
  int           newfds[2];
  t_node        *to;
  char		*pass;

  if ((this == NULL) || ((to = select_file(this)) == NULL) ||
      ((pass = to->content->value.str) == NULL))
    return (EXIT_FAILURE);
  rec_redirect(this, sh);
  if (pipe(newfds) == -1)
    return (EXIT_FAILURE);
  this->pid = 0;
  if ((to = select_other(this, to)) == NULL)
    return (EXIT_FAILURE);
  to->out = this->out;
  if (double_left_loop(newfds, pass) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  to->in = newfds[0];
  close(newfds[1]);
  return (EXIT_SUCCESS);
  return (exec_tree(to, sh));
}
