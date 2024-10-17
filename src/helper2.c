/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:12:03 by leo               #+#    #+#             */
/*   Updated: 2024/10/17 14:16:00 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_textures(mlx_texture_t **texture)
{
	if (texture[NORTH])
		mlx_delete_texture(texture[NORTH]);
	if (texture[SOUTH])
		mlx_delete_texture(texture[SOUTH]);
	if (texture[WEST])
		mlx_delete_texture(texture[WEST]);
	if (texture[EAST])
		mlx_delete_texture(texture[EAST]);
	free (texture);
}

mlx_texture_t **init_textures(void)
{
    mlx_texture_t **texture;

    texture = malloc(4 * sizeof(mlx_texture_t *));
    if (!texture)
    {
        fprintf(stderr, "Error: Failed to allocate memory for textures\n");
        exit(EXIT_FAILURE);
    }
    texture[NORTH] = mlx_load_png(get_game()->map.north);
    texture[SOUTH] = mlx_load_png(get_game()->map.south);
    texture[WEST] = mlx_load_png(get_game()->map.west);
    texture[EAST] = mlx_load_png(get_game()->map.east);
    if (!texture[NORTH] || !texture[SOUTH] || !texture[WEST] || !texture[EAST])
    {
        fprintf(stderr, "Error: Failed to load one or more textures\n");

        free_textures(texture);
        exit(EXIT_FAILURE);
    }
	tex()->size = texture[NORTH]->width;
    return texture;
}

void	set_angle(void)
{
	if (get_game()->player.start_dir == 'N')
        get_game()->player.player_a = 90;
    else if (get_game()->player.start_dir == 'S')
        get_game()->player.player_a = 270;
    else if (get_game()->player.start_dir == 'E')
        get_game()->player.player_a = 0;
    else if (get_game()->player.start_dir == 'W')
        get_game()->player.player_a = 180;
}

void	set_facing_direction(char direction)
{
	if (direction == 'N')
    {
        ray()->dirx = 0;
        ray()->diry = -1;
        ray()->planex = 0.66;
        ray()->planey = 0;
    }
    else if (direction == 'S')
    {
        ray()->dirx = 0;
        ray()->diry = 1;
        ray()->planex = -0.66;
        ray()->planey = 0;
    }
    else if (direction == 'E')
    {
        ray()->dirx = 1;
        ray()->diry = 0;
        ray()->planex = 0;
        ray()->planey = 0.66;
    }
    else if (direction == 'W')
    {
        ray()->dirx = -1;
        ray()->diry = 0;
        ray()->planex = 0;
        ray()->planey = -0.66;
    }
}

void	init_values(void)
{
	ray()->posx = get_game()->player.player_x;
	ray()->posy = get_game()->player.player_y;
}