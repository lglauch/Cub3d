/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:49:45 by lglauch           #+#    #+#             */
/*   Updated: 2024/09/05 15:38:19 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_map_on_minimap(void)
{
	t_minimap	minimap;
	// char		**map;

    char *map[] = {
        "11111111111111111111111111",
        "10000000000000000000000001",
        "10000000010000000000000001",
		"10000000010000000000000001",
		"10000000011110000011100001",
		"10000000000001000000000001",
		"10000000000001000011100001",
		"10000000000001000011100001",
		"10000000000000000000000001",
		"11111111111111111111111111",
        NULL
    };
	minimap = get_game()->minimap_var;
	minimap.sx = 0;
	minimap.sy = 0;
	minimap.map_height = sizeof(map) / sizeof(map[0]) - 1;
	minimap.map_width = ft_strlen(map[0]);
	minimap.minimap_height = WIDTH / 6;
	minimap.minimap_width = WIDTH / 6;
	minimap.scale_x = (float)minimap.minimap_width / minimap.map_width;
	minimap.scale_y = (float)minimap.minimap_height / minimap.map_height;
	draw_on_minimap(&minimap, map);
}

void	draw_minimap_border(void)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < WIDTH / 6)
	{
		ft_put_pixel(get_game()->minimap, x, 0, 0x00FFFFFF);
		ft_put_pixel(get_game()->minimap, x, WIDTH / 6 - 1, 0x00FFFFFF);
		x++;
	}
	while (y < WIDTH / 6)
	{
		ft_put_pixel(get_game()->minimap, 0, y, 0x00FFFFFF);
		ft_put_pixel(get_game()->minimap, WIDTH / 6 - 1, y, 0x00FFFFFF);
		y++;
	}
}

void	draw_player_form_minimap(int player_x, int player_y, int counter)
{
	while (true)
	{
		ft_put_pixel(get_game()->minimap, player_x + counter,
			player_y - counter, 0xFF0000FF);
		counter++;
		if (counter > 5)
			break ;
	}
	counter = 0;
	while (true)
	{
		ft_put_pixel(get_game()->minimap, player_x - counter,
			player_y - counter, 0xFF0000FF);
		counter++;
		if (counter > 5)
			break ;
	}
}

void	drawplayer_minimap(void)
{
	int	player_x;
	int	player_y;
	int	counter;

	player_x = get_game()->player.player_x;
	player_y = get_game()->player.player_y;
	counter = 0;
	ft_memset(get_game()->minimap->pixels, 0,
		(get_game()->minimap->height * get_game()->minimap->width) * 4);
	draw_map_on_minimap();
	draw_player_form_minimap(player_x, player_y, counter);
	draw_minimap_border();
}

void	player_movement(void)
{
	void	*param;

	param = get_game()->mlx;
	if (mlx_is_key_down(param, MLX_KEY_W) && get_game()->player.player_y > 0)
		get_game()->player.player_y--;
	if (mlx_is_key_down(param, MLX_KEY_S) && get_game()->player.player_y + 1
		< get_game()->minimap->height)
		get_game()->player.player_y++;
	if (mlx_is_key_down(param, MLX_KEY_A) && get_game()->player.player_x > 0)
		get_game()->player.player_x--;
	if (mlx_is_key_down(param, MLX_KEY_D) && get_game()->player.player_x + 1
		< get_game()->minimap->width)
		get_game()->player.player_x++;
}
