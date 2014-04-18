
#include <stdlib.h>
#include "my.h"

char	*my_strndup(char *src, int n)
{
  char	*cpy;
  int	i;

  i = 0;
  cpy = NULL;
  if (src == NULL)
    return (NULL);
  if ((cpy = malloc(sizeof(*cpy) * (n + 1))) == NULL)
    return (NULL);
  while (src[i] && i < n)
    {
      cpy[i] = src[i];
      i++;
    }
  cpy[i] = '\0';
  return (cpy);
}

char	*my_strdup(char *src)
{
  char	*cpy;
  int	i;

  i = 0;
  cpy = NULL;
  if (src == NULL)
    return (NULL);
  if ((cpy = malloc(sizeof(*src) * (my_strlen(src) + 1))) == NULL)
    return (NULL);
  while (src[i] != '\0')
    {
      cpy[i] = src[i];
      i++;
    }
  cpy[my_strlen(src)] = '\0';
  return (cpy);
}
