
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static char	*my_free(char *str)
{
  free(str);
  str = NULL;
  return (NULL);
}

char	*read_file(const int fd, char *str, int c, int *x)
{
  static char	buff[SIZE_READ + 1];
  static int	i;
  int		ret;

  ret = 1;
  if (i == 0)
    {
      ret = read(fd, buff, SIZE_READ);
      buff[ret] = '\0';
    }
  while (buff[i] != '\n' && buff[i] != '\0')
    str[c++] = buff[i++];
  str[c] = '\0';
  if (ret == -1 || (ret == 0 && str[0] == '\0'))
    return (my_free(str));
  if (buff[i] == '\n')
    {
      i++;
      *x = 0;
    }
  if (buff[i] == '\0')
    i = 0;
  if (ret == 0)
    *x = 0;
  return (str);
}

char	*find_line(char *str, char *tmp, int x, const int fd)
{
  int	c;

  c = 0;
  while (x != 0)
    {
      x = x + 1;
      c = 0;
      if ((str = malloc(sizeof(*str) * ((SIZE_READ * x) + 1))) == NULL)
	return (NULL);
      while (tmp != NULL && tmp[c] != '\0')
	{
	  str[c] = tmp[c];
	  c++;
	}
      str[c] = '\0';
      if ((str = read_file(fd, str, c, &x)) == NULL)
     	return (NULL);
      free(tmp);
      tmp = str;
    }
  return (str);
}

char	*get_next_line(const int fd)
{
  char		*str;
  char		*tmp;
  int		x;

  tmp = NULL;
  str = NULL;
  x = 1;
  if ((fd < 0) || (SIZE_READ < 1))
    return (NULL);
  str = find_line(str, tmp, x, fd);
  return (str);
}
