/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_three.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:34:31 by bebuber           #+#    #+#             */
/*   Updated: 2024/09/19 15:27:03 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	save_texture(const char *line, char **texture)
{
	int	i;

	i = 3;
	while (line[i] == ' ')
		i++;
	*texture = ft_strtrim(line + i, "\n");
}

int	save_textures(const char *line, t_map *map)
{
	if (!ft_strncmp(line, "NO ", 3))
		save_texture(line, &map->north);
	else if (!ft_strncmp(line, "SO ", 3))
		save_texture(line, &map->south);
	else if (!ft_strncmp(line, "WE ", 3))
		save_texture(line, &map->west);
	else if (!ft_strncmp(line, "EA ", 3))
		save_texture(line, &map->east);
	else
		return (FAIL);
	return (SUCCESS);
}

void	free_and_exit(char *message)
{
	int	i;

	i = 0;
	if (message)
		ft_putendl_fd(message, 2);
	if (get_game()->map.east)
		free (get_game()->map.east);
	if (get_game()->map.west)
		free (get_game()->map.west);
	if (get_game()->map.south)
		free (get_game()->map.south);
	if (get_game()->map.north)
		free (get_game()->map.north);
	if (get_game()->map.map)
	{
		while (i < get_game()->map.map_height)
			free(get_game()->map.map[i++]);
		free (get_game()->map.map);
	}
	exit (FAIL);
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
