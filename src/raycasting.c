/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:06:45 by lglauch           #+#    #+#             */
/*   Updated: 2024/09/19 16:17:32 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void draw_line(float x0, float y0, float x1, float y1) {
//     int steps;
//     float stepX, stepY;
//     float x, y;
//     int i;

//     // Calculate the difference in both directions
//     float dx = x1 - x0;
//     float dy = y1 - y0;

//     // Determine the number of steps to take
//     steps = fmax(fabs(dx), fabs(dy));
//     stepX = dx / (float)steps;
//     stepY = dy / (float)steps;

//     x = x0;
//     y = y0;
//     for (i = 0; i <= steps; i++) {
//         ft_put_pixel(get_game()->minimap, round(x), round(y), 0xFFFFFF);

//         x += stepX;
//         y += stepY;
//     }
// }

