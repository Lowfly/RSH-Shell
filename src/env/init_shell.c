
#include	<stdlib.h>
#include	"shell.h"
#include	"env.h"
#include	"path.h"
#include	"my.h"

int	init_shell(t_shell *sh, char **environ)
{
  char	*home;

  sh->process_group = 0;
  sh->fdin = -1;
  sh->fdout = -1;
  sh->alive = True;
  sh->return_value = 0;
  sh->env = NULL;
  sh->list = NULL;
  sh->local = NULL;
  sh->alias = NULL;
  sh->path = NULL;
  sh->history = NULL;
  sh->history_last = NULL;
  sh->env = init_env(environ);
  sh->path = pars_path(sh->env);
  home = explor_env(sh->env, "HOME");
  sh->history_path = my_concat(home, "/.rsh_history");
  return (EXIT_SUCCESS);
}
