
#include <stdlib.h>
#include <stdio.h>
#include "history.h"
#include "b_history.h"
#include "shell.h"
#include "token.h"
#include "node.h"
#include "my.h"
#include "edit.h"

int     op_c(t_shell *shell)
{
  free_history(shell->history);
  shell->history = NULL;
  shell->history_last = NULL;
  return (EXIT_FAILURE);
}

int     op_d(t_shell *shell, char *value)
{
  int           nb;
  int           i;
  t_cmd_list    *tmp;

  if (!value)
    return (-1);
  nb = my_getnbr(value);
  if (nb <= 0 || nb + 1 > (i = size_history(shell->history_last)))
    {
      fprintf(stderr, "rsh: history: %s: history position out of range\n",
              value);
      return (-1);
    }
  tmp = shell->history_last;
  while (tmp && i > nb)
    {
      tmp = tmp->next;
      i--;
    }
  del_elem_history(tmp);
  return (EXIT_FAILURE);
}

int	op_s(t_shell *shell, char *str)
{
  t_string	*string;

  string = NULL;
  string = history_convert_str_to_cmd(str);
  if (string)
    put_in_history(&shell->history_last, string, NULL);
  return (EXIT_FAILURE);
}

int     history_usage(void)
{
  printf("history: usage: history [-c] [-d offset] [-s] [n]\n");
  return (EXIT_FAILURE);
}

int     history_version(void)
{
  printf("history (ratSHELL built-in) 0.42\n"
	 "Copyright (C) 2013 The RatShell Company, Inc.\n"
	 "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/g"
	 "pl.html>.\n"
	 "This is free software: you are free to change and redistribute it.\n"
	 "There is NO WARRANTY, to the extent permitted by law.\n\n"
	 "Written by Alexandre Paillier\n");
  return (EXIT_FAILURE);
}
