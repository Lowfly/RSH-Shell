
#ifndef PARSER_H__
# define PARSER_H__

typedef struct s_token	t_token;
typedef struct s_node	t_node;
typedef struct s_shell	t_shell;

typedef struct s_parsedline
{
  t_token		*tokenlist;
  t_node		*tree;
  struct s_parsedline	*next;
}			t_parsedline;

t_parsedline	*parser(char *, t_shell *sh, int);
int	parser_free_line(t_parsedline *lines);

#endif
