
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "fd_check.h"
#include "env.h"
#include "cd.h"
#include "my.h"

int	cd_check(char *p)
{
  if (fd_check_access(p, F_OK) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (fd_check_type(p) != DIR)
    {
      fprintf(stderr, "%s: is not a Directory.\n", p);
      return (EXIT_FAILURE);
    }
  if (chdir(p) == -1)
    {
      fd_err_check(p);
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

char	*cd_go_back(char *path)
{
  int	i;

  if (!path)
    return (NULL);
  i = my_strlen(path);
  if (i > 0)
    i -= 1;
  while (i > 1 && path[i] != '/')
    i--;
  path[i] = '\0';
  return (path);
}

char	*cd_concat(char *path, char *dir)
{
  char	*tmp;

  tmp = my_concat(path, "/");
  free(path);
  path = tmp;
  tmp = my_concat(path, dir);
  free(path);
  path = tmp;
  return (path);
}

char	*cd_gen_path(char *p, char *home, t_env *pwd)
{
  char	*path;
  char	**tab;
  int	i;

  path = NULL;
  tab = NULL;
  if (p == NULL || home == NULL)
    return (NULL);
  if (pwd)
    (p[0] != '/') ? (path = my_strdup(pwd->value)) : (path = my_strdup("/"));
  if ((tab = my_str_to_wordtab(p, '/')) == NULL)
    return (NULL);
  i = 0;
  while (tab[i])
    {
      if (!my_strcmp("..", tab[i]))
	path = cd_go_back(path);
      else if (!my_strcmp("~", tab[i]))
	path = cd_concat(path, home);
      else
	path = cd_concat(path, tab[i]);
      i++;
    }
  free_dtab(tab, 0);
  return (path);
}

int	cd_change_dir(char *p, t_env *env)
{
  static char	*old;
  char		*home;
  char		*pwd;
  t_env		*env_pwd;

  if ((home = explor_env(env, "HOME")) == NULL)
    home = my_strdup("/");
  env_pwd = find_in_env(env, "PWD");
  pwd = NULL;
  (p == NULL) ? (pwd = my_strdup(home)) :
    (!my_strncmp(p, "-", 1)) ? (pwd = old) :
    (pwd = cd_gen_path(p, home, env_pwd));
  if ((pwd == NULL) || (cd_check(pwd) == EXIT_FAILURE))
    {
      free(pwd);
      return (-1);
    }
  if (env_pwd)
    {
      old = my_strdup(env_pwd->value);
      free(env_pwd->value);
      env_pwd->value = my_strdup(pwd);
    }
  free(pwd);
  return (EXIT_FAILURE);
}
