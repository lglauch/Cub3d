/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:49:45 by lglauch           #+#    #+#             */
/*   Updated: 2024/09/19 16:12:59 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_map_on_minimap(void)
{
	t_minimap	minimap;
	// char		**map;
	char **map = get_game()->map.map;
	get_game()->map.map = map;
	minimap = get_game()->minimap_var;
	minimap.sx = 0;
	minimap.sy = 0;
	minimap.map_height = get_game()->map.map_height;
	minimap.map_width = get_game()->map.map_width;
	minimap.minimap_height = WIDTH / 6;
	minimap.minimap_width = WIDTH / 6;
	minimap.scale_x = (float)minimap.minimap_width / minimap.map_width;
	minimap.scale_y = (float)minimap.minimap_height / minimap.map_height;
	draw_on_minimap(&minimap, map);
}

void	draw_minimap_border(void)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < WIDTH / 6)
	{
		ft_put_pixel(get_game()->minimap, x, 0, 0x00FFFFFF);
		ft_put_pixel(get_game()->minimap, x, WIDTH / 6 - 1, 0x00FFFFFF);
		x++;
	}
	while (y < WIDTH / 6)
	{
		ft_put_pixel(get_game()->minimap, 0, y, 0x00FFFFFF);
		ft_put_pixel(get_game()->minimap, WIDTH / 6 - 1, y, 0x00FFFFFF);
		y++;
	}
}

void	draw_player_form_minimap(int player_x, int player_y)
{
	ft_put_pixel(get_game()->minimap, player_x, player_y, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x - 2, player_y - 2, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x - 1, player_y - 2, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x, player_y - 2, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x + 1, player_y - 2, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x + 2, player_y - 2, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x - 2, player_y - 1, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x - 1, player_y - 1, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x + 1, player_y - 1, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x + 2, player_y - 1, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x - 2, player_y, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x + 2, player_y, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x - 2, player_y + 1, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x - 1, player_y + 1, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x + 1, player_y + 1, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x + 2, player_y + 1, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x - 2, player_y + 2, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x - 1, player_y + 2, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x, player_y + 2, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x + 1, player_y + 2, 0xFF0000FF);
	ft_put_pixel(get_game()->minimap, player_x + 2, player_y + 2, 0xFF0000FF);
}

void	drawplayer_minimap(void)
{
	int	player_x;
	int	player_y;
	int	counter;

	player_x = get_game()->player.player_x;
	player_y = get_game()->player.player_y;
	counter = 0;
	ft_memset(get_game()->minimap->pixels, 0,
		(get_game()->minimap->height * get_game()->minimap->width) * 4);
	draw_map_on_minimap();
	draw_player_form_minimap(player_x, player_y);
	draw_minimap_border();
}
