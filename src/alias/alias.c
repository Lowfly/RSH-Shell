
#include	<stdlib.h>
#include	<stdio.h>
#include	"shell.h"
#include	"alias.h"
#include	"my.h"

int		b_alias_show(t_alias *list)
{
  t_alias	*tmp;

  tmp = list;
  printf("ALIAS\t\t=\t\tVALUE:\n\n");
  if (tmp == NULL)
    {
      printf("\t\tVoid.\n");
      return (EXIT_SUCCESS);
    }
  while (tmp)
    {
      printf("%s\t\t=\t\t%s\n", tmp->name, tmp->value);
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}

int     put_in_rev_alias(t_alias **alias, char *name, char *value)
{
  t_alias         *elem;
  t_alias         *ptr;

  if ((elem = malloc(sizeof(*elem))) == NULL)
    return (EXIT_FAILURE);
  if ((elem->name = my_strdup(name)) == NULL)
    return (EXIT_FAILURE);
  elem->value = my_strdup(value);
  elem->next = NULL;
  if (*alias)
    {
      ptr = *alias;
      while (ptr && ptr->next)
        ptr = ptr->next;
      ptr->next = elem;
    }
  else
    *alias = elem;
  return (EXIT_SUCCESS);
}

t_alias   *find_in_alias(t_alias *alias, char *name)
{
  t_alias *tmp;

  tmp = alias;
  if (alias == NULL || name == NULL)
    return (NULL);
  while (tmp && my_strcmp(tmp->name, name))
    tmp = tmp->next;
  if (tmp == NULL)
    return (NULL);
  return (tmp);
}

int		b_alias(t_alias **alias, char **cmd, int bool)
{
  t_alias	*tmp;
  t_alias	*find;

  tmp = *alias;
  if (cmd && cmd[0] == NULL)
    {
      b_alias_show(*alias);
      return (EXIT_SUCCESS);
    }
  if ((find = find_in_alias(tmp, cmd[0])) == NULL)
    put_in_rev_alias(alias, cmd[0], cmd[1]);
  else
    {
      free(find->value);
      find->value = my_strdup(cmd[1]);
    }
  if (bool)
    free_dtab(cmd, 1);
  return (EXIT_SUCCESS);
}
