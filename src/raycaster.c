/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongspa <seongspa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:30:30 by seongspa          #+#    #+#             */
/*   Updated: 2023/05/15 13:38:56 by seongspa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "raycaster.h"

void	cast_ray(t_raycaster *rc, t_camera *cam, int x, t_display *dis)
{
	double	cam_x;

	cam_x = 2 * x / (double)dis->width - 1;
	rc->dir[0] = cam->dir_x + cam->plane_x * cam_x;
	rc->dir[1] = cam->dir_y + cam->plane_y * cam_x;
	rc->map_pos[0] = (int)cam->pos_x;
	rc->map_pos[1] = (int)cam->pos_y;
	if (rc->dir[0] != 0)
		rc->delta_dist[0] = fabs(1 / rc->dir[0]);
	else
		rc->delta_dist[0] = 1e30;
	if (rc->dir[1] != 0)
		rc->delta_dist[1] = fabs(1 / rc->dir[1]);
	else
		rc->delta_dist[1] = 1e30;
	rc->step[0] = -1 * (rc->dir[0] < 0) + 1 * (rc->dir[0] >= 0);
	rc->side_dist[0] = ((cam->pos_x - rc->map_pos[0]) * (rc->dir[0] < 0) \
		+ (rc->map_pos[0] + 1.0 - cam->pos_x) * (rc->dir[0] >= 0)) \
		* rc->delta_dist[0];
	rc->step[1] = -1 * (rc->dir[1] < 0) + 1 * (rc->dir[1] >= 0);
	rc->side_dist[1] = ((cam->pos_y - rc->map_pos[1]) * (rc->dir[1] < 0) \
		+ (rc->map_pos[1] + 1.0 - cam->pos_y) * (rc->dir[1] >= 0)) \
		* rc->delta_dist[1];
}

int	hit_wall(t_raycaster *rc, t_map *map)
{
	int	hit;
	int	wall_type;

	hit = 0;
	while (hit == 0)
	{
		if (rc->side_dist[0] < rc->side_dist[1])
		{
			rc->side_dist[0] += rc->delta_dist[0];
			rc->map_pos[0] += rc->step[0];
			wall_type = 3 * (rc->dir[0] < 0) + 1 * (rc->dir[0] >= 0);
		}
		else
		{
			rc->side_dist[1] += rc->delta_dist[1];
			rc->map_pos[1] += rc->step[1];
			wall_type = 0 * (rc->dir[1] < 0) + 2 * (rc->dir[1] >= 0);
		}
		if (map->map[rc->map_pos[1]][rc->map_pos[0]] == '1')
			hit = 1;
	}
	return (wall_type);
}

void	measure_vline(t_raycaster *rc, int wall, t_display *dis)
{
	rc->wall_dist = (rc->side_dist[0] - rc->delta_dist[0]) * (wall % 2) \
		+ (rc->side_dist[1] - rc->delta_dist[1]) * ((wall + 1) % 2);
	rc->vline_h = (int)(dis->height / rc->wall_dist);
	rc->vline[0] = fmax(-rc->vline_h / 2 + dis->height / 2, 0);
	rc->vline[1] = fmin(rc->vline_h / 2 + dis->height / 2, dis->height - 1);
}

void	measure_tex(t_raycaster *rc, int wall, t_texture *tex, t_camera *cam)
{
	double	wall_x;

	wall_x = (cam->pos_y + rc->wall_dist * rc->dir[1]) * (wall % 2) \
		+ (cam->pos_x + rc->wall_dist * rc->dir[0]) * ((wall + 1) % 2);
	wall_x -= floor(wall_x);
	rc->tex[0] = (int)(wall_x * (double)tex->width);
	if ((wall == 3 || wall == 1) && rc->dir[0] < 0)
		rc->tex[0] = tex->width - rc->tex[0] - 1;
	if ((wall == 0 || wall == 2) && rc->dir[1] > 0)
		rc->tex[0] = tex->width - rc->tex[0] - 1;
	rc->tex_step = 1.0 * tex->height / rc->vline_h;
}
