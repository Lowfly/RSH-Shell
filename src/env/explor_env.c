
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "env.h"
#include "my.h"

char	*explor_env(t_env *env, char *name)
{
  t_env	*tmp;

  tmp = env;
  if (env == NULL || name == NULL)
    return (NULL);
  while (tmp && my_strcmp(tmp->name, name))
    tmp = tmp->next;
  if (tmp == NULL)
    return (NULL);
  return (tmp->value);
}

t_env	*find_in_env(t_env *env, char *name)
{
  t_env	*tmp;

  tmp = env;
  if (env == NULL || name == NULL)
    return (NULL);
  while (tmp && my_strcmp(tmp->name, name))
    tmp = tmp->next;
  if (tmp == NULL)
    return (NULL);
  return (tmp);
}
