
#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>
#include	"get_opt.h"
#include	"get_next_line.h"
#include	"exec_parsed.h"
#include	"proc_signal.h"
#include	"history.h"
#include	"parser.h"
#include	"shell.h"
#include	"edit.h"
#include	"conf.h"
#include	"alias.h"

int	shell_initialisation(t_shell *sh, char **environ)
 {
   int	ret;

   if (get_signal() == EXIT_FAILURE)
     return (EXIT_FAILURE);
   if (tgetent(NULL, NULL) <= 0)
     {
       if (tgetent(NULL, "xterm") <= 0)
	 return (EXIT_FAILURE);
     }
   init_shell(sh, environ);
   conf(sh);
   ret = init_history(sh, sh->history_path);
   if (ret != HISTORY_SUCCESS)
     {
       sh->history = NULL;
       if (ret != HISTORY_INIT_FAIL)
   	 return (EXIT_FAILURE);
     }
  return (EXIT_SUCCESS);
}

int	shell_exit(t_shell *sh)
{
  free_env(sh->env);
  free_env(sh->local);
  free_path(sh->path);
  free_alias(sh->alias);
  if (history_put_in_file(sh->history_last, sh->history_path) == EXIT_FAILURE)
    {
      fprintf(stderr, "history save failed.\n");
      return (EXIT_FAILURE);
    }
  free_history(sh->history_last);
  free(sh->history_path);
  return (EXIT_SUCCESS);
}

int		shell_launcher(t_shell *sh)
{
  char		*line;
  t_parsedline	*parsed;

  line = NULL;
  while (sh->alive == True)
    {
      ((isatty(0)) ? (line = get_f_line(sh)) : (line = get_next_line(0)));
      if (line == NULL)
	return (EXIT_SUCCESS);
      if ((parsed = parser(line, sh, 1)) != NULL)
        if (exec_parsed(parsed, sh))
          return (EXIT_FAILURE);
      exec_parsed_free(parsed);
      if (sh->alive == False)
	return (sh->return_value);
      sh->history = sh->history_last;
    }
  return (sh->return_value);
}

int		main(int ac, char **av, char **environ)
{
  t_shell	sh;
  int		return_value;

  if (shell_initialisation(&sh, environ) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (get_opt(av, ac, &sh))
    {
      shell_exit(&sh);
      return (EXIT_SUCCESS);
    }
  return_value = shell_launcher(&sh);
  shell_exit(&sh);
  return (return_value);
}
