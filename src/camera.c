#include <math.h>
#include "camera.h"

void	init_cam(t_camera *cam, t_map *map)
{
	cam->pos_x = map->player_pos[1];
	cam->pos_y = map->player_pos[0];
	cam->dir_x = 0 * (map->player_dir == 'N') \
		+ 1 * (map->player_dir == 'E') \
		+ 0 * (map->player_dir == 'S') \
		+ -1 * (map->player_dir == 'W');
	cam->dir_y = -1 * (map->player_dir == 'N') \
		+ 0 * (map->player_dir == 'E') \
		+ 1 * (map->player_dir == 'S') \
		+ 0 * (map->player_dir == 'W');
	cam->plane_x = 0.66 * (map->player_dir == 'N') \
		+ 0 * (map->player_dir == 'E') \
		+ -0.66 * (map->player_dir == 'S') \
		+ 0 * (map->player_dir == 'W');
	cam->plane_y = 0 * (map->player_dir == 'N') \
		+ 0.66 * (map->player_dir == 'E') \
		+ 0 * (map->player_dir == 'S') \
		+ -0.66 * (map->player_dir == 'W');
	cam->move_speed = 0.05;
	cam->rot_speed = 0.05;
}

void    move(t_camera *cam, t_map *map, double move_speed)
{
	int	y;
	int	x;

	y = (int)(cam->pos_y);
	x = (int)(cam->pos_x + cam->dir_x * move_speed);
	if (map->map[y][x] != '1')
		cam->pos_x += cam->dir_x * move_speed;
	y = (int)(cam->pos_y + cam->dir_y * move_speed);
	x = (int)(cam->pos_x);
	if (map->map[y][x] != '1')
		cam->pos_y += cam->dir_y * move_speed;
}

void    turn(t_camera *cam, double theta)
{
	double old_dir_x = cam->dir_x;
	cam->dir_x = cam->dir_x * cos(theta) - cam->dir_y * sin(theta);
	cam->dir_y = old_dir_x * sin(theta) + cam->dir_y * cos(theta);
	double old_plane_x = cam->plane_x;
	cam->plane_x = cam->plane_x * cos(theta) - cam->plane_y * sin(theta);
	cam->plane_y = old_plane_x * sin(theta) + cam->plane_y * cos(theta);
}