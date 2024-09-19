/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:06:45 by lglauch           #+#    #+#             */
/*   Updated: 2024/09/19 13:11:21 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_line(float x0, float y0, float x1, float y1) {
    int steps;
    float stepX, stepY;
    float x, y;
    int i;

    // Calculate the difference in both directions
    float dx = x1 - x0;
    float dy = y1 - y0;

    // Determine the number of steps to take
    steps = fmax(fabs(dx), fabs(dy));
    stepX = dx / (float)steps;
    stepY = dy / (float)steps;

    x = x0;
    y = y0;
    for (i = 0; i <= steps; i++) {
        ft_put_pixel(get_game()->minimap, round(x), round(y), 0xFFFFFF);

        x += stepX;
        y += stepY;
    }
}

void raycasting(void) {
    if (!get_game() || !get_game()->map.map) {
        fprintf(stderr, "Error: Invalid game state or map.\n");
        return;
    }

    int mapx = 27; // Assuming mapx and mapy are dimensions of the map, not player positions
    int mapy = 10;
    float ra = get_game()->player.player_a;
    while (ra < 0) {
        ra += 2 * M_PI;
    }
    while (ra >= 2 * M_PI) {
        ra -= 2 * M_PI;
    }
    int dof_max = 8;

    for (int r = 0; r < 1; r++) {
         float atan, ntan;
        // Check for ra being 0 or π to avoid division by zero
        if (ra == 0 || ra == (float)M_PI) {
            atan = 0; // atan could be set to 0 as it signifies no change in angle
            ntan = 0; // ntan set to 0 or another value, depending on how you wish to handle this case
        } else {
            atan = -1 / tan(ra);
            ntan = -tan(ra);
        }
        float rx, ry, xo, yo;
        int dof = 0;

        if (ra > M_PI) { // Looking up
            ry = (((int)get_game()->player.player_y >> 6) << 6) - 0.0001;
            rx = (get_game()->player.player_y - ry) * atan + get_game()->player.player_x;
            yo = -64;
            xo = -yo * atan;
        } else if (ra < M_PI) { // Looking down
            ry = (((int)get_game()->player.player_y >> 6) << 6) + 64;
            rx = (get_game()->player.player_y - ry) * atan + get_game()->player.player_x;
            yo = 64;
            xo = -yo * atan;
        } else if (ra == 0 || ra == (float)M_PI) {
            rx = get_game()->player.player_x;
            ry = get_game()->player.player_y;
            dof = dof_max;
        } else if (ra > M_PI / 2 && ra < 3 * M_PI / 2) { // Looking left
            rx = (((int)get_game()->player.player_x >> 6) << 6) - 0.0001;
            ry = (get_game()->player.player_x - rx) * ntan + get_game()->player.player_y;
            xo = -64;
            yo = -xo * ntan;
        } else { // Looking right
            rx = (((int)get_game()->player.player_x >> 6) << 6) + 64;
            ry = (get_game()->player.player_x - rx) * ntan + get_game()->player.player_y;
            xo = 64;
            yo = -xo * ntan;
        }

        while (dof < dof_max) {
    int mx = (int)rx >> 6;
    int my = (int)ry >> 6;
    int mp = my * mapx + mx;

    // Add bounds checking for mp
    if (mp >= 0 && mp < mapx * mapy) {
        char* mapValue = get_game()->map.map[mp]; // Store the pointer before dereferencing
        // Validate the pointer before dereferencing
        if (mapValue && *mapValue == '1') {
            dof = dof_max; // Found a wall
            // Assuming draw_line is a function that draws a line from player position to the wall
            draw_line(get_game()->player.player_x, get_game()->player.player_y, rx, ry);
        } else {
            rx += xo;
            ry += yo;
            dof++;
        }
    } else {
        // Handle the case where mp is out of bounds, possibly by breaking out of the loop or adjusting rx, ry
        break; // Simplest solution: break out of the loop if mp is out of bounds
    }
        }
    }
}
