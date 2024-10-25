/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:20:46 by leo               #+#    #+#             */
/*   Updated: 2024/10/25 14:33:28 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <sys/_types/_u_int8_t.h>

void	render_frame(void)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_put_pixel(get_game()->img, x, y, get_game()->map.c_color);
			x++;
		}
		y++;
	}
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_put_pixel(get_game()->img, x, y, get_game()->map.f_color);
			x++;
		}
		y++;
	}
}

void	free_map(void)
{
	int		i;

	i = 0;
	if (get_game()->map.map)
	{
		while (i < get_game()->map.map_height)
			free(get_game()->map.map[i++]);
		free (get_game()->map.map);
	}
}

void	gamma_correct_pixel(uint32_t *pixel)
{
	uint8_t	*p;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	p = (u_int8_t *)pixel;
	r = pow(p[0] / 255.0, 1.0 / 2.2) * 255;
	g = pow(p[1] / 255.0, 1.0 / 2.2) * 255;
	b = pow(p[2] / 255.0, 1.0 / 2.2) * 255;
	p = (uint8_t *)pixel;
	*pixel = (r << 24) | (g << 16) | (b << 8) | p[3];
}

void	gamma_corrected(mlx_texture_t **textures, int num_textures)
{
	int				i;
	mlx_texture_t	*texture;
	uint32_t		*pixels;
	int				y;
	int				x;

	i = 0;
	texture = 0;
	pixels = 0;
	y = 0;
	x = 0;
	while (i < num_textures)
	{
		texture = textures[i];
		pixels = (uint32_t *)texture->pixels;
		y = 0;
		while ((u_int32_t)y < texture->height)
		{
			x = 0;
			while ((u_int32_t)x++ < texture->width)
				gamma_correct_pixel(&pixels[y * texture->width + x]);
			y++;
		}
		i++;
	}
}
