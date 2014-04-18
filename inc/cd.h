
#ifndef CD_H__
#define CD_H__

#include "env.h"

int	cd_err_access(char *);
int	cd_err_efaults(char *);
int	cd_err_io(char *);
int	cd_err_loop(char *);
int	cd_err_too_long(char *);
int	cd_err_enoent(char *);
int	cd_err_enomem(char *p);
int	cd_err_enotdir(char *);
void	cd_init_msg(int (**)(char *));
int	cd_check(char *);
int	cd_change_dir(char *, t_env *);

#endif
