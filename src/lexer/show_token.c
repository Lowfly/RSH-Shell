
#include <stdio.h>
#include "tokeniser.h"

void		token_is_define(t_token *current)
{
  printf("content:[%c] + vtype = DEF + ", current->value.define);
}

void		token_is_string(t_token *current)
{
  printf("content:[%s] + vtype = STR + ", current->value.str);
}

void		token_is_list(t_token *current)
{
  printf("new_list\n");
  show_token_list(current->value.list);
}

void		print_type(t_token *tmp)
{
  (tmp->type == S_QUOTE) ? (printf("s_quote")) : (tmp->type == B_SLASH) ?
    (printf("b_slash")) : (tmp->type == SEPARATOR) ? (printf("separator")) :
    (tmp->type == B_QUOTE) ? (printf("b_quote")) : (tmp->type == D_QUOTE) ?
    (printf("d_quote")) : (tmp->type == PO) ? (printf("PO")) :
    (tmp->type == PC) ? (printf("PC")) : (tmp->type == AND) ?
    (printf("AND")) : (tmp->type == OR) ? (printf("OR")) :
    (tmp->type == PIPE) ? (printf("PIPE")) : (tmp->type == VAR) ?
    (printf("VAR")) : (tmp->type == RED_L) ? (printf("RED_L")) :
    (tmp->type == RED_R) ? (printf("RED_R")) : (tmp->type == D_RED_L) ?
    (printf("D_RED_L")) : (tmp->type == D_RED_R) ? (printf("D_RED_R")) :
    (tmp->type == BG) ? (printf("BG")) : (tmp->type == SPACE) ?
    (printf("SPACE")) : (tmp->type == WORD) ? (printf("WORD")) :
    (tmp->type == FILENAME) ? (printf("FILE")) : (tmp->type == SAVE) ?
    (printf("SAVE")) : (printf("CMD"));
  printf("\n");
}

void            show_token_list(t_token *list)
{
  t_token       *tmp;

  tmp = list;
  printf("BEGIN LIST\n");
  while (tmp)
    {
      if (tmp->value_type == DEFINE)
	token_is_define(tmp);
      if (tmp->value_type == STRING)
	token_is_string(tmp);
      if (tmp->value_type == LIST)
	printf("list type = ");
      print_type(tmp);
      if (tmp->value_type == LIST)
	token_is_list(tmp);
      tmp = tmp->next;
    }
  printf("END LIST\n");
}
