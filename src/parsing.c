/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:49:04 by bebuber           #+#    #+#             */
/*   Updated: 2024/10/20 14:40:05 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	save_colors(const char *line, t_map *map)
{
	int		i;
	int		value;
	int		rgb[3];
	int		flag;

	i = 2;
	flag = 0;
	value = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] && flag < 3)
	{
		if (ft_isdigit(line[i]))
			value = value * 10 + (line[i] - '0');
		else if (line[i] == ',' || line[i] == '\n')
			rgb[flag++] = value;
		i++;
	}
	if (*line == 'F')
		map->f_color = (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255);
	else if (*line == 'C')
		map->c_color = (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255);
}

int	save_player_loc(char *line, int i, int n)
{
	if (get_game()->player.player_x == -1)
	{
		get_game()->player.start_dir = line[i];
		get_game()->player.player_x = i;
		get_game()->player.player_y = n;
		return (SUCCESS);
	}
	else
		return (FAIL);
}

void	check_map_helper(char *line, t_map *map, int fd, int n)
{
	int			i;
	static int	width = 0;

	i = -1;
	while (line[++i])
	{
		if (ft_strchr("NSEW", line[i]))
		{
			if (save_player_loc(line, i, n))
				error_exit("Error:Invalid map: only one player is allowed",
					line, fd);
		}
		else if (!ft_strchr("01 \n", line[i]))
			error_exit("Error: Invalid map:", line, fd);
		if (line[i] && i > width)
			width = i;
	}
	map->map_width = width;
}

int	check_map(char	*line, t_map *map, int fd)
{
	int	n;

	n = 0;
	while (line && contains_only(line, "01NSEW \n"))
	{
		check_map_helper(line, map, fd, n);
		if (line[0] != '\n')
			n++;
		line = next_line(line, fd);
	}
	if (line != NULL)
		error_exit("Error: Invalid map: map content should be the last",
			line, fd);
	map->map_height = n;
	return (SUCCESS);
}

int	parse_map(char	*file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (compare_any(line, (char *[]){"NO ", "SO ", "WE ", "EA "}, 4, 3))
			save_textures(line, &get_game()->map);
		else if (compare_any(line, (char *[]){"F ", "C "}, 2, 2))
			save_colors(line, &get_game()->map);
		else if (contains_only(line, "10 \n") && contains_any(line, "10"))
		{
			check_map(line, &get_game()->map, fd);
			break ;
		}
		else if (!contains_only(line, " \n"))
			error_exit("Error: invalid map", line, fd);
		line = next_line(line, fd);
	}
	close (fd);
	return (SUCCESS);
}
