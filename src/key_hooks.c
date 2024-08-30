/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:37:26 by lglauch           #+#    #+#             */
/*   Updated: 2024/08/30 13:23:44 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	create_key_hooks(void)
{
	void	*param;

	param = NULL;
	mlx_key_hook(get_game()->mlx, esc_func, param);
	mlx_close_hook(get_game()->mlx, close_func, param);
}
