/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:23:51 by lglauch           #+#    #+#             */
/*   Updated: 2024/08/29 15:10:19 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdnoreturn.h>

int	check_map(char **argv, int argc)
{
	int	length;
	int	fd;

	fd = 0;
	if (argc != 2 || !argv[1])
	{
		printf("Please enter valid input\n");
		return (0);
	}
	length = ft_strlen(argv[1]);
	if (ft_strncmp(&(argv[1][length - 4]), ".cub", 4) != 0 || length < 4)
	{
		printf("Invalid file type or name (.cub needed)\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Unable to open file\n");
		return (0);
	}
	close(fd);
	return (1);
}

int	main(int argc, char **argv)
{
	if (!(check_map(argv, argc)))
		return (1);
	init();
}
