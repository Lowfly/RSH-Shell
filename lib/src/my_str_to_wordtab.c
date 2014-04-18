
#include <stdlib.h>
#include "my.h"

int	count_ellem_to_tab(char *str, char c)
{
  int	nb;
  int	x;

  nb = 1;
  x = 0;
  while (str[x] != '\0')
    {
      if (str[x] == c)
	{
	  nb = nb + 1;
	  while (str[x] == c)
	    x++;
	}
      else
	x++;
    }
  return (nb);
}

static char	*my_strwdup(char *copy, char *str, int *i, int n)
{
  int	x;

  x = 0;
  while (*i < n)
    {
      copy[x++] = str[*i];
      *i = *i + 1;
    }
  if (x == 0)
    return (NULL);
  copy[x] = '\0';
  return (copy);
}

char	**store_in_tab(char *str, char **tab, char c)
{
  char	*copy;
  int	i;
  int	n;
  int	store;

  i = 0;
  n = 0;
  store = 0;
  copy = NULL;
  while (str[i] != '\0')
    {
      while (str[n] != c && str[n] != '\0')
	n = n + 1;
      if ((copy = malloc(sizeof(*copy) * ((n - i) + 1))) == NULL)
	return (NULL);
      copy[0] = '\0';
      while (str[i] == c)
	i = i + 1;
      if ((copy = my_strwdup(copy, str, &i, n)) != NULL)
	tab[store++] = copy;
      while (str[n] == c)
	n = n + 1;
    }
  tab[store] = NULL;
  return (tab);
}

char	**my_str_to_wordtab(char *str, char c)
{
  char	**tab;
  int	nb_elem;

  tab = NULL;
  nb_elem = count_ellem_to_tab(str, c);
  if ((nb_elem == 0) || (tab = malloc(sizeof(*tab) * (nb_elem + 1))) == NULL)
    return (NULL);
  tab = store_in_tab(str, tab, c);
  return (tab);
}

void	show_tab(char **tab)
{
  int	i;

  i = 0;
  if (tab)
    {
      while (tab[i])
	{
	  my_putstr("tab = ");
	  my_putstr(tab[i]);
	  my_putstr(".\n");
	  i++;
	}
    }
}
