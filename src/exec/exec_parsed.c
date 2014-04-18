
#include	<stdlib.h>
#include	<signal.h>
#include	<unistd.h>
#include	"exec.h"
#include	"tree.h"
#include	"token.h"
#include	"tokeniser.h"
#include	"parser.h"
#include	"job_control.h"
#include	"exec_parsed.h"

int	exec_parsed_free(t_parsedline *exec)
{
  if (exec == NULL)
    return (EXIT_FAILURE);
  if (exec->next != NULL)
    exec_parsed_free(exec->next);
  free(exec);
  return (EXIT_SUCCESS);
}

int	exec_parsed(t_parsedline *exec, t_shell *sh)
{
  while (exec != NULL)
    {
      sh->process_group = 0;
      exec_tree(exec->tree, sh);
      tree_free(exec->tree);
      token_delete_list(exec->tokenlist);
      exec = exec->next;
    }
  tcsetpgrp(0, getpgrp());
  signal(SIGTTIN, SIG_DFL);
  signal(SIGTTOU, SIG_DFL);
  return (EXIT_SUCCESS);
}
