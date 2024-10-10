/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:20:47 by lglauch           #+#    #+#             */
/*   Updated: 2024/10/09 12:52:55 by leo              ###   ########.fr       */
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
# define SPEED 5
# define FOV 60

enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

typedef struct s_raycasting
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	deltadistx;
	double	deltadisty;
	int		mapx;
	int		mapy;
	double	perpwalldist;
	double	sidedistx;
	double	sidedisty;
	double	wall_x;
	int		stepx;
	int		stepy;
	int		side;
	double	wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	
}	t_raycasting;

typedef struct s_texinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}	t_texinfo;

typedef	struct s_line
{
	int	x;
	int	y;
	int	y0;
	int	y1;
	int	tex_x;
	int	tex_y;
} t_line;


typedef struct s_player
{
	float	player_x;
	float	player_y;
 	char	start_dir;
	float	player_dx;
	float	player_dy;
	float	player_a;
}	t_player;

typedef struct s_map
{
	char	**map;
 	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		wall;
	int		floor;
 	int		map_height;
	int		map_width;
 	int		c_color;
	int		f_color;
}	t_map;

typedef struct s_minimap
{
	int		x;
	int		y;
	int		sx;
	int		sy;
	int		color;
	int		map_height;
	int		map_width;
	int		minimap_width;
	int		minimap_height;
	float	scale_x;
	float	scale_y;
}	t_minimap;

typedef struct s_cub3d_mlx
{
	void			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*minimap;
	t_player		player;
	t_map			map;
	t_minimap		minimap_var;
}	t_cub3d_mlx;

t_cub3d_mlx		*get_game(void);
t_raycasting	*ray(void);
t_line			*line(void);
t_texinfo		*tex(void);

//hooks
void			create_key_hooks(void);

//key funcions
void			esc_func(mlx_key_data_t key_data, void *param);
void			close_func(void *param);
void			player_movement(void);

//display
void			drawplayer_minimap(void);
void			put_line(float dx, float dy, float player_x, float player_y);

//helper
void			ft_put_pixel(mlx_image_t *image, uint32_t x,
				uint32_t y, uint32_t color);
void			*ft_malloc(size_t size);

//parsing
int				parse_map(char	*file);

//parsing_utils
bool			compare_any(const char *str, char *substr[], int num_str, int n);
bool			contains_only(const char *str, const char *allowedchars);
bool			contains_any(const char *str, const char *chars);
char			*next_line(char *line, int fd);
void			error_exit(char *message, char *line, int fd);

//parsing_utils_two
bool			flood_fill(char **map, int x, int y, int max_height);
int				save_map(char *file);
void			print_map(char **map);
int				check_elements(void);

//parsing_utils_three
int				save_textures(const char *line, t_map *map);
void			save_texture(const char *line, char **texture);
void			free_and_exit(char *message);
void			fill_spaces(char *str, int start, int size);
void			ft_put_pixel(mlx_image_t *image, uint32_t x,
					uint32_t y, uint32_t color);

//minimap_utils
void			draw_on_minimap(t_minimap *minimap, char **map);

//raycasting
void			raycasting(void);

//render
void    		update_texture(int x);

#endif