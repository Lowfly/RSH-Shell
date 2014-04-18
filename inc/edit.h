
#ifndef		__EDIT_H__
#define		__EDIT_H__

#include <term.h>
#include "shell.h"

#define TERMCAP_ERR "Error during termcaps initalization.\n"

typedef	struct s_string
{
  char			c;
  struct s_string	*next;
  struct s_string	*prev;
} t_string;

typedef	struct	s_elem
{
  t_string	*s;
  t_string	*cursor;
  t_string	*clipboard;
  t_shell	*shell;
  char		**cap;
  int		x;
  int		ligne;
  int		taille_prompt;
  int		len;
}t_elem;

t_elem	g_elem;

int		my_putstr(char *s);
void		my_tputs(char *s);
int		raw_mode(struct termios *t);
int		d_echo(struct termios *t);
int		init_termcaps(struct termios *t);
char		**get_idx(void);
int		destroy(struct termios *t);
int		add_cursor(t_elem *e);
int		move_left(t_elem *e);
int		move_right(t_elem *e);
int		delete(t_elem *e);
int		not_implement(void);
void		init_ptr(int (**ptr)());
void		swap(t_elem *e, t_string *elem, t_string *cpy);
int		push_char(t_elem *e, char c, int rewrite);
void		show(t_elem *e);
void		free_list(t_elem *e);
void		free_tab(char **touch);
int		gere_key(char *c, t_elem *e, int (**ptr)());
char		*main_loop(t_elem *e, t_shell *shell);
int		string_size(t_elem *e);
char		*list_to_char(t_elem *e);
char		*get_f_line(t_shell *shell);
int		clrscr(t_elem *e);
int		xwrite(int, char *, unsigned int);
int		is_printable(char *);
void		print_str(t_elem *e);
int		ctrl_k(t_elem *);
int		ctrl_y(t_elem *);
void		deplace_promt(t_elem *e);
void		move_cursor_prompt(t_elem *e, t_string *tmp);
void		move_cursor_line(t_elem *e, t_string *tmp);
void		move_tmp(t_string *tmp, const t_elem *e);
int		get_nb_line(t_elem *e);
int		taille_cursor(t_elem *e);
int		move_right_write(t_elem *e);
void		free_string_edit(t_string *);
void		free_string(t_string *);
int		del_elem_history(t_cmd_list *);
char		*list_last_word(t_elem *);
int		write_after(t_elem *e);
int		bol(t_elem *);
int		eol(t_elem *);
int		_bol(t_elem *e, int i);
int		move_left_befor(t_elem *e, int i);
int		update_coord(t_elem *);
void		save_pos();
int		bol_safe(t_elem *e);
int		detect(t_elem *e);
int		last_line(t_elem *e, t_string *tmp);
int		write_all(t_elem *e, int i, int j, int);
char		**load_capacity(void);
void		update_p();
int		lock(t_elem *e);
int		gest_rezise(t_elem *e);
int		free_my_string(t_string *s);
t_string	*string_dup(t_elem *e);
int		my_put_in_clip(t_elem *e, char c);
int		taille_clip(t_elem *e);
int		past(t_elem *e, t_string *cpy, t_string *save);
int		up(t_elem *e);
int		down(t_elem *e);
int		dup_add(t_string **e, int c);
t_string	*dup_str(t_string *e);
void		rm_line(t_elem *e);
void		get_idx2(char **touch, long int *key);
int		end();
int		coplete(t_elem *e);
int		complete(t_elem *e);
int		init_begin();
void		free_capacity(char **cap);
void		free_end_of_clip(t_string *s);

#endif
