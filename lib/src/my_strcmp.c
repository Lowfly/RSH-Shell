
#include <stdlib.h>
#include "my.h"

char	my_strncmp(char *src, char *dest, int n)
{
  int   i;

  i = 0;
  if ((src == NULL) || (dest == NULL) || n < 1)
    return (-1);
  while (src[i] && dest[i] && i < n)
    {
      if (src[i] != dest[i])
        return (-1);
      i++;
    }
  if (i < n)
    return (-1);
  return (0);
}

char     my_strcmp(char *str, char *dest)
{
  int   i;

  i = 0;
  if (str == NULL || dest == NULL)
    return (-1);
  if ((my_strlen(str)) != my_strlen(dest))
    return (-1);
  while (str[i] != '\0')
    {
      if (str[i] != dest[i])
	return (-1);
      i++;
    }
  return (0);
}
