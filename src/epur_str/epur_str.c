
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	count_lenght(char *str)
{
  int	i;
  int	count;

  i = 0;
  count = 0;
  while ((str[i] == ' ' || str[i] == '\t') && str[i])
     i++;
  while (str[i])
    {
      if (str[i] != ' ' && str[i] != '\t')
	{
	  count++;
	  i++;
	}
      else
	{
	  count++;
	  while ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
	    i++;
	}
    }
  if (i > 1 && (str[i - 1] == ' ' || str[i - 1] == '\t'))
    count--;
  return (count + 1);
}

char	*copy_it(char *str, char *newstr, int limit)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while ((str[i] == ' ' || str[i] == '\t') && str[i])
    i++;
  while (str[i] && j < limit)
    {
      if (str[i] != ' ' && str[i] != '\t')
	newstr[j++] = str[i++];
      else
	{
	  newstr[j] = ' ';
	  j++;
	  while ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
	    i++;
	}
    }
  newstr[j] = '\0';
  return (newstr);
}

char	*epur_str(char *str, int option)
{
  char	*newstr;
  int	limit;

  if (str == NULL)
    return (NULL);
  limit = count_lenght(str);
  if (limit != 0)
    {
      if ((newstr = malloc(sizeof(*newstr) * limit)) == NULL)
	{
	  fprintf(stderr, "Failed to allocate memory.\n");
	  return (NULL);
	}
    }
  else
    return (NULL);
  newstr = copy_it(str, newstr, limit - 1);
  if (option == 1)
    free(str);
  return (newstr);
}
