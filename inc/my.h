
#ifndef __MY_H__
# define __MY_H__

int	my_putchar(char );
int	my_putstr(char *);
int	my_strlen(char *);
int	tab_len(char **);
char	*my_strdup(char *);
char	*my_strndup(char *, int);
char	**my_str_to_wordtab(char *, char);
char	*my_concat(char *, char *);
char	*my_strcat(char *, char *);
char	*my_strncat(char *, char *, int);
void    free_dtab(char **, int);
char	my_strcmp(char *, char *);
char	my_strncmp(char *, char *, int);
int	my_getnbr(char *);
int	is_numeric(char *);

#endif  /* __MY_H__ */
