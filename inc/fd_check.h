
#ifndef FD_CHECK_H_
# define FD_CHECK_H_

#include <sys/types.h>

typedef enum {REG, DIR, CHR, BLK, FIFO, LNK, SOCK, UNKNOW, ERR} t_fdtype;

/* errno msg */
int	fd_err_access(char *);
int	fd_err_efaults(char *);
int	fd_err_io(char *);
int	fd_err_loop(char *);
int	fd_err_too_long(char *);
int	fd_err_enoent(char *);
int	fd_err_enomem(char *);
int	fd_err_enotdir(char *);

/* check type of fd */
t_fdtype	fd_is_reg(mode_t);
t_fdtype	fd_is_dir(mode_t);
t_fdtype	fd_is_chr(mode_t);
t_fdtype	fd_is_blk(mode_t);
t_fdtype	fd_is_fifo(mode_t);
t_fdtype	fd_is_lnk(mode_t);
t_fdtype	fd_is_sock(mode_t);

/* check access */
int		fd_check_access(char *, int);
t_fdtype	fd_check_type(char *);
int		fd_err_check(char *);

#endif /* FD_CHECK_H_ */
