/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:09:58 by bebuber           #+#    #+#             */
/*   Updated: 2024/09/11 17:41:34 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	fill_spaces(char *str, int start, int size)
{
	while (start <= size)
	{
		str[start] = ' ';
		start++;
	}
	str[start] = '\0';
}

bool	flood_fill(char **map, int x, int y, int max_height)
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	int		max_width;

	max_width = get_game()->map.map_width;
	if (x < 0 || y < 0)
		return (true);
	if (x >= max_width || y >= max_width)
		return (false);
	if (map[y][x] == '1' || map[y][x] == '2' || map[y][x] == ' ')
		return (true);
	map[y][x] = 2;
	up = flood_fill(map, x, y - 1, max_height);
	down = flood_fill(map, x, y + 1, max_height);
	left = flood_fill(map, x - 1, y, max_height);
	right = flood_fill(map, x + 1, y, max_height);
	return (up && down && left && right);
}

void	save_map(char *file, t_map *game)
{
	int			fd;
	int			n;
	char		*line;
	char		**map;
	t_player	hans;

	n = 0;
	hans = get_game()->player;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	map = (char **)ft_malloc(game->map_height * sizeof(char *) + 1);
	while (line && contains_only(line, "01 \n") == false)
		line = next_line(line, fd);
	while (line && contains_only(line, "01 \n") == true)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map[n] = (char *)ft_malloc(game->map_width * sizeof(char) + 1);
		map[n] = ft_strdup(line);
		fill_spaces(map[n], ft_strlen(line), game->map_width);
		line = next_line(line, fd);
		n++;
	}
	map[n] = NULL;
	if (hans.player_x > 0 && hans.player_y > 0)
		map[(int)hans.player_y][(int)hans.player_x] = '0';
	game->map = map;
}
