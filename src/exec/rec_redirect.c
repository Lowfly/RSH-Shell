/*
** rec_redirect.c for 42sh in /home/roche_d//projets/42sh-2017-creach_a
** 
** Made by clement roche
** Login   <roche_d@epitech.net>
** 
** Started on  Sun May 26 19:28:57 2013 clement roche
** Last update Sun May 26 20:05:28 2013 clement roche
*/

#include	<stdlib.h>
#include	"token.h"
#include	"node.h"
#include	"shell.h"
#include	"redirect.h"

static void     init_tab(t_ntype types[], int (*func[])(t_node *, t_shell *))
{
  types[0] = node_redirect_r;
  types[1] = node_redirect_dr;
  types[2] = node_redirect_l;
  types[3] = node_redirect_dl;
  func[0] = &redirect_right;
  func[1] = &redirect_double_right;
  func[2] = &redirect_left;
  func[3] = &redirect_double_left;
}

int		rec_redirect(t_node *this, t_shell *sh)
{
  int		(*func[4])(t_node *, t_shell *);
  t_ntype	types[4];
  int		i;

  if (this == NULL || this->right == NULL || this->pid == 0)
    return (EXIT_SUCCESS);
  init_tab(types, func);
  i = 0;
  this->right->in = this->in;
  this->right->out = this->out;
  while (i < 4)
    {
      if (this->right->type == types[i])
	{
	  (func[i])(this->right, sh);
	  this->in = this->right->in;
	  this->out = this->right->out;
	  return (EXIT_SUCCESS);
	}
      i++;
    }
  return (EXIT_SUCCESS);
}
