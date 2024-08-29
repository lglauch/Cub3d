/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:23:51 by lglauch           #+#    #+#             */
/*   Updated: 2024/08/29 12:40:47 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_map(char *argv)
{
	int	length;

	length = ft_strlen(argv);
	if (length < 4)
	{
		printf("Please enter valid map\n");
		return (0);
	}
	&(argv[length - 4]);
}

int	main(int argc, char **argv)
{
	if (argc != 2 && !(check_map(argv[1])))
	{
		
	}
}