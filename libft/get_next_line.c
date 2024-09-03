/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:49:31 by bebuber           #+#    #+#             */
/*   Updated: 2024/06/05 14:58:39 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_line(char *storage)
{
	char	*str;
	int		i;

	i = 0;
	if (storage[0] == '\0')
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		str = (char *)ft_calloc ((i + 2), sizeof(char));
	else
		str = (char *)ft_calloc ((i + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	if (storage[i] == '\n')
		str[i + 1] = '\0';
	while (i >= 0)
	{
		str[i] = storage[i];
		i--;
	}
	return (str);
}

char	*ft_cut_line_out(char *storage)
{
	int	i;
	int	j;

	i = 0;
	while (storage[i] && storage[i] != '\n' )
		i++;
	j = 0;
	while (storage[i])
		storage[j++] = storage[++i];
	storage[j] = '\0';
	return (storage);
}

char	*ft_read_into_storage(int fd, char *storage)
{
	int		byts_read;
	char	buff[BUFFER_SIZE + 1];

	if (storage == NULL)
	{
		storage = (char *)ft_calloc(1, sizeof(char));
		if (storage == NULL)
			return (NULL);
		storage[0] = '\0';
	}
	byts_read = 1;
	while (byts_read > 0)
	{
		byts_read = read (fd, buff, BUFFER_SIZE);
		if (byts_read < 0)
		{
			free (storage);
			return (NULL);
		}
		buff[byts_read] = '\0';
		storage = ft_strjoin(storage, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX || read(fd, 0, 0) < 0)
	{
		free (storage[fd]);
		storage[fd] = NULL;
		return (NULL);
	}
	storage[fd] = ft_read_into_storage (fd, storage[fd]);
	if (storage[fd] == NULL)
		return (NULL);
	line = ft_get_line(storage[fd]);
	if (line == NULL || storage[fd][0] == '\0' || storage[fd] == NULL)
	{
		free (storage[fd]);
		storage[fd] = NULL;
		return (NULL);
	}
	storage[fd] = ft_cut_line_out(storage[fd]);
	return (line);
}
