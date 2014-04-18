
#include	<stdlib.h>

int	my_strlen(char *str)
{
  int	i;

  if (str == NULL)
    return (0);
  i = 0;
  while (str[i] != '\0')
    i++;
  return (i);
}
