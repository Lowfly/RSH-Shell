
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "env.h"
#include "my.h"

int		print_default_prompt(t_env *penv)
{
  char          *user;
  char          *host;
  int		size;

  size = 14;
  if ((user = my_strdup(explor_env(penv, "USER"))) == NULL)
    user = my_strdup("user");
  if ((host = my_strdup(explor_env(penv, "HOST"))) == NULL)
    host = my_strdup("host");
  my_putstr("\033[31m#Rat-shell#\033[0m(\033[01;34m");
  my_putstr(user);
  my_putstr("\033[0m");
  my_putchar('@');
  my_putstr(host);
  my_putchar(')');
  size = size + my_strlen(user) + my_strlen(host);
  free(host);
  free(user);
  return (size - 1);
}

int		print_format_prompt(char *format)
{
  int		size;

  size = 14;
  my_putstr("\033[31m#Rat-shell#\033[0m(\033[01;34m");
  my_putstr(format);
  my_putstr("\033[0m");
  my_putchar(')');
  size = size + my_strlen(format);
  return (size - 1);
}

int             print_prompt(t_env *penv, t_env *local, int update)
{
  static t_env	*save;
  static char	*prompt_str;
  char		*prompt;
  int		size;

  size = 0;
  (penv != NULL || update == 1) ? (save = penv) : (penv = save);
  if (update)
    {
      prompt_str = NULL;
      return (EXIT_SUCCESS);
    }
  if (local)
    {
      prompt = explor_env(local, "prompt");
      prompt_str = prompt;
    }
  else
    prompt = prompt_str;
  if (prompt == NULL)
    size = print_default_prompt(penv);
  else
    size = print_format_prompt(prompt);
  return (size);
}
