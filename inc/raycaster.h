#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "camera.h"
# include "display.h"
# include "map.h"

typedef struct s_raycaster
{
	double	dir[2];
	double	delta_dist[2];
	double	side_dist[2];
	double	wall_dist;
	double	tex_step;
	int		map_pos[2];
	int		step[2];
	int		vline_h;
	int		vline[2];
	int		tex[2];
}	t_raycaster;

void    cast_ray(t_raycaster *rc, t_camera *cam, int x, t_display *dis);
int		hit_wall(t_raycaster *rc, t_map *map);
void	measure_vline(t_raycaster *rc, int wall, t_display *dis);
void	measure_tex(t_raycaster *rc, int wall, t_texture *tex, t_camera *cam);

#endif