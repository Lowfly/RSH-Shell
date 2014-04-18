
#include <stdlib.h>

char	*clean_tab(char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    return (NULL);
  while (str[i])
    {
      if (str[i] == '\t')
	str[i] = ' ';
      i++;
    }
  return (str);
}
