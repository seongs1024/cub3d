/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:37:43 by yback             #+#    #+#             */
/*   Updated: 2023/05/05 20:07:12 by yback            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	yb_path_color_init(char *line, t_map *yback_map)
{
	char	**spl_line;
	int		error_check;

	error_check = 0;
	spl_line = ft_split(line, ' ');
	if (yb_strslen(spl_line) == 2)
	{
		if (yb_strcmp(spl_line[0], "F") || yb_strcmp(spl_line[0], "C"))
			error_check = yb_color_init(spl_line, yback_map);
		else
			error_check = yb_path_init(spl_line, yback_map);
	}
	else
		error_check = -1;
	free_arr(spl_line);
	return (error_check);
}

void	yb_init_map_info(t_map *yback_map, char *map_line)
{
	yback_map->map = ft_split(map_line, '\n');
	yback_map->map_height = yb_strslen(yback_map->map);
	yback_map->map_width = yb_find_max_col(yback_map);
	if (yb_find_player(yback_map) == -1 || yb_check_info(yback_map) == -1)
		error_handle("Error: map error!\n", map_line, yback_map);
	free(map_line);
}

char	*yb_reading_file(int fd, t_map *yback_map, char *map_line)
{
	char	*line;
	int		error_check;

	error_check = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W'
			|| line[0] == 'E' || line[0] == 'F' || line[0] == 'C')
			error_check = yb_path_color_init(yb_trim(line), yback_map);
		else if (line[0] != '\n' && yback_map->flag != -2)
			map_line = yb_done_setting_element(line, map_line, yback_map);
		else if (ft_strlen(map_line) != 0 && ft_strlen(line) == 1)
			yback_map->flag = -2;
		else if (line[0] == '\n')
		{
			free(line);
			continue;
		}
		else
			error_check = -1;
		if (error_check == -1)
			yb_line_error_check(line, map_line, yback_map);
		free(line);
	}
	return (map_line);
}

void	init_map_with_file(char *file_name, t_map *yback_map)
{
	int 	fd;
	char	*map_line;

	map_line = malloc(10000);
	if (!map_line)
		error_handle("Error: map_line malloc error!\n", map_line, yback_map);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error_handle("Error: Can't open file.", map_line, yback_map);
	map_line = yb_reading_file(fd, yback_map, map_line);
	yb_init_map_info(yback_map, map_line);
}

int main()
{
	t_map	*yback_map;

	yback_map = malloc(sizeof(t_map));
	if (!yback_map)
	{
		perror("Error: malloc");
		exit(1);
	}
	// init_map_with_file("./maps/e1-invalid-char-in-map.cub", yback_map);
	// init_map_with_file("./maps/e2-no-wall.cub", yback_map);
	// init_map_with_file("./maps/e3-no-wall2.cub", yback_map);
	// init_map_with_file("./maps/e4-empty.cub", yback_map);
	// init_map_with_file("./maps/e5-more-player.cub", yback_map);
	// init_map_with_file("./maps/e6-invalid-path.cub", yback_map);
	// init_map_with_file("./maps/e7-invalid-path2.cub", yback_map);
	// init_map_with_file("./maps/e8-color-float.cub", yback_map);
	// init_map_with_file("./maps/e9-color-out-of-range.cub", yback_map);
	// init_map_with_file("./maps/e10-color-2num.cub", yback_map);
	// init_map_with_file("./maps/e11-lack-comp.cub", yback_map);
	// init_map_with_file("./maps/e12-lack-comp2.cub", yback_map);
	// init_map_with_file("./maps/e13-lack-comp3.cub", yback_map);
	// init_map_with_file("./maps/e14-more-map.cub", yback_map);
	// init_map_with_file("./maps/e15-empty-image.cub", yback_map);
	// init_map_with_file("./maps/s1.cub", yback_map);
	init_map_with_file("./maps/s2.cub", yback_map);
	yb_print_structure(yback_map);
	free_yback(yback_map);
	system("leaks cub3D");
}