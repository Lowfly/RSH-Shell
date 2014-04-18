
#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#include "shell.h"
#include "token.h"
#include "node.h"
#include "b_env.h"
#include "my.h"

void	set_links(int (*ptr[9])(t_env **, char **, int [2]))
{
  ptr[0] = &op_i;
  ptr[1] = &op_0;
  ptr[2] = &op_u;
  ptr[3] = &env_help;
  ptr[4] = &env_version;
  ptr[5] = &op_i;
  ptr[6] = &op_u;
  ptr[7] = &op_0;
  ptr[8] = NULL;
}

int	set_ptrs(int (*ptr[9])(t_env **, char **, int [2]), char *op[9])
{
  set_links(ptr);
  if ((op[0] = my_strdup("-i")) == NULL)
    return (EXIT_FAILURE);
  if ((op[1] = my_strdup("-0")) == NULL)
    return (EXIT_FAILURE);
  if ((op[2] = my_strdup("-u")) == NULL)
    return (EXIT_FAILURE);
  if ((op[3] = my_strdup("--help")) == NULL)
    return (EXIT_FAILURE);
  if ((op[4] = my_strdup("--version")) == NULL)
    return (EXIT_FAILURE);
  if ((op[5] = my_strdup("--ignore-environment")) == NULL)
    return (EXIT_FAILURE);
  if ((op[6] = my_strdup("--unset")) == NULL)
    return (EXIT_FAILURE);
  if ((op[7] = my_strdup("--null")) == NULL)
    return (EXIT_FAILURE);
  op[8] = NULL;
  return (EXIT_SUCCESS);
}

void    make_it_roll(char **args, int i[2], char **options)
{
  i[1] = 0;
  while (options[i[1]] && my_strcmp(args[i[0]], options[i[1]]))
    {
      i[1]++;
    }
}

int	find_size_ptrs(char **op)
{
  int	i;

  i = 0;
  while (op[i])
    i++;
  return (i);
}

int      loop(t_shell *shell, t_benv *benv)
{
  if (set_ptrs(benv->ptr, benv->options) == EXIT_FAILURE)
    return (-1);
  if (!benv->args[benv->i[0]])
    no_option(&shell->env, '\n');
  else
    {
      while (benv->args[benv->i[0]] && benv->args[benv->i[0]][0] == '-')
        {
          make_it_roll(benv->args, benv->i, benv->options);
          if (benv->i[1] == find_size_ptrs(benv->options))
            {
              if (bad_option(benv->args, benv->i, &shell->env) == EXIT_FAILURE)
                return (3);
            }
          else
            if (benv->ptr[benv->i[1]](&shell->env, benv->args, benv->i) == 1)
              return (EXIT_FAILURE);
          benv->i[0]++;
        }
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
