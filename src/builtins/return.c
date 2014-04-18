
#include	<stdlib.h>
#include	"b_setenv.h"
#include	"shell.h"
#include	"env.h"
#include	"return.h"

static int	nbr_len(int nb)
{
  int		i;

  i = 1;
  while (nb >= 10)
    {
      nb /= 10;
      i++;
    }
  return (i);
}

static void	fill_nbr(char *str, int index, int nb)
{
  if (index)
    fill_nbr(str, index - 1, nb / 10);
  str[index] = nb % 10 + '0';
}

static char	*nbr_to_str(int nb)
{
  char		*new;
  int		n;

  n = nbr_len(nb);
  if ((new = malloc(sizeof(*new) * (n + 1))) == NULL)
    return (NULL);
  fill_nbr(new, n - 1, nb);
  new[n] = '\0';
  return (new);
}

int	set_return(t_env **local, int nb)
{
  char	*cmd[3];
  char	*nbr;

  nbr = nbr_to_str(nb);
  cmd[0] = "?";
  cmd[1] = nbr;
  cmd[2] = NULL;
  b_setenv(local, NULL, cmd, 0);
  free(nbr);
  return (EXIT_FAILURE);
}
