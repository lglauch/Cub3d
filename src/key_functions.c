/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:44:09 by lglauch           #+#    #+#             */
/*   Updated: 2024/10/24 14:09:31 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	esc_func(mlx_key_data_t key_data, void *param)
{
	(void)param;
	if (key_data.key == MLX_KEY_ESCAPE)
	{
		free_textures(tex()->textures);
		free_map();
		free_tex_path();
		mlx_terminate(get_game()->mlx);
		exit (EXIT_SUCCESS);
	}
}

void	close_func(void *param)
{
	(void)param;
	free_textures(tex()->textures);
	free_map();
	free_tex_path();
	mlx_terminate(get_game()->mlx);
	exit (EXIT_SUCCESS);
}
