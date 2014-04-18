
#include <stdlib.h>
#include "lexer.h"

int	token_secondary_group(t_token **list)
{
  if ((token_group_by_type(list, S_QUOTE) == EXIT_FAILURE) ||
      (token_group_by_type(list, B_QUOTE) == EXIT_FAILURE) ||
      (token_group_by_type(list, D_QUOTE) == EXIT_FAILURE))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int	token_secondary(t_token **list)
{
  if ((token_secondary_group(list) == EXIT_FAILURE) ||
      (token_parentheses(list) == EXIT_FAILURE) ||
      (token_cmd(list) == EXIT_FAILURE) ||
      (token_delete_type(list, SPACE) == EXIT_FAILURE))
    return (EXIT_FAILURE);
  if (token_logic(*list) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (token_sequences(list) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
