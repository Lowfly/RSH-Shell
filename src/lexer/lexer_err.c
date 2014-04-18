
#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"
#include "tokeniser.h"

int	lexer_err_unmatched(t_ttype define)
{
  fprintf(stderr, "Unmatched ");
  if (define == S_QUOTE)
    fprintf(stderr, "'.\n");
  else if (define == B_QUOTE)
    fprintf(stderr, "`.\n");
  else if (define == D_QUOTE)
    fprintf(stderr, "\".\n");
  return (EXIT_FAILURE);
}

int	lexer_err_too_many(t_ttype define)
{
  fprintf(stderr, "Too many ");
  if (define == PO || define == PC)
    fprintf(stderr, ")'s.\n");
  return (EXIT_FAILURE);
}

int	lexer_err(int error, t_ttype define)
{
  if (error == UNMATCHED)
    lexer_err_unmatched(define);
  else if (error == TOO_MANY)
    lexer_err_too_many(define);
  else if (error == EMPTY)
    fprintf(stderr, "Error in lexer: token list is empty.\n");
  else if (error == NULL_CMD)
    fprintf(stderr, "Invalid null command.\n");
  else if (error == UNDIF_VAR)
    fprintf(stderr, " : Undefined variable.\n");
  return (EXIT_FAILURE);
}
