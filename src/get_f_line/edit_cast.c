
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "edit.h"

int	string_size(t_elem *e)
{
  int		i;
  t_string	*tmp;

  tmp = e->s;
  i = 0;
  while (tmp)
    {
      i++;
      tmp = tmp->next;
    }
  return (i);
}

char	*list_to_char(t_elem *e)
{
  char		*ret;
  int		i;
  t_string	*tmp;

  tmp = e->s;
  i = 0;
  ret = malloc(sizeof(char) * string_size(e));
  if (!ret)
    return (NULL);
  while (tmp)
    {
      ret[i] = tmp->c;
      i++;
      tmp = tmp->next;
    }
  return (ret);
}

char	*list_last_word(t_elem *e)
{
  t_string	*tmp;
  char		*ret;
  int		i;

  tmp = e->s;
  i = 0;
  while (tmp && tmp->c)
    tmp = tmp->next;
  while (tmp->prev && tmp->prev->c != ' ')
    {
      tmp = tmp->prev;
      i++;
    }
  if (tmp->c == ' ')
    tmp = tmp->next;
  if ((ret = malloc(sizeof(*ret) * (i + 1))) == NULL)
    return (NULL);
  i = 0;
  while (tmp && tmp->c)
    {
      ret[i++] = tmp->c;
      tmp = tmp->next;
    }
  ret[i] = '\0';
  return (ret);
}
