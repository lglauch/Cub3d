/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:20:47 by lglauch           #+#    #+#             */
/*   Updated: 2024/09/05 13:42:35 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

typedef struct s_mlx
{
	void	*mlx;
	char	**map;
	int		map_height;
	int		map_width;
	int		start_x;
	int		start_y;
	char	start_dir;
	int		c_color;
	int		f_color;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_mlx;



//----- parsing.c


#endif