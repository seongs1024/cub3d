/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:37:43 by yback             #+#    #+#             */
/*   Updated: 2023/05/05 19:26:03 by yback            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "get_next_line_bonus.h"
#include "libft.h"

size_t	yb_strslen(char **strs)
{
	size_t	len;

	len = 0;
	while (strs[len])
		len++;
	return (len);
}

int	yb_check_path_empty(char **yb_path, char *spl_line)
{
	int		tmp_fd;
	char	first_byte;

	if (!yb_path)
		return (-1);
	else
	{
		tmp_fd = open(spl_line, O_RDONLY);
		if (tmp_fd == -1)
			return (-1);
		if (read(tmp_fd, &first_byte, 1) == 0)
		{
			close(tmp_fd);
			return (-1);
		}
		*yb_path = ft_strdup(spl_line);
		close(tmp_fd);
	}
	return (0);
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

int	yb_path_init(char **spl_line, t_map *yback_map)
{
	int	error_check;

	error_check = 0;
	if (yb_strcmp(spl_line[0], "NO") == 1)
		error_check = yb_check_path_empty(&yback_map->north_path, spl_line[1]);
	else if (yb_strcmp(spl_line[0], "SO") == 1)
		error_check = yb_check_path_empty(&yback_map->south_path, spl_line[1]);
	else if (yb_strcmp(spl_line[0], "WE") == 1)
		error_check = yb_check_path_empty(&yback_map->west_path, spl_line[1]);
	else if (yb_strcmp(spl_line[0], "EA") == 1)
		error_check = yb_check_path_empty(&yback_map->east_path, spl_line[1]);
	else
		error_check = -1;
	return (error_check);
}

int	yb_atoi_check(char *spl_color)
{
	int	num;

	num = ft_atoi(spl_color);
	if (!(0 <= num && num <= 255))
		return (-123);
	return (num);
}

int	yb_check_int(char **spl_color)
{
	int	i;

	i = -1;
	while (spl_color[++i])
	{
		if (ft_strchr(spl_color[i], '.') != 0)
			return (-1);
	}
	return (0);
}

void	yb_init_colors(t_map *yback_map, int *colors, char **spl_color)
{
	yback_map->flag++;
	colors[0] = yb_atoi_check(spl_color[0]);
	colors[1] = yb_atoi_check(spl_color[1]);
	colors[2] = yb_atoi_check(spl_color[2]);
}

int	yb_color_check(int *colors)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (colors[i] == -123)
			return (-1);
	}
	return (0);
}

int	yb_color_init(char **spl_line, t_map *yback_map)
{
	char	**spl_color;
	int		error_check;

	error_check = 0;
	spl_color = ft_split(spl_line[1], ',');
	if (yb_check_int(spl_color) == -1 || yb_strslen(spl_color) != 3)
	{
		free_arr(spl_color);
		return (-1);
	}
	if (yb_strcmp(spl_line[0], "F") == 1)
		yb_init_colors(yback_map, yback_map->f_colors, spl_color);
	else if (yb_strcmp(spl_line[0], "C") == 1)
		yb_init_colors(yback_map, yback_map->c_colors, spl_color);
	if (yb_color_check(yback_map->f_colors) == -1
		|| yb_color_check(yback_map->c_colors) == -1)
		error_check = -1;

	free_arr(spl_color);
	return (error_check);
}

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

char	*yb_done_setting_element(char *line, char *map_line, t_map *yback_map)
{
	char	*joined_line;

	if (yback_map->north_path == NULL
		|| yback_map->south_path == NULL
		|| yback_map->west_path == NULL
		|| yback_map->east_path == NULL
		|| yback_map->flag != 2)
	{
		free(line);
		error_handle("Error: Element missing!\n", map_line, yback_map);
	}
	joined_line = ft_strjoin(map_line, line);
	return (joined_line);
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
		j = 0;
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

int	yb_map_check_split(char *map_line)
{
	char	**splitted_map;
	int		line_size;
	int		i;
	int		error_check;

	i = -1;
	error_check = 0;
	splitted_map = ft_split(map_line, ' ');
	while (splitted_map[++i])
	{
		line_size = ft_strlen(splitted_map[i]);
		if (splitted_map[i][0] == '0' || splitted_map[i][line_size - 1] == '0')
		{
			error_check = -1;
			break;
		}
	}
	free_arr(splitted_map);
	return (error_check);
}

int	yb_wall_check(t_map *yback_map, int i, int j)
{
	char	u;
	char	d;

	if (i == 0 || i == yback_map->map_height - 1)
		return (-1);
	else
	{
		u = yback_map->map[i - 1][j];
		d = yback_map->map[i + 1][j];
		if (!(u == 'N' || u == 'S' || u == 'E' || u == 'W'
			|| u == '1' || u == '0' || d == '1' || d == '0'
			|| d == 'N' || d == 'S' || d == 'E' || d == 'W'))
			return (-1);
	}
	return (0);
}

int	yb_find_player_pos(t_map *yback_map, int i, int j)
{
	char	c;

	c = yback_map->map[i][j];
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (yback_map->player_pos[0] > 0)
			return (-1);
		yback_map->player_dir = c;
		yback_map->player_pos[0] = i;
		yback_map->player_pos[1] = j;
		return (yb_wall_check(yback_map, i, j));
	}
	else if (!(c == '1' || c == '0' || c == ' '))
		return (-1);
	else if (c == '0')
		return (yb_wall_check(yback_map, i, j));
	return (0);
}

int	yb_find_player(t_map *yback_map)
{
	int	i;
	int	j;
	int	error_check;
	
	i = 0;
	error_check = 0;
	while (yback_map->map[i])
	{
		error_check = yb_map_check_split(yback_map->map[i]);
		if (error_check == -1)
			return (-1);
		j = 0;
		while (yback_map->map[i][j])
		{
			error_check = yb_find_player_pos(yback_map, i, j);
			if (error_check == -1)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	yb_check_info(t_map *yback_map)
{
	if (yb_strslen(yback_map->map) <= 1)
		return (-1);
	return (0);
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

void	init_map_with_file(char *file_name, t_map *yback_map)
{
	int 	fd;
	int		error_check;
	char	*line;
	char	*map_line;

	error_check = 0;
	map_line = malloc(10000);
	if (!map_line)
		error_handle("Error: map_line malloc error!\n", map_line, yback_map);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error_handle("Error: Can't open file.", map_line, yback_map);
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
		{
			free(line);
			error_handle("Error: .cub file error!\n", map_line, yback_map);
		}
		free(line);
	}
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
	init_map_with_file("./maps/s1.cub", yback_map);
	// init_map_with_file("./maps/s2.cub", yback_map);
	yb_print_structure(yback_map);
	free_yback(yback_map);
	system("leaks cub3D");
}