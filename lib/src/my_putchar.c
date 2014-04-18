/*
** my_putchar.c for 42sh in /home/guitte_a//dev/42sh/42sh.git/trunk/lib
**
** Made by antoine guittet
** Login   <guitte_a@epitech.net>
**
** Started on  Fri Apr 12 10:45:31 2013 antoine guittet
** Last update Fri Apr 12 10:49:43 2013 antoine guittet
*/

#include <unistd.h>

void	my_putchar(char c)
{
  write(1, &c, 1);
}
