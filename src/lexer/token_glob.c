
#include <stdlib.h>
#include <glob.h>
#include <stdio.h>
#include "tokeniser.h"
#include "my.h"

int	token_globing_check(char *str)
{
  int	check;
  int	hook;
  int	i;

  check = 0;
  hook = -1;
  if (str == NULL)
    return (0);
  i = 0;
  while (str[i])
    {
      if (str[i] == STAR_C || str[i] == INTEROGATION_C)
	check += 1;
      else if (str[i] == HOOKO_C)
	hook = 1;
      else if (str[i] == HOOKC_C && hook == 1)
	hook = 0;
      i++;
    }
  if (hook == 0)
    check += 1;
  return (check);
}

t_token		*token_globing_insert(t_token *current, char *str)
{
  t_token	*elem;
  t_token	*ptr;

  if ((elem = malloc(sizeof(*elem))) == NULL)
    return (NULL);
  elem->type = WORD;
  elem->value_type = STRING;
  elem->value.str = str;
  ptr = current->next;
  current->next = elem;
  elem->next = ptr;
  return (elem);
}

t_token		*token_globing_exec(t_token *elem)
{
  glob_t	globox;
  char		*str;
  int		i;

  str = elem->value.str;
  if ((glob(str, GLOB_TILDE, NULL, &globox) != 0) ||
      (globox.gl_pathv == NULL || globox.gl_pathv[0] == NULL))
    {
      fprintf(stderr, "rsh: no matches found: %s.\n", str);
      return (elem);
    }
  i = 1;
  free(str);
  elem->value.str = my_strdup(globox.gl_pathv[0]);
  while (globox.gl_pathv[i])
    {
      if ((elem = token_globing_insert(elem,
				       my_strdup(globox.gl_pathv[i]))) == NULL)
	return (NULL);
      i++;
    }
  globfree(&globox);
  return (elem);
}

t_token		*token_globing(t_token *elem)
{
  char		*str;

  str = elem->value.str;
  if (my_strcmp("unsetenv", str) == 0 || my_strcmp("setenv", str) == 0
      || my_strcmp("unset", str) == 0 || my_strcmp("set", str) == 0)
    return (elem);
  if (token_globing_check(str))
    elem = token_globing_exec(elem);
  return (elem);
}
