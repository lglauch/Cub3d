/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:23:51 by lglauch           #+#    #+#             */
/*   Updated: 2024/09/05 12:44:18 by bebuber          ###   ########.fr       */
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
	get_game()->player.player_x = 30;
	get_game()->player.player_y = 30;
}

int	check_arg(char **argv, int argc)
{
	int	length;
	int	fd;

	fd = 0;
	if (argc != 2 || !argv[1])
	{
		printf("Please enter valid input\n");
		return (EXIT_FAILURE);
	}
	length = ft_strlen(argv[1]);
	if (ft_strncmp(&(argv[1][length - 4]), ".cub", 4) != 0 || length < 4)
	{
		printf("Invalid file type or name (.cub needed)\n");
		return (EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Unable to open file\n");
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

void	display(void *param)
{
	param = NULL;
	drawplayer_minimap();
	player_movement();
}

int	main(int argc, char **argv)
{
	if ((check_arg(argv, argc)) == 1)
		return (EXIT_FAILURE);
  if ((parse_map(argv[1], cub)))
		return (EXIT_FAILURE);
	init();
	create_key_hooks();
	mlx_loop_hook(get_game()->mlx, &display, get_game()->mlx);
	mlx_loop(get_game()->mlx); //should be the last function after every mlx stuff is ready
	mlx_terminate(get_game()->mlx);
	return (EXIT_SUCCESS);
}
