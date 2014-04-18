/*
** token_concat_type.c for  in /home/lelabo_m/
**
** Made by marc lelabourier
** Login   <lelabo_m@epitech.net>
**
** Started on  Sun Apr 28 18:16:11 2013 marc lelabourier
** Last update Mon Apr 29 20:21:22 2013 marc lelabourier
*/

#include <stdlib.h>
#include "tokeniser.h"

char    *token_concat_string(t_token *current, t_token *ptr, int len)
{
  t_token       *tmp;
  char          *concat;
  char          save;
  int           i;

  i = 1;
  concat = NULL;
  save = current->value.define;
  if ((concat = malloc(sizeof(*concat) * (len + 2))) == NULL)
    return (NULL);
  concat[0] = save;
  tmp = current->next;
  current->next = ptr;
  while (tmp != current->next)
    {
      concat[i] = tmp->value.define;
      ptr = tmp;
      tmp = tmp->next;
      i++;
      free(ptr);
    }
  concat[i] = '\0';
  return (concat);
}

int     token_concat_type(t_token **list, t_ttype define)
{
  t_token       *tmp;

  tmp = *list;
  if (tmp == NULL)
    return (EXIT_FAILURE);
  while (tmp)
    {
      if (tmp->type == define)
        {
          if ((tmp = token_concat_by_type(tmp, define)) == NULL)
            return (EXIT_FAILURE);
        }
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}
