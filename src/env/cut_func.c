
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "env.h"

char	*cut_name(char *str)
{
  int	i;
  char	*name;

  i = -1;
  if ((name = malloc(sizeof(*name) * strlen(str))) == NULL)
    {
      printf("malloc fail\n");
      return (NULL);
    }
  while (str[++i] != '=')
    {
      name[i] = str[i];
    }
  name[i] = '\0';
  return (name);
}

char	*cut_value(char *str)
{
  int	i;
  int	j;
  char	*value;

  i = 0;
  j = 0;
  if ((value = malloc(sizeof(*value) * strlen(str))) == NULL)
    {
      printf("malloc fail\n");
      return (NULL);
    }
  while (str[i] != '=')
    i++;
  i++;
  while (str[i] != '\0')
    {
      value[j] = str[i];
      i++;
      j++;
    }
  value[j] = '\0';
  return (value);
}
