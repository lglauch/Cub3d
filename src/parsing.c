/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:49:04 by bebuber           #+#    #+#             */
/*   Updated: 2024/09/03 19:45:18 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	contains_any(const char *str, const char *substrings[], int num_str)
{
	int	i;

	i = 0;
	while (i < num_str)
	{
		if (ft_strstr(str, substrings[i]) != NULL)
			return (true);
		i++;
	}
	return (false);
}

void	save_textures(const char *line, t_mlx *cub)
{
	if (ft_strncmp(line, "NO", 2))
		cub->north = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO", 2))
		cub->north = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE", 2))
		cub->north = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA", 2))
		cub->north = ft_strdup(line + 3);
}

void	save_colors(const char *line, t_mlx *cub)
{
	int		i;
	int		color;
	int		value;

	i = 0;
	color = 0;
	value = 0;
	while (line[i] && color < 3)
	{
		if (ft_isdigit(line[i]))
			value = value * 10 + (line[i] - '0');
		else if (line[i] == ',' || line[i + 1] == '\0')
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

int	check_map(char	*line, t_mlx *cub, int fd)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (line && contains_any(line, (const char *[]){"0", "1"}, 2))
	{
		i = 0;
		while (line[i])
		{
			if (ft_strchr("NSEW", line[i]))
			{
				if (cub->start_x == -1)
				{
					cub->start_dir = line[i];
					cub->start_x = i;
					cub->start_y = n;
				}
				else
				{
					perror("Error: only one player is allowed");
					return (EXIT_FAILURE);
				}
			}
			else if (!ft_isdigit(line[i]) && !ft_isspace(line[i]))
				return (perror("Error: invalid map"), EXIT_FAILURE);
			i++;
		}
		n++;
		free (line);
		line = get_next_line(fd);
	}
	cub->map_size = n;
	return (EXIT_SUCCESS);
}

int	parse_map(char	*file, t_mlx *cub)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (contains_any(line, (const char *[]){"NO", "SO", "WE", "EA"}, 4))
			save_textures(line, cub);
		else if (contains_any(line, (const char *[]){"F", "C"}, 2))
			save_colors(line, cub);
		else if (contains_any(line, (const char *[]){"0", "1"}, 2))
		{
			if (check_map(line, cub, fd))
				exit ;
			break ;
		}
		else if (line[0] != '\n')
			return (perror("Error: invalid map"), EXIT_FAILURE);
		free (line);
		line = get_next_line(fd);
	}
	free (line);
	close (fd);
	return (EXIT_SUCCESS);
}
