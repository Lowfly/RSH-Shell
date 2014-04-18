
#include	<stdio.h>
#include	<stdlib.h>
#include	"my.h"
#include	"tokeniser.h"

int	token_primary_func(t_ttype tab[])
{
  tab[0] = S_QUOTE;
  tab[1] = B_SLASH;
  tab[2] = SEPARATOR;
  tab[3] = B_QUOTE;
  tab[4] = D_QUOTE;
  tab[5] = PO;
  tab[6] = PC;
  tab[7] = PIPE;
  tab[8] = VAR;
  tab[9] = RED_L;
  tab[10] = RED_R;
  tab[11] = BG;
  tab[12] = SPACE;
  return (EXIT_SUCCESS);
}

int	token_define(char token[])
{
  token[0] = S_QUOTE_C;
  token[1] = B_SLASH_C;
  token[2] = SEPARATOR_C;
  token[3] = B_QUOTE_C;
  token[4] = D_QUOTE_C;
  token[5] = PO_C;
  token[6] = PC_C;
  token[7] = PIPE_C;
  token[8] = VAR_C;
  token[9] = RED_L_C;
  token[10] = RED_R_C;
  token[11] = BG_C;
  token[12] = SPACE_C;
  return (EXIT_SUCCESS);
}

int	token_tab_func(t_ttype token_id[],
		       t_token_func tab[],
		       char token_char[])
{
  int	i;

  i = 0;
  while (i < NB_PRIMARY_TOKEN)
    {
      tab[i].tokenprim = token_char[i];
      tab[i].token_id = token_id[i];
      i++;
    }
  return (EXIT_SUCCESS);
}

t_token		*tokeniser_create(char *str)
{
  t_token	*list;
  t_token_func	tab[NB_PRIMARY_TOKEN];
  t_ttype	token_id[NB_PRIMARY_TOKEN];
  char		token_char[NB_PRIMARY_TOKEN];
  int		p;

  if (str == NULL)
    return (NULL);
  token_primary_func(token_id);
  token_define(token_char);
  token_tab_func(token_id, tab, token_char);
  list = NULL;
  while (*str != '\0')
    {
      p = 0;
      while (p != NB_PRIMARY_TOKEN && tab[p].tokenprim != *str)
	  p++;
      (p != NB_PRIMARY_TOKEN) ? (token_insert(&list, tab[p].token_id, *str))
      	: (token_insert(&list, WORD, *str));
      str += 1;
    }
  return (list);
}

t_token		*tokeniser(char	*line)
{
  int		(*tokeniser_func[NB_PRIMARY_FUNC])(t_token **);
  t_token	*list;
  int		ret;
  int		i;

  tokeniser_func[0] = &token_backslash;
  tokeniser_func[1] = &token_normaliser;
  tokeniser_func[2] = &token_concat;
  tokeniser_func[3] = &token_var;
  tokeniser_func[4] = &token_dirfile;
  tokeniser_func[5] = &token_dirfile_ord;
  list = NULL;
  if ((list = tokeniser_create(line)) == NULL)
    return (NULL);
  i = 0;
  while (i < NB_PRIMARY_FUNC)
    {
      if ((ret = (tokeniser_func[i])(&list)) == EXIT_FAILURE)
	{
	  token_delete_list(list);
	  return (NULL);
	}
      i++;
    }
   return (list);
}
