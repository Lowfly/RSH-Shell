
#ifndef B_HISTORY_
# define B_HISTORY_

# include "history.h"

int     b_history(t_shell *, char **);
int     history_usage(void);
int     op_d(t_shell *, char *);
int     op_c(t_shell *);
int     check_number(t_shell *, char **);
int     history_version(void);
int     op_s(t_shell *, char *);

#endif /* !B_HISTORY_ */
