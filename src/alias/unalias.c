
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "alias.h"
#include "b_unsetenv.h"
#include "prompt.h"
#include "my.h"

int     unset_else_alias(t_alias *alias)
{
  t_alias *to_rm;

  to_rm = alias->next;
  free(alias->next->name);
  free(alias->next->value);
  alias->next = to_rm->next;
  free(to_rm);
  return (0);
}

int     unset_first_alias(t_alias **alias)
{
  t_alias *first;

  first = *alias;
  *alias = (*alias)->next;
  free(first->name);
  free(first->value);
  free(first);
  return (0);
}

int     unset_all_alias(t_alias **alias)
{
  t_alias *tmp;
  t_alias *save;

  tmp = *alias;
  *alias = NULL;
  while (tmp)
    {
      save = tmp;
      tmp = tmp->next;
      free(save->name);
      free(save->value);
      free(save);
      save = NULL;
    }
  return (0);
}

int     check_it_alias(t_alias **alias, char *var)
{
  t_alias *tmp;

  if (my_strcmp("*", var) == 0)
    return (unset_all_alias(alias));
  tmp = *alias;
  while (tmp)
    {
      if (tmp->next && my_strcmp(tmp->next->name, var) == 0)
        return (unset_else_alias(tmp));
      else if (my_strcmp(tmp->name, var) == 0)
        return (unset_first_alias(alias));
      tmp = tmp->next;
    }
  return (-1);
}

int     b_unalias(t_alias **alias, char **variables, int befree)
{
  int   i;

  i = 0;
  if (!variables || !alias || !*alias)
    return (-1);
  while (variables[i])
    {
      if (check_it_alias(alias, variables[i++]) == -1)
	{
	  if (befree == 1)
	    free_dtab(variables, 1);
	  return (-1);
	}
    }
  if (befree == 1)
    free_dtab(variables, 1);
  return (0);
}
