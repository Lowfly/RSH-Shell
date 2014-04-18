
#include <stdlib.h>
#include <unistd.h>

void	free_dtab(char **tab, int befruit)
{
  int	i;

  i = 0;
  if (!tab)
    return ;
  while (tab[i])
    free(tab[i++]);
  if (befruit == 1)
    free(tab);
}
