/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:24:55 by seongspa          #+#    #+#             */
/*   Updated: 2023/05/05 19:04:22 by yback            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stdlib.h>
# include <stdio.h>
#include <fcntl.h>

typedef struct s_map
{
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	int		f_colors[3];
	int		c_colors[3];
	int		flag;

	int		map_width;
	int		map_height;
	char	**map;

	int		player_pos[2];
	char	player_dir;
}	t_map;

void	error_handle(char *msg, char *map_line, t_map *yback_map);
void	free_arr(char **arr);
void	free_yback(t_map *yback_map);


#endif