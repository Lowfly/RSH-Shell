
#include	<stdlib.h>
#include	<stdio.h>
#include	"my.h"
#include	"shell.h"
#include	"exec_parsed.h"
#include	"parser.h"
#include	"get_opt.h"

static int	version(void)
{
  printf("GNU rsh, version 4.2-rc (x86_64-suse-linux)\n");
  printf("Copyright (C) The RatShell Company, Inc.\n");
  printf("\nThere is NO WARRANTY, to the extent permitted by law.\n");
  return (EXIT_FAILURE);
}

static int	help(void)
{
  printf("GNU rsh, version 4.2-rc (x86_64-suse-linux)\n");
  printf("Usage:\trsh [-c COMMAND] [--version] [--help]\n");
  return (EXIT_FAILURE);
}

static int	exec(char *undup, t_shell *sh)
{
  t_parsedline	*line;
  char		*str;

  str = my_strdup(undup);
  if (str == NULL)
    return (EXIT_FAILURE);
  if ((line = parser(str, sh, 1)) == NULL)
    return (EXIT_FAILURE);
  exec_parsed(line, sh);
  exec_parsed_free(line);
  return (EXIT_FAILURE);
}

int	get_opt(char **av, int ac, t_shell *sh)
{
  int	i;
  int	ret;

  if (sh == NULL)
    return (EXIT_FAILURE);
  if (ac <= 1)
    return (EXIT_SUCCESS);
  i = 1;
  ret = EXIT_SUCCESS;
  while (i < ac)
    {
      if (my_strcmp("--version", av[i]) == 0)
	return (version());
      else if (my_strcmp("-c", av[i]) == 0)
	ret += exec(av[i + 1], sh);
      else if (my_strcmp("--help", av[i]) == 0)
	return (help());
      i++;
    }
  return (ret);
}
