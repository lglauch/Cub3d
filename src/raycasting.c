/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:06:45 by lglauch           #+#    #+#             */
/*   Updated: 2024/10/18 16:49:25 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//https://hackmd.io/@nszl/H1LXByIE2#player-direction-vector-and-camera-vector
//https://github.com/mcombeau/cub3D/blob/main/sources/render/raycasting.c#L95
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
		if (ray()->mapy < 0 || ray()->mapx < 0 || ray()->mapy
			>= get_game()->map.map_height
			|| ray()->mapx >= get_game()->map.map_width)
			break ;
		if (get_game()->map.map[ray()->mapy][ray()->mapx] == '1')
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
		ray()->perpwalldist = (ray()->mapx - ray()->posx
			+ (1 - ray()->stepx) / 2) / ray()->raydirx;
	else
		ray()->perpwalldist = (ray()->mapy - ray()->posy
			+ (1 - ray()->stepy) / 2) / ray()->raydiry;
	ray()->line_height = (int)(HEIGHT / ray()->perpwalldist);
}

void	cast_ray(int x)
{
	ray()->posx = get_game()->player.player_x;
	ray()->posy = get_game()->player.player_y;
	ray()->camerax = 2 * x / (double)WIDTH - 1;
	ray()->raydirx = ray()->dirx + ray()->planex * ray()->camerax;
	ray()->raydiry = ray()->diry + ray()->planey * ray()->camerax;
	ray()->deltadistx = fabs(1 / ray()->raydirx);
	ray()->deltadisty = fabs(1 / ray()->raydiry);
	ray()->mapx = (int)ray()->posx;
	ray()->mapy = (int)ray()->posy;
	do_dda_calc();
	dda_algo();
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
		ray()->wall_dist * ray()->raydiry;
	else
		ray()->wall_x = get_game()->player.player_x + \
		ray()->wall_dist * ray()->raydirx;
	ray()->wall_x -= floor(ray()->wall_x);
}

void	update_texture(int x)
{
	int	tex_x;
	int	tex_y;
	int	color;
	int	y;

	if (tex()->index < 0 || tex()->index >= 4)
	{
		fprintf(stderr, "Error: Texture index out of bounds\n");
		return ;
	}
	tex_x = (int)(ray()->wall_x * (double)tex()->textures[tex()->index]->width);
	if (ray()->side == 0 && ray()->raydirx > 0)
		tex_x = tex()->textures[tex()->index]->width - tex_x - 1;
	if (ray()->side == 1 && ray()->raydiry < 0)
		tex_x = tex()->textures[tex()->index]->width - tex_x - 1;
	if (tex_x < 0 || (uint32_t)tex_x >= tex()->textures[tex()->index]->width)
	{
		fprintf(stderr, "Error: Texture x-coordinate out of bounds\n");
		return ;
	}
	y = ray()->draw_start;
	while (y < ray()->draw_end)
	{
		tex_y = (((y * 256 - HEIGHT * 128 + ray()->line_height * 128) * tex()->textures[tex()->index]->height) / ray()->line_height) / 256;
		if (tex_y < 0 || (uint32_t)tex_y >= tex()->textures[tex()->index]->height)
		{
			fprintf(stderr, "Error: Texture y-coordinate out of bounds\n");
			return ;
		}
		mlx_texture_t *texture = tex()->textures[tex()->index];
		color = ((int *)texture->pixels)[tex()->textures[tex()->index]->width * tex_y + tex_x];
		ft_put_pixel(get_game()->img, x, y, color);
		y++;
	}
}

void	raycasting(void)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		cast_ray(x);
		calculate_line_height();
		update_texture(x);
		x++;
	}
}
