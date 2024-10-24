/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:05:13 by bebuber           #+#    #+#             */
/*   Updated: 2024/10/24 14:16:24 by leo              ###   ########.fr       */
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

bool	contains_any(const char *str, const char *chars)
{
	while (*str)
	{
		if (ft_strchr(chars, *str))
			return (true);
		str++;
	}
	return (false);
}

char	*next_line(char *line, int fd)
{
	free (line);
	line = get_next_line(fd);
	return (line);
}

void	error_exit(char *message, char *line, int fd)
{
	free_textures(tex()->textures);
	free_map();
	free_tex_path();
	if (get_game()->img)
		mlx_terminate(get_game()->mlx);
	free (line);
	close (fd);
	ft_putendl_fd(message, 2);
	exit (1);
}
