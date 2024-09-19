/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:23:51 by lglauch           #+#    #+#             */
/*   Updated: 2024/09/19 15:26:52 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_error(void)
{
	printf("Error in init function");
	exit(EXIT_FAILURE);
}

void	init(void)
{
	get_game()->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D you belong to me", true);
	if (!get_game()->mlx)
		ft_error();
	get_game()->img = mlx_new_image(get_game()->mlx, WIDTH, HEIGHT);
	get_game()->minimap = mlx_new_image(get_game()->mlx, WIDTH / 6, WIDTH / 6);
	if (!get_game()->img || !get_game()->minimap
		|| (mlx_image_to_window(get_game()->mlx, get_game()->img, 0, 0) < 0)
		|| mlx_image_to_window(get_game()->mlx, get_game()->minimap, 0, 0) < 0)
		ft_error();
	get_game()->player.player_x = -1;
	get_game()->player.player_y = -1;
	get_game()->map.c_color = -1;
	get_game()->map.f_color = -1;
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

void	display(void *param)
{
	(void)param;
	drawplayer_minimap();
	player_movement();
}

void	print_map(char **map)
{
	int	i = -1;
	int	max_height = get_game()->map.map_height;

	printf("width: %d, height: %d\n", get_game()->map.map_width, get_game()->map.map_height);
	while (++i < max_height)
		printf("----line %d: %s\n", i, map[i]);
}

int	main(int argc, char **argv)
{
	if (check_arg(argv, argc))
		return (FAIL);
	init();
  	if (parse_map(argv[1]) || save_map(argv[1]) || check_elements())
		return (FAIL);
	printf("east: %swest: %snorth: %ssouth: %s", get_game()->map.east, get_game()->map.west, get_game()->map.north, get_game()->map.south);
	create_key_hooks();
	mlx_loop_hook(get_game()->mlx, &display, get_game()->mlx);
	mlx_loop(get_game()->mlx); //should be the last function after every mlx stuff is ready
	mlx_terminate(get_game()->mlx);
	return (EXIT_SUCCESS);
}
// 
