/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:46:45 by leo               #+#    #+#             */
/*   Updated: 2024/10/10 17:54:45 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    set_direction(void)
{
    if (ray()->side == 0)
    {
        if (ray()->dirx < 0)
            tex()->index = WEST;
        else
            tex()->index = EAST;
    }
    else
    {
        if (ray()->diry > 0)
            tex()->index = SOUTH;
        else
            tex()->index = NORTH;
    }
}

// void    update_texture(int x)
// {
//     int y;
//     int color;

//     set_direction();
//     tex()->size = 64;
//     tex()->x = (int)(ray()->wall_x * tex()->size);
//     if ((ray()->side == 0 && ray()->dirx < 0)
// 		|| (ray()->side == 1 && ray()->diry > 0))
// 		tex()->x = tex()->size - tex()->x - 1;
// 	tex()->step = 1.0 * tex()->size / ray()->line_height;
// 	tex()->pos = (ray()->draw_start - HEIGHT / 2
// 			+ ray()->line_height / 2) * tex()->step;
// 	y = ray()->draw_start;
// 	while (y < ray()->draw_end)
// 	{
// 		tex()->y = (int)tex()->pos & (tex()->size - 1);
// 		tex()->pos += tex()->step;
// 		color = data->textures[tex()->index][tex()->size * tex()->y + tex()->x];
// 		if (tex()->index == NORTH || tex()->index == EAST)
// 			color = (color >> 1) & 8355711;
// 		if (color > 0)
// 			data->texture_pixels[y][x] = color;
// 		y++;
// 	}
// }
