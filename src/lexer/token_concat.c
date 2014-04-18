
#include <stdlib.h>
#include "tokeniser.h"

int	token_by_define(t_token **list)
{
  if (token_concat_define(list, AND_C, AND, AND_C[0])
      || token_concat_define(list, OR_C, OR, OR_C[0]))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int	token_by_op(t_token **list)
{
  if (token_concat_op(list, D_RED_L_C, D_RED_L, RED_L)
      || token_concat_op(list, D_RED_R_C, D_RED_R, RED_R))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int	token_by_type(t_token **list)
{
  if (token_concat_type(list, WORD)
      || token_concat_type(list, SPACE))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int	token_concat(t_token **list)
{
  if (token_by_define(list) || token_by_op(list) || token_by_type(list))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
