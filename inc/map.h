/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:24:55 by seongspa          #+#    #+#             */
/*   Updated: 2023/05/15 14:58:38 by yback            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "get_next_line_bonus.h"
# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# define TMP_MEM 2147483647

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

/* error_handler.c */
int		fnull(char *one);
void	error_handle(char *msg, char *map_line, t_map *yback_map);
void	free_arr(char **arr);
void	free_yback(t_map *yback_map);
void	yb_line_error_check(char *line, char *map_line, t_map *yback_map);

/* getter_color.c */
void	yb_init_colors(t_map *yback_map, int *colors, char **spl_color);
int		yb_color_check(int *colors);
int		yb_color_init(char **spl_line, t_map *yback_map);

/* getter_img.c */
int		yb_check_path_empty(char **yb_path, char *spl_line);
int		yb_path_init(char **spl_line, t_map *yback_map);

/* getter_map.c */
int		yb_map_check_split(char *map_line);
int		yb_wall_check(t_map *yback_map, int i, int j);
int		yb_check_info(t_map *yback_map);

/* getter_player.c */
int		yb_find_player_pos(t_map *yback_map, int i, int j);
int		yb_find_player(t_map *yback_map);

/* utils1.c */
size_t	yb_strslen(char **strs);
int		yb_strcmp(char *s1, char *s2);
int		yb_atoi_check(char *spl_color);
int		yb_check_int(char **spl_color);
int		yb_check_cub(char *file_ex);


/* utils2.c */
int		yb_isspace(char c);
char	*yb_trim(char *line);
int		yb_find_max_col(t_map *yback_map);
char	*yb_done_setting_element(char *line, char *map_line, t_map *yback_map);
t_map	*generate_map(char *file_name);

#endif