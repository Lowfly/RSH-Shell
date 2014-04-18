
#include <stdlib.h>
#include <unistd.h>
#include "my.h"

int	my_putstr(char *str)
{
  if (str == NULL)
    return (EXIT_FAILURE);
  write(1, str, my_strlen(str));
  return (EXIT_SUCCESS);
}
