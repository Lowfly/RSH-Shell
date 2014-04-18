
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "prompt.h"
#include "my.h"

void	get_sig()
{
  printf("\n");
  print_prompt(NULL, NULL, 0);
}

int	get_signal()
{
  if ((signal(SIGINT, get_sig) == SIG_ERR)
      || (signal(SIGTSTP, get_sig) == SIG_ERR)
      || (signal(SIGQUIT, get_sig) == SIG_ERR))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
