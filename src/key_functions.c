/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:44:09 by lglauch           #+#    #+#             */
/*   Updated: 2024/09/04 12:18:40 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	esc_func(mlx_key_data_t key_data, void *param)
{
	param = NULL;
	if (key_data.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(get_game()->mlx);
		exit (EXIT_SUCCESS);
	}
}

void	close_func(void *param)
{
	param = NULL;
	mlx_terminate(get_game()->mlx);
	exit (EXIT_SUCCESS);
}
