/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:46:45 by leo               #+#    #+#             */
/*   Updated: 2024/10/12 15:29:58 by leo              ###   ########.fr       */
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

void update_texture(int x)
{
    int y;
    int color;
    set_direction();

    tex()->x = (int)(ray()->wall_x * tex()->size);
    printf("b\n");
    if ((ray()->side == 0 && ray()->dirx < 0)
        || (ray()->side == 1 && ray()->diry > 0))
        tex()->x = tex()->size - tex()->x - 1;
    printf("a\n");
    tex()->step = 1.0 * tex()->size / ray()->line_height;
    tex()->pos = (ray()->draw_start - HEIGHT / 2 + ray()->line_height / 2) * tex()->step;
    y = ray()->draw_start;
    printf("c\n");
    while (y < ray()->draw_end)
    {
        tex()->y = (int)tex()->pos & (tex()->size - 1);
        printf("c1\n");
        tex()->pos += tex()->step;
        printf("c2\n");

        // Add bounds checking and null pointer checks
        if (tex()->index < 0 || tex()->index >= 4)
        {
            fprintf(stderr, "Error: tex()->index out of bounds: %d\n", tex()->index);
            return;
        }
        printf("1\n");
        if (!tex()->textures)
        {
            fprintf(stderr, "Error: tex()->textures is null\n");
            return;
        }
        if (!tex()->textures[tex()->index])
        {
            fprintf(stderr, "Error: tex()->textures[%d] is null\n", tex()->index);
            return;
        }
        printf("tex->y\n");
        if (tex()->y < 0 || tex()->y >= tex()->size)
        {
            fprintf(stderr, "Error: tex()->y out of bounds: %d\n", tex()->y);
            return;
        }
        printf("3\n");
        if (tex()->x < 0 || tex()->x >= tex()->size)
        {
            fprintf(stderr, "Error: tex()->x out of bounds: %d\n", tex()->x);
            return;
        }
        printf("checks ended\n");
        color = tex()->textures[tex()->index][tex()->size * tex()->y + tex()->x];
        printf("c3\n");
        if (tex()->index == NORTH || tex()->index == EAST)
            color = (color >> 1) & 8355711;
        printf("Color : %d\n", color);
        if (color > 0)
        {
            ft_put_pixel(get_game()->img, x, y, color);
            printf("SCHABERNAK");
        }
        printf("c4\n");
        y++;
    }
}