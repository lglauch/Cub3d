/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:06:45 by lglauch           #+#    #+#             */
/*   Updated: 2024/09/18 17:00:46 by lglauch          ###   ########.fr       */
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

    // Added debugging information before the loop starts
    printf("Before loop: dx=%f, dy=%f, steps=%d, stepX=%f, stepY=%f\n", dx, dy, steps, stepX, stepY);

    for (i = 0; i <= steps; i++) {
        // Debugging inside the loop to track the progress
        printf("Loop %d: x=%f, y=%f\n", i, x, y);

        ft_put_pixel(get_game()->minimap, round(x), round(y), 0xFFFFFF);

        x += stepX;
        y += stepY;
    }

    // Debugging after the loop to confirm completion
    printf("Line drawing completed.\n");
}

void raycasting(void) {
    if (!get_game() || !get_game()->map.map) {
        fprintf(stderr, "Error: Invalid game state or map.\n");
        return;
    }

    int mapx = 64; // Assuming mapx and mapy are dimensions of the map, not player positions
    int mapy = 64;
    float ra = get_game()->player.player_a;
    int dof_max = 8;

    for (int r = 0; r < 1; r++) {
        float atan = -1 / tan(ra);
        float ntan = -tan(ra);
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
        } else if (ra == 0 || ra == M_PI) { // Looking straight left or right
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

            if (mp < mapx * mapy && get_game()->map.map[mp] == (char *)1) {
                dof = dof_max; // Found a wall
                // Assuming draw_line is a function that draws a line from player position to the wall
                draw_line(get_game()->player.player_x, get_game()->player.player_y, rx, ry);
            } else {
                rx += xo;
                ry += yo;
                dof++;
            }
        }
    }

    // Debugging after the loop to confirm completion
    printf("Line drawing completed.\n");
}