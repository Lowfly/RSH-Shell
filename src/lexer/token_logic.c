
#include <stdlib.h>
#include <stdio.h>
#include "tokeniser.h"

int		token_logic_separator(t_token *list)
{
  t_token	*tmp;
  int		is_last;

  tmp = list;
  is_last = 0;
  while (tmp)
    {
      (tmp->type == SEPARATOR) ? (is_last = 1) : (is_last = 0);
      tmp = tmp->next;
    }
  return ((is_last) ? (EXIT_SUCCESS) : (EXIT_FAILURE));
}

int		token_logic_type(t_token *tmp, t_ttype define)
{
  int		is_first;
  int		nb_def;
  int		nb_cmd;

  nb_cmd = 0;
  nb_def = 0;
  is_first = 0;
  while (tmp)
    {
      if (tmp->type == WORD || tmp->type == CMD ||
	  (is_first == 0 && (tmp->type == D_QUOTE ||
			     tmp->type == S_QUOTE || tmp->type == B_QUOTE)))
	{
	  nb_cmd++;
	  is_first = 1;
	}
      else if (tmp->type == define)
	{
	  nb_def++;
	  is_first = 0;
	}
      tmp = tmp->next;
    }
  return ((nb_def >= nb_cmd && nb_def) ? (EXIT_FAILURE) : (EXIT_SUCCESS));
}

int		token_logic_andor(t_token *tmp)
{
  int		is_first;
  int		nb_op;
  int		nb_cmd;

  nb_cmd = 0;
  nb_op = 0;
  is_first = 0;
  while (tmp)
    {
      if (tmp->type == WORD || tmp->type == CMD ||
	  (is_first == 0 && (tmp->type == D_QUOTE ||
			     tmp->type == S_QUOTE || tmp->type == B_QUOTE)))
	{
	  nb_cmd++;
	  is_first = 1;
	}
      else if (tmp->type == OR || tmp->type == AND)
	{
	  nb_op++;
	  is_first = 0;
	}
      tmp = tmp->next;
    }
  return ((nb_op >= nb_cmd && nb_op) ? (EXIT_FAILURE) : (EXIT_SUCCESS));
}

int     token_ambigous(t_token *tmp, int is_output, int is_input, int nb_pipe)
{
  while (tmp)
    {
      if (tmp->type == RED_L || tmp->type == D_RED_L)
        {
          if (nb_pipe || is_input)
	    return (2);
	  is_input = 1;
        }
      else if (tmp->type == RED_R || tmp->type == D_RED_R)
        is_output = 1;
      else if (tmp->type == PIPE)
        {
          if (is_output)
	    return (1);
          nb_pipe = 1;
        }
      else if (tmp->type == AND || tmp->type == OR || tmp->type == SEPARATOR)
        {
	  is_input = 0;
          is_output = 0;
          nb_pipe = 0;
        }
      tmp = tmp->next;
    }
  return (0);
}

int	token_logic(t_token *list)
{
  int		ret;

  if (token_logic_type(list, PIPE) == EXIT_FAILURE)
    {
      fprintf(stderr, "invalide null command.\n");
      return (EXIT_FAILURE);
    }
  if (token_logic_type(list, SEPARATOR) == EXIT_FAILURE &&
      token_logic_separator(list) == EXIT_FAILURE)
    {
      fprintf(stderr, "syntax error near unexpected token ';'\n");
      return (EXIT_FAILURE);
    }
  if (token_logic_andor(list) == EXIT_FAILURE)
    {
      fprintf(stderr, "syntax error near unexpected token '&&' or '||'\n");
      return (EXIT_FAILURE);
    }
  if ((ret = token_ambigous(list, 0, 0, 0)) != 0)
    {
      (ret == 1) ? (fprintf(stderr, "Ambiguous input redirect.\n")) :
	(fprintf(stderr, "Ambiguous output redirect.\n"));
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
