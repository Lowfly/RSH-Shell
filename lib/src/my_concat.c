
#include	<stdlib.h>
#include	"my.h"

char	*my_concat(char *a, char *b)
{
  int   size_a;
  int   size_b;
  int   i;
  char  *str;

  if (a == NULL || b == NULL)
    return (NULL);
  size_a = my_strlen(a);
  size_b = my_strlen(b);
  if ((str = malloc(sizeof(*str) * (size_a + size_b + 2))) == NULL)
    return (str);
  i = 0;
  while (i++ < size_a)
    str[i - 1] = a[i - 1];
  i--;
  while (i++ < size_a + size_b)
    str[i - 1] = b[i - size_a - 1];
  str[i - 1] = 0;
  return (str);
}
