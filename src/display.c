#include "mlx.h"
#include "display.h"
#include "raycaster.h"

void	init_display( void *ctx, t_display *dis, int width, int height)
{
	dis->img = mlx_new_image(ctx, width, height);
	dis->width = width;
	dis->height = height;
	dis->addr = mlx_get_data_addr(dis->img, \
		&dis->bits_per_pixel, \
		&dis->line_length, \
		&dis->endian);
}

void	pixel_put(t_display *dis, int x, int y, int color)
{
	char	*dst;

	dst = dis->addr + (y * dis->line_length + x * (dis->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	render_floor_and_ceiling(t_display *dis, t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (x < dis->width)
	{
		y = 0;
		while (y < (int)(dis->height / 2))
		{
			pixel_put(dis, x, y, 
				map->c_colors[0] << 16 | \
				map->c_colors[1] << 8 | \
				map->c_colors[2]);
			y++;
		}
		while (y < dis->height)
		{
			pixel_put(dis, x, y, 
				map->f_colors[0] << 16 | \
				map->f_colors[1] << 8 | \
				map->f_colors[2]);
			y++;
		}
		x++;
	}
}

void	render_map(t_display *dis, t_camera *cam, t_map *map, t_texture *texs)
{
	int			x;
	int			y;
	t_raycaster	rc;
	int			wall;
	double		addr;

	render_floor_and_ceiling(dis, map);
	x = 0;
	while (x < dis->width)
	{
		cast_ray(&rc, cam, x, dis);
		wall = hit_wall(&rc, map);
		measure_vline(&rc, wall, dis);
		measure_tex(&rc, wall, &texs[wall], cam);
		addr = (rc.vline[0] - dis->height / 2 + rc.vline_h / 2) * rc.tex_step;
		y = rc.vline[0];
		while (y < rc.vline[1])
		{
			rc.tex[1] = (int)addr & (texs[wall].height - 1);
			addr += rc.tex_step;
			pixel_put(dis, x, y, color(&texs[wall], rc.tex[0], rc.tex[1]));
			y++;
		}
		x++;
	}
}