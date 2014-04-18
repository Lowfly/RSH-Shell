
#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#include "b_unsetenv.h"
#include "shell.h"
#include "token.h"
#include "node.h"
#include "b_env.h"
#include "my.h"

void	free_them(t_benv *benv, t_env **env, t_env **old)
{
  char	*var[2];

  free_dtab(benv->options - 1, 0);
  var[0] = "*";
  var[1] = NULL;
  b_unsetenv(env, NULL, var, 0);
  *env = *old;
}

int	put_in_rev_env(t_env **env, char *name, char *value)
{
  t_env		*elem;
  t_env		*ptr;

  if ((elem = malloc(sizeof(*elem))) == NULL)
    {
      fprintf(stderr, "Failed while trying to allocate memory.\n");
      return (EXIT_FAILURE);
    }
  if ((elem->name = my_strdup(name)) == NULL)
    return (EXIT_FAILURE);
  elem->value = my_strdup(value);
  elem->next = NULL;
  if (*env)
    {
      ptr = *env;
      while (ptr->next)
	ptr = ptr->next;
      ptr->next = elem;
    }
  else
    *env = elem;
  return (EXIT_SUCCESS);
}

int	backup_old(t_env **env, t_env **old)
{
  t_env	*tmp;

  tmp = *env;
  while (tmp)
    {
      if (put_in_rev_env(old, tmp->name, tmp->value) == EXIT_FAILURE)
	return (EXIT_FAILURE);
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}

int	do_the_work(t_shell *shell, t_benv *benv, t_node *node)
{
  int	ret;
  int	ret2;

  if ((ret = loop(shell, benv)) != EXIT_SUCCESS)
    {
      if (benv->args[benv->i[0]])
	{
	  if (my_strcmp(benv->args[benv->i[0]], "--help") == 0 ||
	      my_strcmp(benv->args[benv->i[0]], "--version") == 0)
	    return (EXIT_SUCCESS);
	  if ((ret2 = check_name_value(benv, shell)) == EXIT_FAILURE)
	    return (EXIT_FAILURE);
	  if (ret2 != 3)
	    {
	      if (prepare_exec(ret, benv, shell, node) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	    }
	}
    }
  if (ret == -1)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int	b_env(t_shell *shell, char **args, t_node *node)
{
  t_benv	benv;
  t_env		*old;

  old = NULL;
  benv.args = args;
  benv.i[0] = 0;
  if (backup_old(&shell->env, &old) == EXIT_FAILURE)
    return (-1);
  if (do_the_work(shell, &benv, node) == EXIT_FAILURE)
    return (-1);
  free_them(&benv, &shell->env, &old);
  return (EXIT_FAILURE);
}
