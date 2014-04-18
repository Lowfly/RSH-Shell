
#ifndef SIGNAL_H_
# define SIGNAL_H_

/* define msg */
#define SIGPERSO_MSG	"Sigperso"
#define SIGHUP_MSG	"Sighup"
#define SIGINT_MSG	"Sigint"
#define SIGQUIT_MSG	"Sigquit"
#define SIGILL_MSG	"Sigill"
#define SIGTRAP_MSG	"Sigtrap"
#define SIGABORT_MSG	"Sigabort"
#define SIGIOT_MSG	"Sigiot"
#define SIGBUS_MSG	"Sigbus"
#define SIGFPE_MSG	"Sigfpe"
#define SIGKILL_MSG	"Sigkill"
#define SIGUSR1_MSG	"User signal 1"
#define SIGSEV_MSG	"Segmentation Fault"
#define SIGUSR2_MSG	"User signal 2"
#define SIGPIPE_MSG	"Broken pipe"
#define SIGALRM_MSG	"Sigalrm"
#define SIGTERM_MSG	"Sigterm"
#define SIGSTKFLT_MSG	"Sigstkflt"
#define SIGCHLD_MSG	"Sigchld"
#define SIGCONT_MSG	"Sigcont"
#define SIGSTOP_MSG	"Sigstop"
#define SIGTSTP_MSG	"Sigtstp"
#define SIGTTIN_MSG	"Sigttin"
#define SIGTTOU_MSG	"Sigttou"
#define SIGURG_MSG	"Sigurg"
#define SIGXCPU_MSG	"Sigxcpu"
#define SIGXFSZ_MSG	"Sigxfsz"
#define SIGVTALRM_MSG	"Sigvtalrm"
#define SIGPROF_MSG	"Sigprof"
#define SIGWINCH_MSG	"Sigwinch"
#define SIGIO_MSG	"Sigio"
#define SIGPOLL_MSG	"Sigpoll"
#define SIGPWR_MSG	"Sigpwr"
#define SIGSYS_MSG	"Sigchld"

/* define index */
#define PERSO_IND	0
#define SIGHUP_IND	1
#define SIGINT_IND	2
#define SIGQUIT_IND	3
#define SIGILL_IND	4
#define SIGTRAP_IND	5
#define SIGABORT_IND	6
#define SIGIOT_IND	6
#define SIGBUS_IND	7
#define SIGFPE_IND	8
#define SIGKILL_IND	9
#define SIGUSR1_IND	10
#define SIGSEV_IND	11
#define SIGUSR2_IND	12
#define SIGPIPE_IND	13
#define SIGALRM_IND	14
#define SIGTERM_IND	15
#define SIGSTKFLT_IND	16
#define SIGCHLD_IND	17
#define SIGCONT_IND	18
#define SIGSTOP_IND	19
#define SIGTSTP_IND	20
#define SIGTTIN_IND	21
#define SIGTTOU_IND	22
#define SIGURG_IND	23
#define SIGXCPU_IND	24
#define SIGXFSZ_IND	25
#define SIGVTALRM_IND	26
#define SIGPROF_IND	27
#define SIGWINCH_IND	28
#define SIGIO_IND	29
#define SIGPOLL_IND	29
#define SIGPWR_IND	30
#define SIGSYS_IND	31

#define NB_SIG 32

int	process_statut(int, int *);
int	get_signal();

#endif /* SIGNAL_H_ */
