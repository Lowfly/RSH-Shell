
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "proc_signal.h"

int	process_statut_msg_init1(char *msg[])
{
  msg[PERSO_IND] = SIGPERSO_MSG;
  msg[SIGHUP_IND] = SIGHUP_MSG;
  msg[SIGINT_IND] = SIGINT_MSG;
  msg[SIGQUIT_IND] = SIGQUIT_MSG;
  msg[SIGILL_IND] = SIGILL_MSG;
  msg[SIGTRAP_IND] = SIGTRAP_MSG;
  msg[SIGABORT_IND] = SIGABORT_MSG;
  msg[SIGIOT_IND] = SIGIOT_MSG;
  msg[SIGBUS_IND] = SIGBUS_MSG;
  msg[SIGFPE_IND] = SIGFPE_MSG;
  msg[SIGKILL_IND] = SIGKILL_MSG;
  msg[SIGUSR1_IND] = SIGUSR1_MSG;
  msg[SIGSEV_IND] = SIGSEV_MSG;
  msg[SIGUSR2_IND] = SIGUSR2_MSG;
  msg[SIGPIPE_IND] = SIGPIPE_MSG;
  msg[SIGALRM_IND] = SIGALRM_MSG;
  return (EXIT_SUCCESS);
}

int	process_statut_msg_init2(char *msg[])
{
  msg[SIGTERM_IND] = SIGTERM_MSG;
  msg[SIGSTKFLT_IND] = SIGSTKFLT_MSG;
  msg[SIGCHLD_IND] = SIGCHLD_MSG;
  msg[SIGCONT_IND] = SIGCONT_MSG;
  msg[SIGSTOP_IND] = SIGSTOP_MSG;
  msg[SIGTSTP_IND] = SIGTSTP_MSG;
  msg[SIGTTIN_IND] = SIGTTIN_MSG;
  msg[SIGTTOU_IND] = SIGTTOU_MSG;
  msg[SIGURG_IND] = SIGURG_MSG;
  msg[SIGXCPU_IND] = SIGXCPU_MSG;
  msg[SIGXFSZ_IND] = SIGXFSZ_MSG;
  msg[SIGVTALRM_IND] = SIGVTALRM_MSG;
  msg[SIGPROF_IND] = SIGPROF_MSG;
  msg[SIGWINCH_IND] = SIGWINCH_MSG;
  msg[SIGIO_IND] = SIGIO_MSG;
  msg[SIGPOLL_IND] = SIGPOLL_MSG;
  msg[SIGPWR_IND] = SIGPWR_MSG;
  msg[SIGSYS_IND] = SIGSYS_MSG;
  return (EXIT_SUCCESS);
}

int	process_statut_kill(int status, char *msg[])
{
  int	sig;

  sig = WTERMSIG(status);
  if (sig < NB_SIG)
    {
      fprintf(stderr, "killed by signal ");
      fprintf(stderr, "%s.\n", msg[sig]);
    }
  else
    fprintf(stderr, "killed by signal %d\n", sig);
  if (WCOREDUMP(status))
    fprintf(stderr, "(core dumped).\n");
  return (EXIT_SUCCESS);
}

int	process_statut_stop(int status, char *msg[])
{
  int	sig;

  sig = WSTOPSIG(status);
  if (sig < NB_SIG)
    {
      fprintf(stderr, "stopped by signal ");
      fprintf(stderr, "%s\n", msg[sig]);
    }
  else
    fprintf(stderr, "stopped by signal %d\n", sig);
  return (EXIT_SUCCESS);
}

int	process_statut(int status, int *exit_statut)
{
  char	*msg[NB_SIG];

  process_statut_msg_init1(msg);
  process_statut_msg_init2(msg);
  if (exit_statut)
    *exit_statut = WEXITSTATUS(status);
  if (WIFSIGNALED(status))
    process_statut_kill(status, msg);
  else if (WIFSTOPPED(status))
    process_statut_stop(status, msg);
  else if (WIFCONTINUED(status))
    fprintf(stderr, "continued.\n");
  if (WIFEXITED(status))
    return (EXIT_SUCCESS);
  return (EXIT_FAILURE);
}
