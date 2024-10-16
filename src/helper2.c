/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:12:03 by leo               #+#    #+#             */
/*   Updated: 2024/10/16 15:24:33 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_textures(void)
{
	xpm_t	**textures;

	textures = NULL;
	textures[NORTH] = mlx_load_xpm42(get_game()->map.north);
	textures[SOUTH] = mlx_load_xpm42(get_game()->map.south);
	textures[EAST] = mlx_load_xpm42(get_game()->map.east);
	textures[WEST] = mlx_load_xpm42(get_game()->map.west);
}
