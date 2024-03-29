/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozeki <rozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:04:22 by rozeki            #+#    #+#             */
/*   Updated: 2023/04/13 15:40:18 by rozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_size(char *storage)
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

char	*get_line_and_update(char **storage, int size)
{
	char	*line;
	char	*temp;
	int		i;

	line = malloc(sizeof(char) * (size + 1));
	if (line == NULL)
		return (memoryfree(storage));
	i = 0;
	while (i < size)
	{
		line[i] = (*storage)[i];
		i++;
	}
	line[size] = '\0';
	temp = *storage;
	*storage = ft_strdup(&temp[size]);
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
	static char	*storage;
	int			size;
	int			end[1];

	if (fd < 0)
		return (NULL);
	size = get_size(storage);
	*end = 1;
	while (size == 0 && *end != 0)
	{
		storage = read_stock(storage, fd, end);
		if (storage == NULL)
			return (memoryfree(&storage));
		size = get_size(storage);
	}
	line = NULL;
	if (size != 0)
		line = get_line_and_update(&storage, size);
	else if (ft_strlen(storage) != 0)
		line = get_endline(&storage);
	if (line == NULL)
		memoryfree(&storage);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>
// int main(void)
// {
// 	int fd;
// 	char *str;
// 	fd = open("./test", O_RDONLY);
// 	str = get_next_line(fd);
// 	while (str != NULL)
// 	{
// 		printf("%s", str);
// 		str = get_next_line(fd);
// 	}
// 	return (0);
// }
