/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:12:50 by aproust           #+#    #+#             */
/*   Updated: 2022/12/13 15:17:19 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*apply_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[0])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*ft_backup(char *str)
{
	int		i;
	int		j;
	char	*backup;

	i = 0;
	j = 0;
	if (!str[0])
		return (free(str), NULL);
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	backup = ft_calloc(ft_strlen(str) - i + 1, sizeof(char));
	if (!backup)
		return (NULL);
	while (str[i])
		backup[j++] = str[i++];
	free(str);
	return (backup);
}

char	*get_next_line_final(int fd, char *str[fd])
{
	char	*res;

	res = apply_line(str[fd]);
	if (!(res))
	{
		if (!str[fd])
			return (free(str[fd]), NULL);
	}
	str[fd] = ft_backup(str[fd]);
	if (!(str[fd]))
		return (free(str[fd]), NULL);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*str[4096];
	char		*buffer;
	int			i;
	char		*res;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	i = 1;
	while (i && !ft_strchr(buffer, '\n'))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
			return (free(buffer), NULL);
		buffer[i] = '\0';
		str[fd] = ft_strjoin(str[fd], buffer);
		if (!(str[fd]))
			return (free(buffer), NULL);
	}
	res = get_next_line_final(fd, str);
	return (free(buffer), res);
}

// int main (void)
// {
// 	int	fd;

// 	fd = open("test", O_RDONLY);
// 	char *str;

// 	// str  = get_next_line(fd);
// 	// printf("%s", str);
// 	// free(str);
// 	while ((str = get_next_line(fd)))
// 	{
// 		printf("%s", str);
// 		free(str);
// 	}
// }
