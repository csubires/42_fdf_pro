/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/08/09 13:26:46 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	parse_color(t_map *map, char *s)
{
	while (*s && (isdigit(*s) || *s == '-' || *s == '+' || *s == ','))
		s++;
	if (*s && *s == 'x')
	{
		map->has_color = 1;
		return (strtol(s + 1, 0, 16));
	}
	return (BG_COLOR);
}

static void	map_to_mem(t_map *map, int fd)
{
	int		x;
	int		y;
	char	*line;
	char	**split;

	y = -1;
	while (++y < map->height)
	{
		line = ft_get_next_line(fd);
		split = ft_split(line, ' ');
		if (!split)
		{
			free_map(map);
			error_and_exit("map_to_mem", "split = ft_split");
		}
		x = -1;
		while (++x < map->width)
		{
			map->z_gen[y][x] = strtol(split[x], 0, 10);
			map->color_file[y][x] = parse_color(map, split[x]);
		}
		ft_free_split(split);
		free(line);
	}
}

static void	parse_file(t_map *map, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free_map(map);
		error_and_exit(file, "Error to open file or calloc.");
	}
	map_to_mem(map, fd);
	close(fd);
}

void	parse_args(t_map **map, int argc, char *argv[])
{
	if (argc != 2)
		error_and_exit(" Incorrect arguments", \
		"\nUse: ./fdf maps/name_map.fdf");
	printf("\n Preparing map, wait...\n");
	printf(" [+] Reading file fdf\n");
	*map = initialise_map(argv[1]);
	printf(" [+] Creating the memory structure\n");
	create_struct_mem(*map);
	printf(" [+] Loading map into memory\n");
	parse_file(*map, argv[1]);
	printf(" [+] Obtaining isometric coordinates\n");
	set_z_limits(*map);
	printf(" All ready. Press [ENTER] to open the help menu.\n");
}
