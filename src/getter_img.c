/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:33:57 by yback             #+#    #+#             */
/*   Updated: 2023/05/15 14:02:06 by yback            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

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
