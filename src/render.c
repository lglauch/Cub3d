/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:20:46 by leo               #+#    #+#             */
/*   Updated: 2024/10/17 20:58:05 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void    render_frame(void)
{
    int x;
    int y;

    y = 0;
    while (y < HEIGHT / 2)
    {
        x = 0;
        while (x < WIDTH)
        {
            ft_put_pixel(get_game()->img, x, y, 0x87CEEB);
            x++;
        }
        y++;
    }
    y = HEIGHT / 2;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            ft_put_pixel(get_game()->img, x, y, 0x2F4F4F);
            x++;
        }
        y++;
    }
}
