
#include <stdlib.h>
#include "tokeniser.h"
#include "history.h"
#include "edit.h"
#include "my.h"

int		token_rebinding_put_in_cmd(t_string **begin, char c)
{
  t_string	*elem;

  elem = NULL;
  if ((elem = malloc(sizeof(*elem))) == NULL)
    return (EXIT_FAILURE);
  elem->c = c;
  elem->next = NULL;
  elem->prev = *begin;
  if (elem->prev)
    elem->prev->next = elem;
  *begin = elem;
  return (EXIT_SUCCESS);
}

char		*token_rebinding_store(char *cmd, t_token *tmp)
{
  char		*save;
  char		buff[2];

  save = cmd;
  buff[1] = '\0';
  if (tmp->value_type == DEFINE)
    {
      buff[0] = tmp->value.define;
      cmd = my_strcat(save, buff);
    }
  else if (tmp->type == SPACE)
    (tmp->next) ? (cmd = my_strcat(save, " ")) : (save = NULL);
  else if (tmp->type == VAR)
    {
      cmd = my_strcat(save, "$");
      free(save);
      save = cmd;
      cmd = my_strcat(save, tmp->value.str);
    }
  else if (tmp->value_type == STRING)
    cmd = my_strcat(save, tmp->value.str);
  else
    save = NULL;
  free(save);
  return (cmd);
}

int	token_rebinding(t_token *list, t_shell *sh)
{
  t_string	*cmd;
  t_token	*tmp;
  t_cmd_list	*ptr;
  char		*cmd_tmp;

  cmd_tmp = NULL;
  tmp = list;
  if (tmp == NULL)
    return (EXIT_FAILURE);
  if (tmp->type == SPACE)
    tmp = tmp->next;
  while (tmp)
    {
      if ((cmd_tmp = token_rebinding_store(cmd_tmp, tmp)) == NULL)
	return (EXIT_FAILURE);
      tmp = tmp->next;
    }
  cmd = history_convert_str_to_cmd(cmd_tmp);
  ptr = sh->history_last;
  if (put_in_history(&(sh->history_last), cmd, cmd_tmp) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (sh->history == ptr)
    sh->history = sh->history_last;
  return (EXIT_SUCCESS);
}
