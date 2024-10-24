/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:23:51 by lglauch           #+#    #+#             */
/*   Updated: 2024/10/24 17:11:25 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_error(void)
{
	mlx_terminate(get_game()->mlx);
	printf("Error in init function\n");
	exit(EXIT_FAILURE);
}

void	init(void)
{
	get_game()->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D you belong to me", true);
	if (!get_game()->mlx)
	{
		printf("Error in init function\n");
		exit(EXIT_FAILURE);
	}
	get_game()->img = mlx_new_image(get_game()->mlx, WIDTH, HEIGHT);
	get_game()->minimap = mlx_new_image(get_game()->mlx, WIDTH / 6, WIDTH / 6);
	if (!get_game()->img || !get_game()->minimap
		|| (mlx_image_to_window(get_game()->mlx, get_game()->img, 0, 0) < 0)
		|| mlx_image_to_window(get_game()->mlx, get_game()->minimap, 0, 0) < 0)
		ft_error();
	get_game()->player.player_x = -1;
	get_game()->player.player_y = -1;
}

int	check_arg(char **argv, int argc)
{
	int	length;
	int	fd;

	fd = 0;
	if (argc != 2 || !argv[1])
	{
		printf("Error: usage: ./cub3D /path_to_the_map\n");
		return (EXIT_FAILURE);
	}
	length = ft_strlen(argv[1]);
	if (ft_strncmp(&(argv[1][length - 4]), ".cub", 4) != 0 || length < 4)
	{
		printf("Error: Invalid file type (.cub needed)\n");
		return (EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Failed opening file\n");
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

void	render(void *param)
{
	(void)param;
	drawplayer_minimap();
	render_frame();
	player_movement();
	raycasting();
}

int	main(int argc, char **argv)
{
	if (check_arg(argv, argc))
		return (FAIL);
	init();
	if (parse_map(argv[1]) || save_map(argv[1]) || check_elements())
		return (FAIL);
	set_facing_direction(get_game()->player.start_dir);
	set_angle();
	tex()->textures = init_textures();
	create_key_hooks();
	mlx_loop_hook(get_game()->mlx, &render, get_game()->mlx);
	mlx_loop(get_game()->mlx);
	mlx_terminate(get_game()->mlx);
	free_tex_path();
	free(tex()->textures);
	free_map();
	return (EXIT_SUCCESS);
}
