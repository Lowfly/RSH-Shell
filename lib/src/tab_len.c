
#include <stdlib.h>

int	tab_len(char **tab)
{
  int	i;

  i = 0;
  if (tab)
    {
      while (tab[i])
	i++;
    }
  return (i);
}
