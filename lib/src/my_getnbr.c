
#include <stdlib.h>
#include "my.h"

int	digit_to_value(char c, char *base)
{
  int	i;

  i = 0;
  while (base[i] != c && base[i] != '\0')
    i++;
  if (base[i] == '\0')
    return (-1);
  return (i);
}

int	my_getnbr_base(char *str, char *base)
{
  int	nb;
  int	i;
  int	c;

  nb = 0;
  i = 0;
  c = 1;
  while (str[i] != '\0')
    {
      if (str[i] == '-')
	c *= -1;
      else if (digit_to_value(str[i], base) != -1)
	{
	  nb *= my_strlen(base);
	  nb += digit_to_value(str[i], base);
	}
      i++;
    }
  return (nb * c);
}

int	is_numeric(char *str)
{
  int	i;

  if (str == NULL)
    return (0);
  (str[0] == '-') ? (i = 1) : (i = 0);
  while (str[i])
    {
      if (str[i] < '0'|| str[i] > '9')
	return (EXIT_FAILURE);
      i++;
    }
  return (EXIT_SUCCESS);
}

int	my_getnbr(char *str)
{
  return (my_getnbr_base(str, "0123456789"));
}
