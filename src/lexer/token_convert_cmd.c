/*
** token_convert_cmd.c for  in /home/lelabo_m/
**
** Made by marc lelabourier
** Login   <lelabo_m@epitech.net>
**
** Started on  Thu May 16 10:34:44 2013 marc lelabourier
** Last update Sun May 26 18:12:12 2013 marc lelabourier
*/

#include <stdlib.h>
#include <stdio.h>
#include "token_to_tab.h"
#include "tokeniser.h"
#include "node.h"
#include "builtins.h"
#include "my.h"

char		**token_convert_tab(t_token *list)
{
  t_token	*tmp;
  char		**tab;
  int		i;

  if (list == NULL || ((i = token_to_tab_len(list)) <= 0))
    return (NULL);
  if ((tab = malloc(sizeof(*tab) * (i + 1))) == NULL)
    return (NULL);
  i = 0;
  tmp = list;
  while (tmp)
    {
      (tmp->value.str == NULL) ? (tab[i] = my_strdup("")) :
	(tab[i] = my_strdup(tmp->value.str));
      if (tab[i] == NULL)
	return (NULL);
      i++;
      tmp = tmp->next;
    }
  tab[i] = NULL;
  return (tab);
}

char		*token_convert_tab_to_str(char **tab)
{
  char		*str;
  char		*save;
  int		i;

  if ((tab == NULL) || (tab && tab[0] == NULL))
    return (NULL);
  str = NULL;
  i = 1;
  str = my_strdup(tab[0]);
  while (tab[i])
    {
      save = str;
      str = my_strcat(save, tab[i]);
      free(save);
      i++;
    }
  return (str);
}

int		token_convert_cache(t_token *tmp, t_shell *sh)
{
  tmp = tmp;
  sh = sh;
  return (0);
}

int		token_convert_cmd_prepare(t_token *list,
					  t_shell *sh,
					  int level,
					  int (*convert_func[])(t_token *))
{
  t_token	*tmp;
  int		b;
  int		ret;
  int		i;

  tmp = list;
  (tmp->type == WORD && (is_builtins(tmp->value.str))) ? (b = 1) : (b = 0);
  while (tmp)
    {
      ret = -1;
      i = 0;
      token_convert_cache(tmp, sh);
      while (i < NB_CONVERT_FUNC && ret == -1)
	{
	  if ((ret = (convert_func[i])(tmp)) == EXIT_FAILURE)
	    return (EXIT_FAILURE);
	  i++;
	}
      if ((ret == -1) && (tmp != list) && (level == 0) && (b)
      	  && ((tmp = token_globing(tmp)) == NULL))
      	return (EXIT_FAILURE);
      if (tmp)
	tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}

char		**token_convert_cmd(t_token *box, t_shell *sh, int level)
{
  t_token	*list;
  char		**cmd;
  int		(*convert_func[NB_CONVERT_FUNC])(t_token *);
  int		stat;

  if (box == NULL)
    return (NULL);
  (box->type == CMD) ? (list = box->value.list) : (list = box);
  (list->value_type == LIST) ? (stat = 0) : (stat = 1);
  convert_func[0] = &token_convert_squote;
  convert_func[1] = (int (*)(t_token *)) &token_convert_dquote;
  convert_func[2] = &token_convert_bquote;
  convert_func[3] = &token_convert_parentheses;
  if (token_convert_cmd_prepare(list, sh, level, convert_func) == EXIT_FAILURE)
    return (NULL);
  if ((cmd = token_convert_tab(list)) == NULL)
    return (NULL);
  if ((level == 0) && (stat) && ((cmd = token_alias_replace(cmd, sh)) == NULL))
    return (NULL);
  return (cmd);
}
