/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:20:46 by leo               #+#    #+#             */
/*   Updated: 2024/10/24 14:13:58 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
