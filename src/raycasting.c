/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:06:45 by lglauch           #+#    #+#             */
/*   Updated: 2024/10/17 00:42:40 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//https://hackmd.io/@nszl/H1LXByIE2#player-direction-vector-and-camera-vector
//https://github.com/mcombeau/cub3D/blob/main/sources/render/raycasting.c#L95

void	cast_ray(int x)
{
	init_values();
	ray()->camerax = 2 * x / (double)WIDTH - 1;
	printf("Before calculation: dirx=%f, diry=%f, planex=%f, planey=%f, camerax=%f\n", ray()->dirx, ray()->diry, ray()->planex, ray()->planey, ray()->camerax);
	ray()->raydirx = ray()->dirx + ray()->planex * ray()->camerax;
	ray()->raydiry = ray()->diry + ray()->planey * ray()->camerax;
	ray()->deltadistx = fabs(1 / ray()->raydirx);
	ray()->deltadisty = fabs(1 / ray()->raydiry);
	// if (ray()->deltadistx == 0)
	// 	ray()->deltadistx = 1e30;
	// if (ray()->deltadisty == 0)
	// 	ray()->deltadisty = 1e30;
	ray()->mapx = (int)ray()->posx;
	ray()->mapy = (int)ray()->posy;
	printf("cast_ray: x=%d, camerax=%f, raydirx=%f, raydiry=%f\n", x, ray()->camerax, ray()->raydirx, ray()->raydiry);
}

void	do_dda_calc(void)
{
	if (ray()->raydirx < 0)
	{
		ray()->stepx = -1;
		ray()->sidedistx = (ray()->posx - ray()->mapx) * ray()->deltadistx;
	}
	else
	{
		ray()->stepx = 1;
		ray()->sidedistx = (ray()->mapx + 1.0 - ray()->posx) \
		* ray()->deltadistx;
	}
	if (ray()->raydiry < 0)
	{
		ray()->stepy = -1;
		ray()->sidedisty = (ray()->posy - ray()->mapy) * ray()->deltadisty;
	}
	else
	{
		ray()->stepy = 1;
		ray()->sidedisty = (ray()->mapy + 1.0 - ray()->posy) \
		* ray()->deltadisty;
	}
}

void	dda_algo(void)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray()->sidedistx < ray()->sidedisty)
		{
			ray()->sidedistx += ray()->deltadistx;
			ray()->mapx += ray()->stepx;
			ray()->side = 0;
		}
		else
		{
			ray()->sidedisty += ray()->deltadisty;
			ray()->mapy += ray()->stepy;
			ray()->side = 1;
		}
		if (ray()->mapy < 0.25 || ray()->mapx < 0.25
			|| ray()->mapy > get_game()->map.map_height - 0.25
			|| ray()->mapx > get_game()->map.map_width - 1.25)
			break ;
		else if (get_game()->map.map[ray()->mapy][ray()->mapx] > '0')
			hit = 1;
	}
	if (ray()->side == 0)
    {
        if (ray()->raydirx > 0)
            tex()->index = EAST;
        else
            tex()->index = WEST;
    }
    else
    {
        if (ray()->raydiry > 0)
            tex()->index = SOUTH;
        else
            tex()->index = NORTH;
    }
	if (ray()->side == 0)
        ray()->perpwalldist = (ray()->mapx - ray()->posx + (1 - ray()->stepx) / 2) / ray()->raydirx;
    else
        ray()->perpwalldist = (ray()->mapy - ray()->posy + (1 - ray()->stepy) / 2) / ray()->raydiry;
    ray()->line_height = (int)(HEIGHT / ray()->perpwalldist);
}

void	calculate_line_height(void)
{
	if (ray()->side == 0)
		ray()->wall_dist = (ray()->sidedistx - ray()->deltadistx);
	else
		ray()->wall_dist = (ray()->sidedisty - ray()->deltadisty);
	ray()->line_height = ((int)HEIGHT / ray()->wall_dist);
	ray()->draw_start = -(ray()->line_height) / 2 + HEIGHT / 2;
	if (ray()->draw_start < 0)
		ray()->draw_start = 0;
	ray()->draw_end = ray()->line_height / 2 + HEIGHT / 2;
	if (ray()->draw_end >= HEIGHT)
		ray()->draw_end = HEIGHT - 1;
	if (ray()->side == 0)
		ray()->wall_x = get_game()->player.player_y + \
		ray()->wall_dist * ray()->diry;
	else
		ray()->wall_x = get_game()->player.player_x + \
		ray()->wall_dist * ray()->dirx;
	ray()->wall_x -= floor(ray()->wall_x);
}

void	raycasting(void)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		cast_ray(x);
		do_dda_calc();
		dda_algo();
		calculate_line_height();
		update_texture(x);
		x++;
	}
}