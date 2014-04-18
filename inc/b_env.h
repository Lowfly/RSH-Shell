
#ifndef B_ENV_H_
# define B_ENV_H_

# define INVALID_OP1	"env:invalid option --'%s'\nTry `env --help' for more"
# define INVALID_OP2	" information.\n"
# define UNRECOG_OP1	"env:unrecognized option '--%s'\nTry `env --help' for"
# define UNRECOG_OP2	" more information.\n"
# define CANNOT_NULL1	"env:cannot specify --null (-0) with command: No such"
# define CANNOT_NULL2	" file or directory\nTry `env --help' for more inform"
# define CANNOT_NULL3	"ation.\n"
# define NEEDS_ARG1	"env: option requires an argument -- 'u'\nTry `env "
# define NEEDS_ARG2	"--help' for more information.\n"

typedef struct	s_benv
{
  int           (*ptr[9])(t_env **, char **, int [2]);
  char          *options[9];
  char		**args;
  int		i[2];
}		t_benv;

	/* b_env.c */
int     b_env(t_shell *, char **, t_node *);
int     do_the_work(t_shell *, t_benv *, t_node *);

	/* exec.c */
int     prepare_exec(int, t_benv *, t_shell *, t_node *);

	/* options.c */
int     op_u(t_env **, char **, int [2]);
int     op_0(t_env **, char **, int [2]);
int     op_i(t_env **, char **, int [2]);
int     no_option(t_env **, char);

	/* help_version.c */
int     env_version(t_env **, char **, int [2]);
int     env_help(t_env **, char **, int [2]);

	/* bad_option.c */
int     bad_option(char **, int [2], t_env **);

	/* loop.c */
int      loop(t_shell *, t_benv *);

	/* check_op_null.c */
int     check_null(char **);

	/* check_name_value.c */
int     check_name_value(t_benv *, t_shell *);

#endif /* !B_ENV_H_ */
