
#ifndef JOB_CONTROL_H_
# define JOB_CONTROL_H_

typedef struct s_shell	t_shell;

int	job_change_group(int pid, t_shell *sh);
int	job_wait_group(t_shell *sh);

#endif
