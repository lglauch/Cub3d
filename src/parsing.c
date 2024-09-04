/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:49:04 by bebuber           #+#    #+#             */
/*   Updated: 2024/09/04 18:54:46 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	save_textures(const char *line, t_mlx *cub)
{
	if (ft_strncmp(line, "NO ", 3))
		save_texture(line, &cub->north);
	else if (ft_strncmp(line, "SO ", 3))
		save_texture(line, &cub->south);
	else if (ft_strncmp(line, "WE ", 3))
		save_texture(line, &cub->west);
	else if (ft_strncmp(line, "EA ", 3))
		save_texture(line, &cub->east);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	save_colors(const char *line, t_mlx *cub)
{
	int		i;
	int		color;
	int		value;

	i = 2;
	color = 0;
	value = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] && color < 3)
	{
		if (ft_isdigit(line[i]))
			value = value * 10 + (line[i] - '0');
		else if (line[i] == ',' || line[i + 1] == '\n')
		{
			color = (color << 8) + value;
			value = 0;
		}
		i++;
	}
	if (*line == 'F')
		cub->f_color = color;
	else if (*line == 'C')
		cub->c_color = color;
}

void	save_player_loc(char *line, int i, int n, t_mlx *cub, int fd)
{
	if (cub->start_x == -1)
	{
		cub->start_dir = line[i];
		cub->start_x = i;
		cub->start_y = n;
	}
	else
		error_exit("Error: only one player is allowed", line, fd);
}

int	check_map(char	*line, t_mlx *cub, int fd)
{
	int	i;
	int	n;

	i = 0;
	n = 0;

	while (line && contains_only(line, "01 \n"))
	{
		i = -1;
		while (line[++i])
		{
			if (ft_strchr("NSEW", line[i]))
				save_player_loc(line, i, n, cub, fd);
			else if (!ft_strchr("01 \n", line[i]))
				error_exit("Error: invalid map", line, fd);
		}
		n++;
		line = next_line(line, fd);
	}
	if (line != NULL)
		error_exit("Error: invalid map", line, fd);
	cub->map_size = n;
	free (line);
	close (fd);
	return (EXIT_SUCCESS);
}

void	save_map(char *file, t_mlx *cub)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (contains_any(line, (const char *[]){"1", "0"}, 2))
		{
			while (line)
			{
				
			}
			break ;
		}
		else
			line = next_line(line, fd);
	}

}

int	parse_map(char	*file, t_mlx *cub)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (compare_any(line, (char *[]){"NO ", "SO ", "WE ", "EA "}, 4, 3))
			save_textures(line, cub);
		else if (compare_any(line, (char *[]){"F ", "C "}, 2, 2))
			save_colors(line, cub);
		else if (contains_only(line, "1 \n"))
		{
			check_map(line, cub, fd);
			save_map(file, cub);
			break ;
		}
		else if (contains_only(line, " \n"))
			line = next_line(line, fd);
		else
			error_exit("Error: invalid map", line, fd);
	}
	free (line);
	close (fd);
	return (EXIT_SUCCESS);
}
