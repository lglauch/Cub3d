/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:20:47 by lglauch           #+#    #+#             */
/*   Updated: 2024/09/05 15:10:45 by bebuber          ###   ########.fr       */
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

# define WIDTH 1600
# define HEIGHT 1200
# define FAIL 1
# define SUCCESS 0

typedef struct s_player
{
	float	player_x;
	float	player_y;
 	char	start_dir;
}	t_player;

typedef struct s_map
{
	char	**map;
 	char	*north;
	char	*south;
	char	*west;
	char	*east;
 	int		map_height;
	int		map_width;
 	int		c_color;
	int		f_color;
}	t_map;

typedef struct s_cub3d_mlx
{
	void			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*minimap;
	t_player		player;
	t_map			map;
}	t_cub3d_mlx;

t_cub3d_mlx	*get_game(void);

//hooks
void		create_key_hooks(void);

//key funcions
void		esc_func(mlx_key_data_t key_data, void *param);
void		close_func(void *param);
void		player_movement(void);

//display
void		drawplayer_minimap(void);

//helper
void		ft_put_pixel(mlx_image_t *image, uint32_t x,
				uint32_t y, uint32_t color);

//parsing
int			parse_map(char	*file);

//parsing_utils
bool		compare_any(const char *str, char *substr[], int num_str, int n);
bool		contains_only(const char *str, const char *allowedchars);
char		*next_line(char *line, int fd);
void		save_texture(const char *line, char **texture);
void		error_exit(char *message, char *line, int fd);

//parsing_utils_two
void		fill_spaces(char *str, int start, int size);



#endif