/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:12:03 by leo               #+#    #+#             */
/*   Updated: 2024/10/16 15:22:26 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void 			init_textures(void)
// {
// 	tex()->textures[NORTH] = mlx_load_png(get_game()->map.north);
// 	tex()->textures[SOUTH] = mlx_load_png(get_game()->map.south);
// 	tex()->textures[WEST] = mlx_load_png(get_game()->map.west);
// 	tex()->textures[EAST] = mlx_load_png(get_game()->map.east);
// }

void	init_values(void)
{
	ray()->posx = get_game()->player.player_x;
	ray()->posy = get_game()->player.player_y;
	ray()->dirx = -1; //initial direction vector, mabye needs change to get north west south east
	ray()->diry = 0; //same
	ray()->planex = 0;
	ray()->planey = 0.66;
}