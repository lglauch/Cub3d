/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:07:38 by lglauch           #+#    #+#             */
/*   Updated: 2024/09/05 14:05:22 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_cub3d_mlx	*get_game(void)
{
	static t_cub3d_mlx	game;

	return (&game);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		ft_putstr_fd("Error: memory allocation failed", 2);
		return (NULL);
	}
	return (ptr);
}

void	ft_put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	if (!image)
		return ;
	if (x >= 0 && y >= 0 && x < image->width && y < image->height)
		mlx_put_pixel(image, x, y, color);
}
