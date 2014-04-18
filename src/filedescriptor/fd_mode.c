/*
** fd_mode.c for  in /home/lelabo_m//LOCAL/Projet/42.sh/42sh-2017-creach_a/src/filedescriptor
**
** Made by marc lelabourier
** Login   <lelabo_m@epitech.net>
**
** Started on  Sat May 11 21:57:28 2013 marc lelabourier
** Last update Sat May 11 21:59:34 2013 marc lelabourier
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "fd_check.h"

t_fdtype	fd_is_reg(mode_t mode)
{
  if (S_ISREG(mode))
    return (REG);
  return (UNKNOW);
}

t_fdtype	fd_is_dir(mode_t mode)
{
  if (S_ISDIR(mode))
    return (DIR);
  return (UNKNOW);
}

t_fdtype	fd_is_chr(mode_t mode)
{
  if (S_ISCHR(mode))
    return (CHR);
  return (UNKNOW);
}

t_fdtype	fd_is_blk(mode_t mode)
{
  if (S_ISBLK(mode))
    return (BLK);
  return (UNKNOW);
}

t_fdtype	fd_is_fifo(mode_t mode)
{
  if (S_ISFIFO(mode))
    return (FIFO);
  return (UNKNOW);
}
