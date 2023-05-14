#include <math.h>
#include "camera.h"

void    move_forward(t_camera *cam, t_map *map)
{
    // [TODO]: out of indexing
    if (map->map[(int)(cam->pos_y)][(int)(cam->pos_x + cam->dir_x * cam->move_speed)] != '1')
        cam->pos_x += cam->dir_x * cam->move_speed;
    if (map->map[(int)(cam->pos_y + cam->dir_y * cam->move_speed)][(int)(cam->pos_x)] != '1')
        cam->pos_y += cam->dir_y * cam->move_speed;
}

void    move_backward(t_camera *cam, t_map *map)
{
    if (map->map[(int)(cam->pos_y)][(int)(cam->pos_x - cam->dir_x * cam->move_speed)] != '1')
        cam->pos_x -= cam->dir_x * cam->move_speed;
    if (map->map[(int)(cam->pos_y - cam->dir_y * cam->move_speed)][(int)(cam->pos_x)] != '1')
        cam->pos_y -= cam->dir_y * cam->move_speed;
}

void    turn_left(t_camera *cam)
{
    double old_dir_x = cam->dir_x;
    cam->dir_x = cam->dir_x * cos(-cam->rot_speed) - cam->dir_y * sin(-cam->rot_speed);
    cam->dir_y = old_dir_x * sin(-cam->rot_speed) + cam->dir_y * cos(-cam->rot_speed);
    double old_plane_x = cam->plane_x;
    cam->plane_x = cam->plane_x * cos(-cam->rot_speed) - cam->plane_y * sin(-cam->rot_speed);
    cam->plane_y = old_plane_x * sin(-cam->rot_speed) + cam->plane_y * cos(-cam->rot_speed);
}

void    turn_right(t_camera *cam)
{
    double old_dir_x = cam->dir_x;
    cam->dir_x = cam->dir_x * cos(cam->rot_speed) - cam->dir_y * sin(cam->rot_speed);
    cam->dir_y = old_dir_x * sin(cam->rot_speed) + cam->dir_y * cos(cam->rot_speed);
    double old_plane_x = cam->plane_x;
    cam->plane_x = cam->plane_x * cos(cam->rot_speed) - cam->plane_y * sin(cam->rot_speed);
    cam->plane_y = old_plane_x * sin(cam->rot_speed) + cam->plane_y * cos(cam->rot_speed);
}