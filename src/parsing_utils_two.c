/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:09:58 by bebuber           #+#    #+#             */
/*   Updated: 2024/09/05 15:15:09 by bebuber          ###   ########.fr       */
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

int	flood_fill(char **map, int x, int y, int max_height)
{
	int	row_length;

	if (y < 0 || y >= max_height || map[y] == NULL)
		return ;
	row_length = ft_strlen(map[y]);
	if (x < 0 || x >= row_length || map[y][x] == '1')
		return ;
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (EXIT_FAILURE);
	map[y][x] =
	flood_fill(map, x + 1, y, max_height);
	flood_fill(map, x - 1, y, max_height);
	flood_fill(map, x, y + 1, max_height);
	flood_fill(map, x, y - 1, max_height);
}

void	save_map(char *file, t_map game)
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
	map = (char *)ft_malloc(game.map_height * sizeof(char *) + 1);
	while (line && !contains_any(line, (const char *[]){"1", "0"}, 2))
		line = next_line(line, fd);
	while (line && contains_any(line, (const char *[]){"1", "0"}, 2))
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map[n] = (char)ft_malloc(game.map_width * sizeof(char) + 1);
		map[n] = ft_strdup(line);
		fill_spaces(map[n], ft_strlen(line), game.map_width);
		line = next_line(line, fd);
	}
	map[n] = NULL;
	map[(int)hans.player_y][(int)hans.player_x] = '0';
	game.map = map;
}
