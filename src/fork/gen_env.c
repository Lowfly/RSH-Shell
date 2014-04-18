
#include	<stdlib.h>
#include	<unistd.h>
#include	"shell.h"
#include	"my.h"

int     strlen_env(t_shell *shell)
{
  int   i;
  t_env *tmp;

  i = 0;
  tmp = shell->env;
  while (tmp)
    {
      i++;
      tmp = tmp->next;
    }
  return (i);
}

int     cpy_pointers(char **tab, t_env *env)
{
  int   i;
  t_env *tmp;
  char  *str;

  i = 0;
  tmp = env;
  while (tmp)
    {
      if ((str = my_concat(tmp->name, "=")) == NULL)
        return (-1);
      if (tmp->value)
        {
          if ((tab[i] = my_concat(str, tmp->value)) == NULL)
            return (-1);
          free(str);
        }
      else
        tab[i] = str;
      i++;
      tmp = tmp->next;
    }
  tab[i] = NULL;
  return (0);
}

char    **gen_env(t_shell *shell)
{
  char  **env;

  if ((env = malloc(sizeof(char *) * (strlen_env(shell) + 1))) == NULL)
    return (NULL);
  if (cpy_pointers(env, shell->env) == -1)
    return (NULL);
  return (env);
}
