
#include "my.h"

int     is_builtins(char *str)
{
  if (my_strcmp(str, "setenv") && my_strcmp(str, "unsetenv")
      && my_strcmp(str, "set") && my_strcmp(str, "unset")
      && my_strcmp(str, "alias") && my_strcmp(str, "unalias"))
    return (1);
  return (0);
}
