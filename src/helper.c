/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:07:38 by lglauch           #+#    #+#             */
/*   Updated: 2024/10/18 16:37:29 by lglauch          ###   ########.fr       */
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
		ft_putstr_fd("Error: Memory allocation failed", 2);
		return (NULL);
	}
	return (ptr);
}

t_raycasting	*ray(void)
{
	static t_raycasting	ray;

	return (&ray);
}

t_texinfo	*tex(void)
{
	static t_texinfo	tex;

	return (&tex);
}

t_line	*line(void)
{
	static t_line	line;

	return (&line);
}
