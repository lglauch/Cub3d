/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:05:13 by bebuber           #+#    #+#             */
/*   Updated: 2024/09/11 16:58:13 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	compare_any(const char *str, char *substr[], int num_str, int n)
{
	int	i;

	i = 0;
	while (i < num_str)
	{
		if (!ft_strncmp(str, substr[i], n))
			return (true);
		i++;
	}
	return (false);
}

bool	contains_only(const char *str, const char *allowedchars)
{
	while (*str)
	{
		if (ft_strchr(allowedchars, *str) == NULL)
			return (false);
		str++;
	}
	return (true);
}

char	*next_line(char *line, int fd)
{
	free (line);
	line = get_next_line(fd);
	return (line);
}

void	save_texture(const char *line, char *texture)
{
	int	i;

	i = 3;
	while (line[i] == ' ')
		i++;
	texture = ft_strdup(line + i);
}

void	error_exit(char *message, char *line, int fd)
{
	free (line);
	close (fd);
	ft_putendl_fd(message, 2);
	printf("hello\n");
	exit (1);
}
