
#include	<stdlib.h>
#include	<stdio.h>
#include	"shell.h"
#include	"path.h"
#include	"env.h"
#include	"my.h"

int		b_setenv_show(t_env *env)
{
  t_env		*tmp;

  tmp = env;
  while (tmp)
    {
      printf("%s=%s\n", tmp->name, tmp->value);
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}

int		dup_for_env(t_env *find, t_env *tmp, char **cmd, t_env **env)
{
  if ((find = find_in_env(tmp, cmd[0])) == NULL)
    put_in_rev_env(env, cmd[0], cmd[1]);
  else
    {
      free(find->value);
      if ((find->value = my_strdup(cmd[1])) == NULL)
	return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

int		b_setenv(t_env **env, t_path **path, char **cmd, int freemode)
{
  t_env		*tmp;
  t_env		*find;

  find = NULL;
  tmp = *env;
  if (cmd && cmd[0] == NULL)
    {
      b_setenv_show(*env);
      return (EXIT_SUCCESS);
    }
  if (dup_for_env(find, tmp, cmd, env) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (cmd && my_strcmp("PATH", cmd[0]) == 0)
    {
      free_path(*path);
      if ((*path = pars_path(*env)) == NULL)
	return (EXIT_FAILURE);
    }
  if (freemode)
    free_dtab(cmd, 1);
  return (EXIT_SUCCESS);
}
