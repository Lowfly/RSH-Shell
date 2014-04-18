
#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#include "shell.h"
#include "token.h"
#include "node.h"
#include "b_env.h"
#include "my.h"

int     check_null(char **args)
{
  int   i;

  i = 0;
  while (args[i] && my_strlen(args[i]) > 0 && args[i][0] == '-')
    {
      if (my_strcmp(args[i], "-0") == 0 || my_strcmp(args[i], "--null") == 0)
        {
          fprintf(stderr, "%s%s%s", CANNOT_NULL1, CANNOT_NULL2, CANNOT_NULL3);
          return (EXIT_FAILURE);
        }
      i++;
    }
  return (EXIT_SUCCESS);
}
