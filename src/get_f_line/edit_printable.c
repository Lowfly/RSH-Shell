
#include "edit.h"
#include "my.h"

int	is_printable(char *s)
{
  if (my_strlen(s) == 1)
    {
      if ((s[0] >= 0x20) && (s[0] <= 0x7E))
	return (1);
    }
  return (0);
}
