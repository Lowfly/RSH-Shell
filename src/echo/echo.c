
#include	<stdlib.h>
#include	<stdio.h>
#include	"my.h"
#include	"echo.h"

int		print_info(int mode)
{
  if (mode == VERSION)
    {
      printf("echo (ratSHELL built-in) 0.42\n");
      printf("Copyright (C) 2013 The RatShell Company, Inc.\n");
      printf("License GPLv3+: GNU GPL version 3 or later ");
      printf("<http://gnu.org/licenses/gpl.html\n");
      printf("This is free software: you are free");
      printf(" to change and redistribute it.\n");
      printf("There is NO WARRANTY, to the extent permitted by law.\n\n");
      printf("Written by Antoine Guittet and Marc Le Labourier\n");
    }
  else if (mode == HELP)
    {
      printf("Usage : echo [SHORT-OPTION]... [STRING]...\n");
      printf("        echo LONG-OPTION\n");
    }
  return (EXIT_FAILURE);
}

int	check_option(char **cmd, int *bslash_opt, int *newline, int *index)
{
  int	i;

  while (cmd[*index] && cmd[*index][0] == '-')
    {
      if (my_strcmp(cmd[*index], "--version") == 0)
	return (print_info(VERSION));
      else if (my_strcmp(cmd[*index], "--help") == 0)
	return (print_info(HELP));
      i = 1;
      while (cmd[*index][i])
	{
	  (cmd[*index][i] == 'n') ? (*newline = 0) : (cmd[*index][i] == 'e') ?
	    (*bslash_opt = OPT_ENABLE) : (cmd[*index][i] == 'E') ?
	    (*bslash_opt = OPT_DISABLE) :
	    (fprintf(stderr,
		     "Warning: unknown option for echo: %c.\n", cmd[*index][i]));
	  i++;
	}
      *index += 1;
    }
  return (EXIT_SUCCESS);
}

int	form_f(int index)
{
  int	i;

  i = 0;
  my_putchar('\n');
  while (i <= index)
    {
      my_putchar(' ');
      i++;
    }
  return (0);
}

int		print_echo(char *str)
{
  int		i;
  int		f;

  i = -1;
  f = 0;
  while (str[++i])
    {
      if (str[i] == '\\' && str[i + 1])
	{
	  i += 1;
	  f -= 1;
	  if (str[i] == 'c')
	    return (EXIT_FAILURE);
	  (str[i] == '\\') ? (my_putchar('\\')) : (str[i] == 'a') ?
	    (my_putstr("bip")) : (str[i] == 'b') ? (my_putchar('\b')) :
	    (str[i] == 'e') ? (my_putchar(' ')) : (str[i] == 'f') ? (form_f(f))
	    : (str[i] == 'n') ? (my_putchar('\n')) : (str[i] == 'r') ?
	    (my_putchar('\r')) : (str[i] == 't') ? (my_putchar('\t')) :
	    (str[i] == 'v') ? (my_putchar('\v')) : (printf("%c%c", '\\', str[i]));
	}
      else
	my_putchar(str[i]);
      f++;
    }
  return (EXIT_SUCCESS);
}

int		b_echo(char **cmd)
{
  int		newline;
  int		opt;
  int		id;
  int		ret;

  ret = 0;
  id = 1;
  newline = 1;
  opt = OPT_DISABLE;
  if (cmd != NULL && cmd[0] != NULL)
    {
      if (check_option(cmd, &opt, &newline, &id) == EXIT_FAILURE)
	return (EXIT_SUCCESS);
      while (cmd[id])
	{
	  (opt) ? (my_putstr(cmd[id])) : (ret = print_echo(cmd[id]));
	  if (cmd[id + 1] != NULL)
	    my_putchar(' ');
	  id++;
	}
    }
  if (newline && ret == EXIT_SUCCESS)
    my_putchar('\n');
  return (EXIT_SUCCESS);
}
