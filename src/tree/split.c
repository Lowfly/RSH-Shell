
#include	<stdlib.h>
#include	"token.h"
#include	"split.h"

int		split(t_token *this, t_token **left, t_token **right)
{
  t_token	*iterator;

  if (this == NULL || left == NULL || right == NULL)
    return (EXIT_FAILURE);
  *right = this->next;
  iterator = *left;
  while (iterator != NULL && iterator != this && iterator->next != this)
    iterator = iterator->next;
  if (iterator != NULL)
    iterator->next = NULL;
  if ((this == *right && this == *left) || iterator == NULL)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
