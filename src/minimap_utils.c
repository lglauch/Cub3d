/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:42:42 by lglauch           #+#    #+#             */
/*   Updated: 2024/09/19 16:04:16 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_color(char c)
{
	if (c == '1')
		return (0x1A237E);
	else
		return (0x000000);
}

void	set_color(t_minimap *minimap, int x, int y, char **map)
{
	char	tile;

	tile = map[y][x];
	minimap->color = get_color(tile);
}

void	draw_minimap_tile(t_minimap *minimap, int x, int y)
{
	int	draw_x;
	int	draw_y;

	draw_x = 0;
	draw_y = 0;
	minimap->sx = 0;
	while (minimap->sx < minimap->scale_x - 1)
	{
		minimap->sy = 0;
		while (minimap->sy < minimap->scale_y - 1)
		{
			draw_x = (int)(x * minimap->scale_x) + minimap->sx;
			draw_y = (int)(y * minimap->scale_y) + minimap->sy;
			ft_put_pixel(get_game()->minimap, draw_x, draw_y, minimap->color);
			minimap->sy++;
		}
		minimap->sx++;
	}
}

// void	clear_minimap_background(t_minimap *minimap, int clear_color)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	while (y < minimap->minimap_height * minimap->scale_y)
// 	{
// 		while (x < minimap->minimap_width * minimap->scale_x)
// 		{
// 			ft_put_pixel (get_game()->minimap, x, y, clear_color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

void	draw_on_minimap(t_minimap *minimap, char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	// clear_minimap_background(minimap, 0x202020);
	while (y < minimap->map_height)
	{
		x = 0;
		while (x < minimap->map_width)
		{
			set_color(minimap, x, y, map);
			draw_minimap_tile(minimap, x, y);
			x++;
		}
		y++;
	}
}
