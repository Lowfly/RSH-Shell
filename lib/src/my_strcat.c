
#include <stdlib.h>
#include "my.h"

char		*my_strncat(char *src, char *dest, int n)
{
  char		*new_src;
  int		i;
  int		c;

  i = 0;
  c = 0;
  if (src == NULL || dest == NULL || my_strlen(dest) < n || n <= 0)
    return (NULL);
  if ((new_src = malloc(sizeof(*dest) * (my_strlen(src) + n + 1))) == NULL)
    return (NULL);
  while (src[c])
    new_src[i++] = src[c++];
  c = 0;
  while (c <= n)
    new_src[i++] = dest[c++];
  new_src[i] = '\0';
  src = NULL;
  dest = NULL;
  return (new_src);
}

char		*my_strcat(char *src, char *dest)
{
  char		*new_src;
  int		i;
  int		c;

  i = 0;
  c = 0;
  if (src == NULL)
    return (my_strdup(dest));
  if (dest == NULL)
    return (my_strdup(src));
  if ((new_src = malloc(sizeof(*new_src)
			* (my_strlen(dest) + my_strlen(src) + 1))) == NULL)
    return (NULL);
  while (src[c])
    new_src[i++] = src[c++];
  c = 0;
  while (dest[c])
   new_src[i++] = dest[c++];
  new_src[i] = '\0';
  return (new_src);
}
