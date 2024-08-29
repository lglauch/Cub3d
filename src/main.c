/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:23:51 by lglauch           #+#    #+#             */
/*   Updated: 2024/08/29 12:57:11 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_map(char *argv)
{
	int	length;
	int	fd;

	fd = 0;
	length = ft_strlen(argv);
	if (length < 4)
	{
		printf("Please enter valid map\n");
		return (0);
	}
	if (ft_strncmp(&(argv[length - 4]), ".cub", 4) != 0)
	{
		printf("Invalid file type (.cub needed)\n");
		return (0);
	}
	fd = open(argv, O_RDONLY);
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
	if (argc != 2 || !(check_map(argv[1])))
		return (1);
	
}