/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bounus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozeki <rozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:52:51 by rozeki            #+#    #+#             */
/*   Updated: 2023/03/30 16:52:52 by rozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	get_line_len(char *storage)
{
	int	i;

	if (storage == NULL)
		return (0);
	i = 0;
	while (storage[i] != '\0')
	{
		if (storage[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*read_stock(char *storage, int fd, int *end)
{
	char	*buf;
	char	*new;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (memoryfree(&storage));
	*end = read(fd, buf, BUFFER_SIZE);
	if (*end < 0)
		return (memoryfree(&buf));
	buf[*end] = '\0';
	new = ft_strjoin(storage, buf);
	memoryfree(&buf);
	memoryfree(&storage);
	return (new);
}

char	*get_line_and_update(char **storage, int len)
{
	char	*line;
	char	*temp;
	int		i;

	line = malloc(sizeof(char) * (len + 1));
	if (line == NULL)
		return (memoryfree(storage));
	i = 0;
	while (i < len)
	{
		line[i] = (*storage)[i];
		i++;
	}
	line[len] = '\0';
	temp = *storage;
	*storage = ft_strdup(&temp[len]);
	memoryfree(&temp);
	if (*storage == NULL)
		return (NULL);
	return (line);
}

char	*get_endline(char **storage)
{
	char	*line;

	line = ft_strdup(*storage);
	memoryfree(storage);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*storage[1024];
	int			len;
	int			end[1];

	if (fd < 0 || fd > 1024)
		return (NULL);
	len = get_line_len(storage[fd]);
	*end = 1;
	while (len == 0 && *end != 0)
	{
		storage[fd] = read_stock(storage[fd], fd, end);
		if (storage[fd] == NULL)
			return (memoryfree(&storage[fd]));
		len = get_line_len(storage[fd]);
	}
	line = NULL;
	if (len != 0)
		line = get_line_and_update(&storage[fd], len);
	else if (ft_strlen(storage[fd]) != 0)
		line = get_endline(&storage[fd]);
	if (line == NULL)
		memoryfree(&storage[fd]);
	return (line);
}


#include <stdio.h>
#include <fcntl.h>
int main(void)
{
	int fd;
	int fd2;
	char *str;
	fd = open("./test", O_RDONLY);
	fd2 = open("./test2", O_RDONLY);
	str = get_next_line(fd);
	while (str != NULL)
	{
		printf("%s", str);
		str = get_next_line(fd);
	}
	printf("\n");
	str = get_next_line(fd2);
	while (str != NULL)
	{
		printf("%s", str);
		str = get_next_line(fd2);
	}

	return (0);
}
