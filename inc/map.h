/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:24:55 by seongspa          #+#    #+#             */
/*   Updated: 2023/05/04 18:31:37 by yback            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

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

#endif