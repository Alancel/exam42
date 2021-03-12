#include "get_next_line.h"

int ft_strlen(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

char *ft_strjoin(char *remainder, char *buf)
{
	int i;
	int j;
	unsigned int len;
	char *str;

	i = 0;
	j = 0;
	if (!remainder && !buf)
		return (NULL);
	len = ft_strlen(remainder) + ft_strlen(buf);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (remainder)
	{
		while(remainder[i])
		{
			str[i] = remainder[i];
			i++;
		}
	}
	while (buf[j])
	{
		str[i] = buf[j];
		i++;
		j++;
	}
	str[len] = '\0';
	free((void*)remainder);
	return(str);
}

char *push_line(char *remainder)
{
	int i;
	char *str;

	i = 0;
	while (remainder[i] && remainder [i] != '\n')
		i++;
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (remainder[i] && remainder [i] != '\n')
	{
		str[i] = remainder[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char *cut_line(char *remainder)
{
	int i;
	int j;
	char *str;

	i = 0;
	j = 0;
	while (remainder[i] && remainder [i] != '\n')
		i++;
	if (!remainder[i])
	{
		free(remainder);
		return (NULL);
	}
	if (!(str = (char*)malloc(sizeof(char) * (ft_strlen(remainder) - i + 1))))
		return (NULL);
	while (remainder[++i])
	{
		str[j] = remainder[i];
		j++;
	}
	str[j] = '\0';
	free(remainder);
	return (str);
}

int get_next_line(char **line)
{
	int res, fd;
	static char *remainder;
	char buf[BUFFER_SIZE + 1];

	fd = 0;
	res = 1;
	if (!line)
		return (-1);
	while (buf[0] != '\n' && res != 0)
	{
		if((res = read(fd, buf, BUFFER_SIZE)) == (-1))
			return (-1);
		buf[res] = '\0';
		remainder = ft_strjoin(remainder, buf);
	}
	*line = push_line(remainder);
	remainder = cut_line(remainder);
	return ((res == 0) ? 0 : 1);
}
