
#include	<stdlib.h>
#include	"lexer.h"
#include	"token.h"
#include	"tree.h"
#include	"node.h"
#include	"parser.h"
#include	"epur_str.h"

static int	parser_append(t_parsedline **list, t_token *token, t_node *tree)
{
  t_parsedline	*new;
  t_parsedline	*iterator;

  if (list == NULL || token == NULL || tree == NULL)
    return (EXIT_FAILURE);
  if ((new = malloc(sizeof(*new))) == NULL)
    return (EXIT_FAILURE);
  new->next = NULL;
  if (*list == NULL)
    *list = new;
  else
    {
      iterator = *list;
      while (iterator->next != NULL)
	iterator = iterator->next;
      iterator->next = new;
    }
  new->tree = tree;
  new->tokenlist = token;
  return (EXIT_SUCCESS);
}

int	parser_free_line(t_parsedline *lines)
{
  if (lines == NULL)
    return (EXIT_FAILURE);
  if (lines->next != NULL)
    parser_free_line(lines->next);
  free(lines);
  return (EXIT_SUCCESS);
}

static t_parsedline	*free_str(char *str)
{
  free(str);
  return (NULL);
}

t_parsedline	*parser(char *str, t_shell *sh, int opt)
{
  t_token	*list;
  t_token	*iterator;
  t_node	*tree;
  t_parsedline	*lines;

  if (str == NULL || ((str = clean_tab(str)) == NULL))
    return (NULL);
  if (str[0] == '\0')
    return (free_str(str));
  if ((list = lexer(str, sh, opt)) == NULL)
    return (free_str(str));
  iterator = list;
  lines = NULL;
  while (iterator != NULL)
    {
      if ((tree = tree_build(iterator->value.list)) == NULL)
	return (free_str(str));
      parser_append(&lines, iterator->value.list, tree);
      iterator->value.list = NULL;
      iterator = iterator->next;
    }
  token_delete_list(list);
  free(str);
  return (lines);
}
