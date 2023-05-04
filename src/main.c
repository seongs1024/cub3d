/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:37:43 by yback             #+#    #+#             */
/*   Updated: 2023/05/04 22:40:09 by yback            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "get_next_line_bonus.h"
#include "libft.h"
#include <stdio.h>
#include <fcntl.h>

size_t	yb_strslen(char **strs)
{
	size_t	len;

	len = 0;
	while (strs[len])
		len++;
	return (len);
}

void	yb_check_path_empty(char **yb_path, char *splitted_line)
{
	if (*yb_path)
	{
		perror("Error: This path is already assigned!");
		exit(1);
	}
	else
		*yb_path = splitted_line;
}

int	yb_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;

	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

void	yb_path_init(t_map *yback_map, char **splitted_line)
{
	if (yb_strcmp(splitted_line[0], "NO") == 1)
		yb_check_path_empty(&yback_map->north_path, splitted_line[1]);
	else if (yb_strcmp(splitted_line[0], "SO") == 1)
		yb_check_path_empty(&yback_map->south_path, splitted_line[1]);
	else if (yb_strcmp(splitted_line[0], "WE") == 1)
		yb_check_path_empty(&yback_map->west_path, splitted_line[1]);
	else if (yb_strcmp(splitted_line[0], "EA") == 1)
		yb_check_path_empty(&yback_map->east_path, splitted_line[1]);
	else
	{
		perror("Error: Invalid argument. Check!!");
		exit(1);
	}
}

int	yb_atoi_check(char *splitted_color)
{
	int	num;

	num = ft_atoi(splitted_color);
	if (!(0 <= num && num <= 255))
	{
		perror("Error: Invalid color number!");
		exit(1);
	}
	return (num);
}

void	yb_check_int(char **splitted_color)
{
	int	i;

	i = -1;
	while (splitted_color[++i])
	{
		if (ft_strchr(splitted_color[i], '.') != 0)
		{
			perror("Error: Only Integer color allowed!\n");
			exit(1);
		}
	}
}

void	yb_color_init(t_map *yback_map, char **splitted_line)
{
	char	**splitted_color;
	
	splitted_color = ft_split(splitted_line[1], ',');
	yb_check_int(splitted_color);
	if (yb_strslen(splitted_color) != 3)
	{
		perror("Error: Invalid color.");
		exit(1);
	}
	if (yb_strcmp(splitted_line[0], "F") == 1)
	{
		yback_map->flag++;
		yback_map->f_colors[0] = yb_atoi_check(splitted_color[0]);
		yback_map->f_colors[1] = yb_atoi_check(splitted_color[1]);
		yback_map->f_colors[2] = yb_atoi_check(splitted_color[2]);
	}
	else if (yb_strcmp(splitted_line[0], "C") == 1)
	{
		yback_map->flag++;
		yback_map->c_colors[0] = yb_atoi_check(splitted_color[0]);
		yback_map->c_colors[1] = yb_atoi_check(splitted_color[1]);
		yback_map->c_colors[2] = yb_atoi_check(splitted_color[2]);
	}
}

void	yb_path_color_init(t_map *yback_map, char *line)
{
	char	**splitted_line;

	splitted_line = ft_split(line, ' ');
	if (yb_strslen(splitted_line) == 2)
	{
		if (yb_strcmp(splitted_line[0], "F") || yb_strcmp(splitted_line[0], "C"))
			yb_color_init(yback_map, splitted_line);
		else
			yb_path_init(yback_map, splitted_line);
	}
	else
	{
		perror("Error: There are invalid arguments in the file!!!");
		exit(1);
	}
}

int	yb_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

char	*yb_trim(char *line)
{
	char	*end_line;

	while (yb_isspace(*line))
		line++;
	if (*line == '\0')
		return (line);
	end_line = line + ft_strlen(line) - 1;
	while (end_line > line && yb_isspace(*end_line))
		end_line--;
	*(end_line + 1) = '\0';
	return (line);
}

void	yb_done_setting_element(t_map *yback_map)
{
	if (yback_map->north_path == NULL
		|| yback_map->south_path == NULL
		|| yback_map->west_path == NULL
		|| yback_map->east_path == NULL
		|| yback_map->flag != 2)
	{
		perror("Error: Element missing!\n");
		exit(1);
	}	
}

int	yb_find_max_col(t_map *yback_map)
{
	int	i;
	int	j;
	int max_len;

	i = 0;
	j = 0;
	max_len = -1;
	while (yback_map->map[i])
	{
		while (yback_map->map[i][j])
		{
			if (j > max_len)
				max_len = j;
			j++;
		}
		i++;
	}
	return (max_len + 1);
}

void	yb_map_check_split(char *map_line)
{
	char	**splitted_map;
	int		line_size;
	int		i;

	i = -1;
	splitted_map = ft_split(map_line, ' ');
	while (splitted_map[++i])
	{
		line_size = ft_strlen(splitted_map[i]);
		if (splitted_map[i][0] == '0' || splitted_map[i][line_size - 1] == '0')
		{
			perror("Error: Wall missing1!\n");
			exit(1);
		}
	}
}

void	yb_wall_check(t_map *yback_map, int i, int j)
{
	char	u;
	char	d;

	if (i == 0 || i == yback_map->map_height - 1)
	{
		perror("Error: Wall missing2!\n");
		exit(1);
	}
	else
	{
		u = yback_map->map[i - 1][j];
		d = yback_map->map[i + 1][j];
		if (!(u == 'N' || u == 'S' || u == 'E' || u == 'W'
			|| u == '1' || u == '0' || d == '1' || d == '0'
			|| d == 'N' || d == 'S' || d == 'E' || d == 'W'))
		{
			perror("Error: Wall missing3!\n");
			exit(1);
		}
	}
}

void	yb_find_player_pos(t_map *yback_map, int i, int j)
{
	char	c;

	c = yback_map->map[i][j];
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (yback_map->player_pos[0] > 0)
		{
			perror("Error: Only one player allowed!\n");
			exit(1);
		}
		yback_map->player_dir = c;
		yback_map->player_pos[0] = i;
		yback_map->player_pos[1] = j;
		yb_wall_check(yback_map, i, j);
	}
	else if (!(c == '1' || c == '0' || c == ' '))
	{
		perror("Error: Invalid player info!\n");
		exit(1);
	}
	else if (c == '0')
		yb_wall_check(yback_map, i, j);
}

void	yb_find_player(t_map *yback_map)
{
	int	i;
	int	j;
	
	i = 0;
	while (yback_map->map[i])
	{
		yb_map_check_split(yback_map->map[i]);
		j = 0;
		while (yback_map->map[i][j])
		{
			yb_find_player_pos(yback_map, i, j);
			j++;
		}
		i++;
	}
}

void	yb_check_info(t_map *yback_map)
{
	if (yb_strslen(yback_map->map) <= 1)
	{
		perror("Error: Invalid map!!");
		exit(1);
	}
}

void	yb_init_map_info(t_map *yback_map, char *map_line)
{
	yback_map->map = ft_split(map_line, '\n');
	free(map_line);
	yback_map->map_height = yb_strslen(yback_map->map);
	yback_map->map_width = yb_find_max_col(yback_map);
	yb_find_player(yback_map);
	yb_check_info(yback_map);
}

void	init_map_with_file(char *file_name, t_map *yback_map)
{
	int 	fd;
	char	*line;
	char	*map_line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror("Error: Can't open file.");
		exit(1);
	}
	map_line = malloc(10000);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E' || line[0] == 'F' || line[0] == 'C')
			yb_path_color_init(yback_map, yb_trim(line));
		else if (line[0] != '\n' && yback_map->flag != -2)
		{
			yb_done_setting_element(yback_map);
			map_line = ft_strjoin(map_line, line);
		}
		else if (ft_strlen(map_line) != 0 && ft_strlen(line) == 1)
			yback_map->flag = -2;
		else if (line[0] == '\n')
			continue;
		else
		{
			perror("Error: Element error occured!");
			exit(1);
		}
	}
	yb_init_map_info(yback_map, map_line);
}

void	yb_print_structure(t_map *yback_map)
{
	int	i;

	i = 0;
	printf("north_path = %s\n", yback_map->north_path);
	printf("south_path = %s\n", yback_map->south_path);
	printf("west_path = %s\n", yback_map->west_path);
	printf("east_past = %s\n", yback_map->east_path);
	printf("f_colors = ");
	while (i < 3)
		printf("%d ", yback_map->f_colors[i++]);
	printf("\nc_colors = ");
	i = 0;
	while (i < 3)
		printf("%d ", yback_map->c_colors[i++]);
	printf("\n");
	printf("height = %d, width = %d\n", yback_map->map_height, yback_map->map_width);
	i = 0;
	while (yback_map->map[i])
		printf("%s\n", yback_map->map[i++]);
	printf("player_pos = (%d, %d)\n", yback_map->player_pos[0], yback_map->player_pos[1]);
	printf("player_dir = %c\n", yback_map->player_dir);
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
	// init_map_with_file("./maps/e7-invalid-path2.cub", yback_map); 이거 해결해야함
	// init_map_with_file("./maps/e8-color-float.cub", yback_map);
	// init_map_with_file("./maps/e9-color-out-of-range.cub", yback_map);
	// init_map_with_file("./maps/e10-color-2num.cub", yback_map);
	// init_map_with_file("./maps/e11-lack-comp.cub", yback_map);
	// init_map_with_file("./maps/e12-lack-comp2.cub", yback_map);
	// init_map_with_file("./maps/e13-lack-comp3.cub", yback_map);
	// init_map_with_file("./maps/e14-more-map.cub", yback_map);
	// init_map_with_file("./maps/e15-empty-image.cub", yback_map); 이거 해결해야함
	// init_map_with_file("./maps/s1.cub", yback_map);
	// init_map_with_file("./maps/s2.cub", yback_map);
	yb_print_structure(yback_map);
}