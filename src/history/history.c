
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "tokeniser.h"
#include "history.h"
#include "fd_check.h"
#include "shell.h"
#include "edit.h"
#include "my.h"

int	size_history(t_cmd_list *list)
{
  t_cmd_list	*tmp;
  int		i;

  i = 0;
  tmp = list;
  while (tmp)
    {
      i++;
      tmp = tmp->next;
    }
  return (i);
}

int	show_history(t_cmd_list *list, int i, int til)
{
  t_cmd_list	*tmp;
  t_string	*cmd;

  tmp = list;
  if (i > 1 && i > til)
    show_history(tmp->next, i - 1, til);
  cmd = tmp->cmd;
  printf("%i\t", i);
  while (cmd->c != 0)
    {
      printf("%c", cmd->c);
      cmd = cmd->next;
    }
  printf("\n");
  return (EXIT_SUCCESS);
}

int	put_in_history(t_cmd_list **begin, t_string *cmd, char *str)
{
  t_cmd_list	*elem;

  elem = NULL;
  if ((elem = malloc(sizeof(*elem))) == NULL)
    return (EXIT_FAILURE);
  elem->str = str;
  elem->cmd = cmd;
  elem->next = *begin;
  elem->prev = NULL;
  if (elem->next)
    elem->next->prev = elem;
  *begin = elem;
  return (EXIT_SUCCESS);
}

t_string	*history_convert_str_to_cmd(char *str)
{
  t_string	*cmd;
  int		i;

  cmd = NULL;
  i = 0;
  if (str == NULL)
    return (NULL);
  while (str[i])
    {
      if (token_rebinding_put_in_cmd(&cmd, str[i]) == EXIT_FAILURE)
        return (NULL);
      i++;
    }
  if (token_rebinding_put_in_cmd(&cmd, '\0') == EXIT_FAILURE)
    return (NULL);
  while (cmd->prev)
    cmd = cmd->prev;
  return (cmd);
}

int		history_put_in_file(t_cmd_list *begin, char *filename)
{
  t_cmd_list	*tmp;
  int		fd;

  fd = 0;
  if (filename == NULL)
    return (EXIT_FAILURE);
  if ((fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY,
                 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    {
      fd_err_check(filename);
      return (EXIT_FAILURE);
    }
  tmp = begin;
  while (tmp)
    {
      dprintf(fd, "%s\n", tmp->str);
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}
