/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:06:45 by lglauch           #+#    #+#             */
/*   Updated: 2024/09/19 16:17:32 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void draw_line(float x0, float y0, float x1, float y1) {
//     int steps;
//     float stepX, stepY;
//     float x, y;
//     int i;

//     // Calculate the difference in both directions
//     float dx = x1 - x0;
//     float dy = y1 - y0;

//     // Determine the number of steps to take
//     steps = fmax(fabs(dx), fabs(dy));
//     stepX = dx / (float)steps;
//     stepY = dy / (float)steps;

//     x = x0;
//     y = y0;
//     for (i = 0; i <= steps; i++) {
//         ft_put_pixel(get_game()->minimap, round(x), round(y), 0xFFFFFF);

//         x += stepX;
//         y += stepY;
//     }
// }

//https://hackmd.io/@nszl/H1LXByIE2#player-direction-vector-and-camera-vector

void	init_values(void)
{
	ray()->posx = get_game()->player.player_x;
	ray()->posy = get_game()->player.player_y;
	ray()->dirx = -1; //initial direction vector, mabye needs change to get north west south east
	ray()->diry = 0; //same
	ray()->planex = 0;
	ray()->planey = 0.66;
}

void	cast_ray(void)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		ray()->camerax = 2 * x / (double)WIDTH - 1;
		ray()->raydirx = ray()->dirx + ray()->planex * ray()->camerax;
		ray()->raydiry = ray()->diry + ray()->planey * ray()->camerax;
		x++;
	}
	ray()->deltadistx = abs(1 / ray()->raydirx);
	ray()->deltadisty = abs(1 / ray()->raydiry);
	if (ray()->deltadistx == 0)
		ray()->deltadistx = 1e30;
	if (ray()->deltadisty == 0)
		ray()->deltadisty = 1e30;
	ray()->mapx = (int)ray()->posx;
	ray()->mapy = (int)ray()->posy;
}

void	calc_step_sidedist(void)
{
	static	int	stepx;
	static	int	stepy;
	static	int	hit;
	static	int	side;

	do_calc(&stepx, &stepy, &hit, &side);//correct?
}

void	do_calc(int stepx, int stepy, int hit, int side)
{
	if (ray()->raydirx < 0)
	{
		stepx = -1;
		ray()->sidedistx = (ray()->posx - ray()->mapx) * ray()->deltadistx;
	}
	else
	{
		stepx = 1;
		ray()->sidedistx = (ray()->mapx + 1.0 - ray()->posx) * ray()->deltadistx;
	}
	if (ray()->raydiry < 0)
	{
		stepy = -1;
		ray()->sidedisty = (ray()->posy - ray()->mapy) * ray()->deltadisty;
	}
	else
	{
		stepy = 1;
		ray()->sidedisty = (ray()->mapy + 1.0 - ray()->posy) * ray()->deltadisty;
	}
	dda_algo(&stepx, &stepy, &hit, &side);
}

void	dda_algo(int stepx, int stepy, int hit, int side)
{
	while (hit == 0)
	{
		if (ray()->sidedistx < ray()->sidedisty)
		{
			ray()->sidedistx += ray()->deltadistx;
			ray()->mapx += stepx;
			side = 0;
		}
		else
		{
			ray()->sidedisty += ray()->deltadisty;
			ray()->mapy += stepy;
			side = 1;
		}
		if (get_game()->map.map[ray()->mapx][ray()->mapy] > 0)//if not working change x and y
			hit = 1;
	}
	if (side == 0)
		ray()->perpwalldist = (ray()->sidedistx - ray()->deltadistx);
	else
		ray()->perpwalldist = (ray()->sidedisty - ray()->deltadisty);
}

void	raycasting(void)
{
	init_values();
	cast_ray();
	calc_step_sidedist();
	if (get_game()->map.west || get_game()->map.east)
		ray()->wall_x = get_game()->player.player_y + ray()->perpwalldist * ray()->raydiry;
	else
		ray()->wall_x = get_game()->player.player_x + ray()->perpwalldist * ray()->raydirx;
	ray()->wall_x -= floor(ray()->wall_x);
	line()->x = ray()->
}
