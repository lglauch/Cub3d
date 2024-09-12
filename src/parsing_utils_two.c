/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:09:58 by bebuber           #+#    #+#             */
/*   Updated: 2024/09/12 17:35:19 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	flood_fill(char **map, int x, int y, int max_height)
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	int		max_width;

	max_width = get_game()->map.map_width;
	if (x < 0 || y < 0 || x >= max_width || y >= max_height)
		return (true);
	if (map[y][x] == '1' || map[y][x] == '2')
		return (true);
	if (map[y][x] != '0')
		return (false);
	map[y][x] = '2';
	up = flood_fill(map, x, y - 1, max_height);
	down = flood_fill(map, x, y + 1, max_height);
	left = flood_fill(map, x - 1, y, max_height);
	right = flood_fill(map, x + 1, y, max_height);
	return (up && down && left && right);
}


int	check_textures(t_map *map)
{
	int		fd[4];
	int		n;
	int		i;

	n = 0;
	i = 0;
	fd[0] = open(map->east, O_RDONLY);
	fd[1] = open(map->west, O_RDONLY);
	fd[2] = open(map->north, O_RDONLY);
	fd[3] = open(map->south, O_RDONLY);
	while (i < 4)
	{
		if (fd[i] < 0)
			n = 1;
		else
			close (fd[i]);
		i++;
	}
	return (n);
}

int	check_elements(void)
{
	t_map	*map;

	map = &get_game()->map;
	if (!map->east || !map->west || !map->north || !map->south)
		free_and_exit("Error: Invalid map: no texture files found");
	if (check_textures(map))
		free_and_exit("Error: Invalid map: error opening texture file");
	if (map->f_color == -1 || map->c_color == -1)
		free_and_exit("Error: Invalid map: no color codes found");
	if (get_game()->player.player_x == -1)
		free_and_exit("Error: Invalid map: no player found");
	if (!flood_fill(map->map, get_game()->player.player_x, \
	get_game()->player.player_y, map->map_height))
		free_and_exit("Error: Invalid map: not enclosed by walls");
}

int	save_map_helper(char *line, int fd, char **map)
{
	int	n;

	n = 0;
	while (line && contains_only(line, "01NESW \n"))
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map[n] = (char *)ft_malloc(get_game()->map.map_width + 1);
		if (!map[n])
			return (FAIL);
		ft_strlcpy(map[n], line, ft_strlen(line) + 1);
		fill_spaces(map[n], ft_strlen(line), get_game()->map.map_width);
		line = next_line(line, fd);
		n++;
	}
	map[n] = NULL;
}

int	save_map(char *file)
{
	int			fd;
	char		*line;
	char		**map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putendl_fd("Error: opening file", 2), FAIL);
	line = get_next_line(fd);
	map = (char **)ft_malloc((get_game()->map.map_height * sizeof(char *)) + 1);
	if (!map)
		return (FAIL);
	while (line && !(contains_only(line, "01 \n") && contains_any(line, "01")))
		line = next_line(line, fd);
	if (save_map_helper(line, fd, map))
		return (FAIL);
	if (get_game()->player.player_x > -1 && get_game()->player.player_y > -1)
		map[(int)get_game()->player.player_y][(int)get_game()->player.player_x] \
		= '0';
	get_game()->map.map = map;
	close(fd);
	return (SUCCESS);
}

