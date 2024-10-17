/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:46:45 by leo               #+#    #+#             */
/*   Updated: 2024/10/17 21:15:32 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void    set_direction(void)
// {
//     printf("Side %d\n", ray()->side);
//     if (ray()->side == 0)
// 	{
// 		if (ray()->dirx < 0)
// 			tex()->index = WEST;
// 		else
// 			tex()->index = EAST;
// 	}
// 	else
// 	{
// 		if (ray()->diry > 0)
// 			tex()->index = SOUTH;
// 		else
// 			tex()->index = NORTH;
// 	}
//     printf("Direction set: tex()->index = %d\n", tex()->index);
// }

// void update_texture(int x)
// {
//     int y;
//     int color;

//     // set_direction();
//     tex()->x = (int)(ray()->wall_x * (double)(tex()->size));
//     if ((ray()->side == 0 && ray()->raydirx > 0) || (ray()->side == 1 && ray()->raydiry < 0))
//         tex()->x = tex()->size - tex()->x - 1;

//     // Calculate step and initial texture position
//     tex()->step = 1.0 * tex()->size / ray()->line_height;
//     tex()->pos = (ray()->draw_start - HEIGHT / 2 + ray()->line_height / 2) * tex()->step;

//     y = ray()->draw_start;
//     while (y < ray()->draw_end)
//     {
//         // Calculate texture y coordinate
//         tex()->y = (int)tex()->pos & (tex()->size - 1);
//         tex()->pos += tex()->step;

//         // printf("tex_info->index: %d, tex_info->x: %d, tex_info->y: %d\n", tex()->index, tex()->x, tex()->y);

//         // Ensure indices are within bounds
//         if (tex()->index < 0 || tex()->index >= 4 ||
//             tex()->x < 0 || tex()->x >= tex()->size ||
//             tex()->y < 0 || tex()->y >= tex()->size)
//         {
//             fprintf(stderr, "Error: Texture index out of bounds\n");
//             return;
//         }
//         // Fetch color from texture
//         mlx_texture_t *texture = tex()->textures[tex()->index];
//         color = ((int *)texture->pixels)[tex()->size * tex()->y + tex()->x];
//         ft_put_pixel(get_game()->img, x, y, color);
//         y++;
//     }
// }
