/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:49:45 by lglauch           #+#    #+#             */
/*   Updated: 2024/09/04 14:31:16 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_player_form(int player_x, int player_y, int counter)
{
	while (true)
	{
		ft_put_pixel(get_game()->minimap, player_x + counter,
			player_y - counter, 0xFF023560);
		counter++;
		if (counter > 5)
			break ;
	}
	counter = 0;
	while (true)
	{
		ft_put_pixel(get_game()->minimap, player_x - counter,
			player_y - counter, 0xFF023560);
		counter++;
		if (counter > 5)
			break ;
	}
}

void	drawplayer(void)
{
	int	player_x;
	int	player_y;
	int	counter;

	player_x = get_game()->player.player_x;
	player_y = get_game()->player.player_y;
	counter = 0;
	ft_memset(get_game()->minimap->pixels, 0,
		(get_game()->minimap->height * get_game()->minimap->width) * 4);
	draw_player_form(player_x, player_y, counter);
}

void	player_movement(void)
{
	void	*param;

	param = get_game()->mlx;
	if (mlx_is_key_down(param, MLX_KEY_W) && get_game()->player.player_y > 0)
		get_game()->player.player_y--;
	if (mlx_is_key_down(param, MLX_KEY_S) && get_game()->player.player_y + 1
		< get_game()->img->height)
		get_game()->player.player_y++;
	if (mlx_is_key_down(param, MLX_KEY_A) && get_game()->player.player_x > 0)
		get_game()->player.player_x--;
	if (mlx_is_key_down(param, MLX_KEY_D) && get_game()->player.player_x + 1
		< get_game()->img->width)
		get_game()->player.player_x++;
}
