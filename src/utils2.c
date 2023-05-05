/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:30:40 by yback             #+#    #+#             */
/*   Updated: 2023/05/05 19:45:14 by yback            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

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