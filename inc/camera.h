/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongspa <seongspa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:13:56 by seongspa          #+#    #+#             */
/*   Updated: 2023/05/03 20:14:24 by seongspa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "map.h"

typedef struct s_camera
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}	t_camera;

void    move_forward(t_camera *cam, t_map *map);
void    move_backward(t_camera *cam, t_map *map);
void    turn_left(t_camera *cam);
void    turn_right(t_camera *cam);

#endif