/*
** token_convert_func.c for  in /home/lelabo_m/
**
** Made by marc lelabourier
** Login   <lelabo_m@epitech.net>
**
** Started on  Wed May 22 19:30:19 2013 marc lelabourier
** Last update Sun May 26 18:20:52 2013 marc lelabourier
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "tokeniser.h"
#include "token_to_tab.h"

int	token_convert_squote(t_token *tmp)
{
  char	**tab;
  char	*str;

  if (tmp->type == S_QUOTE)
    {
      tab = NULL;
      str = NULL;
      if ((tab = token_to_tab(tmp)) != NULL)
	if ((str = token_convert_tab_to_str(tab)) == NULL)
	  {
	    free_dtab(tab, 1);
	    return (EXIT_FAILURE);
	  }
      free_dtab(tab, 1);
      token_delete_list(tmp->value.list);
      tmp->value.list = NULL;
      tmp->value.str = str;
      tmp->type = WORD;
      tmp->value_type = STRING;
      return (EXIT_SUCCESS);
    }
  return (-1);
}

int	token_convert_dquote(t_token *tmp, t_shell *sh)
{
  char	**tab;
  char	*str;

  if (tmp->type == D_QUOTE)
    {
      tab = NULL;
      str = NULL;
      if ((tab = token_convert_cmd(tmp->value.list, sh, 1)) != NULL)
	if ((str = token_convert_tab_to_str(tab)) == NULL)
	  {
	    free_dtab(tab, 1);
	    return (EXIT_FAILURE);
	  }
      token_delete_list(tmp->value.list);
      free_dtab(tab, 1);
      tmp->value.str = str;
      tmp->value_type = STRING;
      tmp->type = WORD;
      return (EXIT_SUCCESS);
    }
  return (-1);
}

int	token_convert_bquote(t_token *tmp)
{
  if (tmp->type == B_QUOTE)
    {
      fprintf(stderr, "Warning: backquote is not implement in this shell.\n");
      return (EXIT_SUCCESS);
    }
  return (-1);
}

int	token_convert_parentheses(t_token *tmp)
{
  if (tmp->type == PO)
    {
      fprintf(stderr, "Warning: parentheses is not implement in this");
      fprintf(stderr, " shell.\n");
      return (EXIT_SUCCESS);
    }
  return (-1);
}
