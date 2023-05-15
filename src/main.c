/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:37:43 by yback             #+#    #+#             */
/*   Updated: 2023/05/15 15:05:39 by yback            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx.h"
#include "map.h"
#include "engine.h"

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
		error_handle("Error\nmap error!\n", map_line, yback_map);
	free(map_line);
}

char	*yb_reading_file(int fd, t_map *yback_map, char *map_line)
{
	char	*line;
	int		error_check;

	error_check = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strchr("NSWEFC", line[0]))
			error_check = yb_path_color_init(yb_trim(line), yback_map);
		else if (line[0] != '\n' && yback_map->flag != -2)
			map_line = yb_done_setting_element(line, map_line, yback_map);
		else if (ft_strlen(map_line) != 0 && ft_strlen(line) == 1)
			yback_map->flag = -2;
		else if (line[0] == '\n' && fnull(line))
			continue ;
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
	int		fd;
	char	*map_line;

	map_line = malloc(TMP_MEM);
	if (!map_line)
		error_handle("Error\nmap_line malloc error!\n", map_line, yback_map);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error_handle("Error\nCan't open file.\n", map_line, yback_map);
	map_line = yb_reading_file(fd, yback_map, map_line);
	yb_init_map_info(yback_map, map_line);
}

int	main(int argc, char *argv[])
{
	t_engine	engine;

	if (argc != 2 || argv[1] == NULL || argv[1][0] == '\0')
	{
		perror("Error\nInvalid arguments!\n");
		exit(1);
	}
	engine.ctx = mlx_init();
	engine.window = mlx_new_window(engine.ctx, WINDOW_W, WINDOW_H, "cub3D");
	engine.map = generate_map(argv[1]);
	init_display(engine.ctx, &engine.display, WINDOW_W, WINDOW_H);
	init_cam(&engine.cam, engine.map);
	if (init_textures(engine.ctx, &engine.map->north_path, engine.texs))
	{
		perror("Error\nCannot load textures!\n");
		destroy_engine(&engine);
		return (1);
	}
	mlx_hook(engine.window, EVENT_KEYPRESS, 0, &key_hook, &engine);
	mlx_hook(engine.window, EVENT_EXPOSE, 0, &expose_hook, &engine);
	mlx_hook(engine.window, EVENT_EXIT, 0, &close_hook, &engine);
	mlx_loop(engine.ctx);
	return (0);
}
