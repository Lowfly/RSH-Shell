
#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#include "shell.h"
#include "token.h"
#include "node.h"
#include "b_env.h"

void	env_use_params(t_env **env, char **args, int i[2])
{
  env = env;
  args = args;
  i = i;
}

int	env_help(t_env **env, char **args, int i[2])
{
  env_use_params(env, args, i);
  printf("Usage: env [OPTION]... [-] [NAME=VALUE]... [COMMAND [ARG]...]\n"
	 "Set each NAME to VALUE in the environment and run COMMAND.\n\n"
	 "  -i, --ignore-environment  start with an empty environment\n"
	 "  -0, --null           end each output line with 0 byte rather than n"
	 "ewline\n"
	 "  -u, --unset=NAME     remove variable from the environment\n"
	 "      --help     display this help and exit\n"
	 "      --version  output version information and exit\n\n"
	 "A mere - implies -i.  If no COMMAND, print the resulting environment."
	 "\n\n"
	 "Report env bugs to pailli_a@epitech.eu\n");
  return (EXIT_FAILURE);
}

int	env_version(t_env **env, char **args, int i[2])
{
  env_use_params(env, args, i);
  printf("env (ratSHELL built-in) 0.42\n"
	 "Copyright (C) 2013 The RatShell Company, Inc.\n"
	 "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/g"
	 "pl.html>.\n"
	 "This is free software: you are free to change and redistribute it.\n"
	 "There is NO WARRANTY, to the extent permitted by law.\n\n"
	 "Written by Alexandre Paillier\n");
  return (EXIT_FAILURE);
}
