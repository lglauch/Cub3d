/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:42:42 by lglauch           #+#    #+#             */
/*   Updated: 2024/09/05 15:37:02 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_color(char c)
{
	if (c == '1')
		return (0x1A237E);
	else if (c == '0')
		return (0xFFFF00);
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
	while (minimap->sx < minimap->scale_x)
	{
		minimap->sy = 0;
		while (minimap->sy < minimap->scale_y)
		{
			draw_x = (int)(x * minimap->scale_x) + minimap->sx;
			draw_y = (int)(y * minimap->scale_y) + minimap->sy;
			ft_put_pixel(get_game()->minimap, draw_x, draw_y, minimap->color);
			minimap->sy++;
		}
		minimap->sx++;
	}
}

void	draw_on_minimap(t_minimap *minimap, char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
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

