/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aprsing_utils_three.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:34:31 by bebuber           #+#    #+#             */
/*   Updated: 2024/09/12 17:35:59 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	save_texture(const char *line, char *texture)
{
	int	i;

	i = 3;
	while (line[i] == ' ')
		i++;
	texture = ft_strdup(line + i);
}

int	save_textures(const char *line, t_map *map)
{
	if (ft_strncmp(line, "NO ", 3))
		save_texture(line, map->north);
	else if (ft_strncmp(line, "SO ", 3))
		save_texture(line, map->south);
	else if (ft_strncmp(line, "WE ", 3))
		save_texture(line, map->west);
	else if (ft_strncmp(line, "EA ", 3))
		save_texture(line, map->east);
	else
		return (FAIL);
	return (SUCCESS);
}

void	fill_spaces(char *str, int start, int size)
{
	while (start <= size)
	{
		str[start] = ' ';
		start++;
	}
	str[start] = '\0';
}

