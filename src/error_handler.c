/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:24:17 by yback             #+#    #+#             */
/*   Updated: 2023/05/05 19:13:44 by yback            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	fnull(char *one)
{
	free(one);
	one = NULL;
}

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		fnull(arr[i]);
	free(arr);
	arr = NULL;
}

void	free_yback(t_map *yback_map)
{
	if (yback_map->north_path)
		fnull(yback_map->north_path);
	if (yback_map->south_path)
		fnull(yback_map->south_path);
	if (yback_map->west_path)
		fnull(yback_map->west_path);
	if (yback_map->east_path)
		fnull(yback_map->east_path);
	if (yback_map->map)
		free_arr(yback_map->map);
	free(yback_map);
	yback_map = NULL;
}

void	error_handle(char *msg, char *map_line, t_map *yback_map)
{
	perror(msg);
	fnull(map_line);
	free_yback(yback_map);
	system("leaks cub3D");
	exit(1);
}