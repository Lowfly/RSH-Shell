
#ifndef B_UNSETENV_H_
# define B_UNSETENV_H_

typedef struct	s_env t_env;
typedef struct	s_path t_path;

int     b_unsetenv(t_env **, t_path **, char **, int);
void    free_dtab(char **, int);

#endif /* B_UNSETENV_H_ */
