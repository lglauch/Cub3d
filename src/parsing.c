/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:49:04 by bebuber           #+#    #+#             */
/*   Updated: 2024/09/11 17:47:34 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	save_colors(const char *line, t_map *map)
{
	int		i;
	int		color;
	int		value;

	i = 2;
	color = 0;
	value = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] && color < 3)
	{
		if (ft_isdigit(line[i]))
			value = value * 10 + (line[i] - '0');
		else if (line[i] == ',' || line[i + 1] == '\n')
		{
			color = (color << 8) + value;
			value = 0;
		}
		i++;
	}
	if (*line == 'F')
		map->f_color = color;
	else if (*line == 'C')
		map->c_color = color;
}

int	save_player_loc(char *line, int i, int n)
{
	if (get_game()->player.player_x == -1)
	{
		get_game()->player.start_dir = line[i];
		get_game()->player.player_x = i;
		get_game()->player.player_y = n;
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}

int	check_map(char	*line, t_map *map, int fd)
{
	int	width;
	int	i;
	int	n;

	i = 0;
	n = 0;
	width = 0;
	while (line && contains_only(line, "01 \n"))
	{
		i = -1;
		while (line[++i])
		{
			if (ft_strchr("NSEW", line[i]) && save_player_loc(line, i, n))
				error_exit("Error: only one player is allowed", line, fd);
			else if (!ft_strchr("01 \n", line[i]))
				error_exit("Error: invalid map", line, fd);
			if (line[i] && i > width)
				width = i;
		}
		if (line[0] != '\n')
			n++;
		line = next_line(line, fd);
	}
	if (line != NULL)
		error_exit("Error: invalid map", line, fd);
	map->map_height = n;
	map->map_width = width;
	free (line);
	close (fd);
	return (EXIT_SUCCESS);
}

int	parse_map(char	*file)
{
	int		fd;
	char	*line;
	char	**map;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (compare_any(line, (char *[]){"NO ", "SO ", "WE ", "EA "}, 4, 3))
			save_textures(line, &get_game()->map);
		else if (compare_any(line, (char *[]){"F ", "C "}, 2, 2))
			save_colors(line, &get_game()->map);
		else if (contains_only(line, "10 \n"))
		{
			check_map(line, &get_game()->map, fd);
			save_map(file, &get_game()->map);
			break ;
		}
		else if (!contains_only(line, " \n"))
			error_exit("Error: invalid map", line, fd);
		line = next_line(line, fd);
	}
	map = get_game()->map.map;
	printf("--------------\n");
	print_map(get_game()->map.map);
	close (fd);
	if (!flood_fill(map, get_game()->player.player_x, \
	get_game()->player.player_y, get_game()->map.map_height))
		return (perror("Error: invalid map"), FAIL);
	return (EXIT_SUCCESS);
}
