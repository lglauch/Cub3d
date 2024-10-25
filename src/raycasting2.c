/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:12:03 by lglauch           #+#    #+#             */
/*   Updated: 2024/10/25 14:30:30 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_direction(void)
{
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
			+ (float)(1 - ray()->stepx) / 2) / ray()->raydirx;
	else
		ray()->perpwalldist = (ray()->mapy - ray()->posy
			+ (float)(1 - ray()->stepy) / 2) / ray()->raydiry;
	ray()->line_height = (int)(HEIGHT / ray()->perpwalldist);
}

void	put_texture(int tex_y, int color, int x, int tex_x)
{
	mlx_texture_t	*texture;
	int				y;

	y = ray()->draw_start;
	texture = tex()->textures[tex()->index];
	while (y < ray()->draw_end)
	{
		tex_y = (((y * 256 - HEIGHT * 128 + ray()->line_height * 128)
					* tex()->textures[tex()->index]->height)
				/ ray()->line_height) / 256;
		if (tex_y < 0 || (uint32_t)tex_y
			>= tex()->textures[tex()->index]->height)
		{
			fprintf(stderr, "Error: Texture y-coordinate out of bounds\n");
			return ;
		}
		color = ((int *)texture->pixels)[tex()->textures[tex()->index]->width
			* tex_y + tex_x];
		ft_put_pixel(get_game()->img, x, y, color);
		y++;
	}
}

void	update_texture(int x)
{
	int	tex_x;
	int	tex_y;
	int	color;

	tex_y = 0;
	color = 0;
	if (tex()->index < 0 || tex()->index >= 4)
		return ;
	tex_x = (int)(ray()->wall_x * (double)tex()->textures[tex()->index]->width);
	if (ray()->side == 0 && ray()->raydirx > 0)
		tex_x = tex()->textures[tex()->index]->width - tex_x - 1;
	if (ray()->side == 1 && ray()->raydiry < 0)
		tex_x = tex()->textures[tex()->index]->width - tex_x - 1;
	if (tex_x < 0 || (uint32_t)tex_x >= tex()->textures[tex()->index]->width)
		return ;
	put_texture(tex_y, color, x, tex_x);
}
