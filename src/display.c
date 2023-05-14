#include <math.h>
#include "display.h"

#define COLOR_FLOOR		(0xE7B2FE)
#define COLOR_CEILING	(0xE7B201)

void	pixel_put(t_display *dis, int x, int y, int color)
{
	char	*dst;

	dst = dis->addr + (y * dis->line_length + x * (dis->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	render_vertical_line(t_display *dis, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		pixel_put(dis, x, y, color);
		y++;
	}
}

void	render_floor_and_ceiling(t_display *dis, int width, int height)
{
	int	x;

	x = 0;
	while (x < width)
	{
		render_vertical_line(dis, x, 0, height / 2, COLOR_CEILING);
		render_vertical_line(dis, x, height / 2, height - 1, COLOR_FLOOR);
		x++;
	}
}

void	render_map_3d(t_display *dis, t_camera *cam, t_map *map, int width, int height)
{
	int	x;

	render_floor_and_ceiling(dis, width, height);
	x = 0;
	while (x < width)
	{
		double cam_x = 2 * x / (double)width - 1;
		double ray_dir_x = cam->dir_x + cam->plane_x * cam_x;
		double ray_dir_y = cam->dir_y + cam->plane_y * cam_x;
		
		int map_x = (int)cam->pos_x;
		int map_y = (int)cam->pos_y;

		//length of ray from current position to next x or y-side
		double side_dist_x;
		double side_dist_y;
		
		 //length of ray from one x or y-side to next x or y-side
		double delta_dist_x;
		if (ray_dir_x != 0)
			delta_dist_x = fabs(1 / ray_dir_x);
		else
			delta_dist_x = 1e30;
		double delta_dist_y;
		if (ray_dir_y != 0)
			delta_dist_y = fabs(1 / ray_dir_y);
		else
			delta_dist_y = 1e30;
		double perp_wall_dist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int step_x;
		int step_y;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (cam->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - cam->pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (cam->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - cam->pos_y) * delta_dist_y;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				if (ray_dir_x < 0)
					side = 3;
				else
					side = 1;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				if (ray_dir_y < 0)
					side = 0;
				else
					side = 2;
			}
			//Check if ray has hit a wall
			// [TODO]: out of indexing
			if (map->map[map_y][map_x] == '1')
				hit = 1;
		}
		// ref: https://chichoon.tistory.com/m/429
		if (side == 3 || side == 1)
			perp_wall_dist = side_dist_x - delta_dist_x; //((map_x - cam->pos_x + (1 - step_x) / 2) / ray_dir_x);
		else
			perp_wall_dist = side_dist_y - delta_dist_y; // ((map_y - cam->pos_y + (1 - step_y) / 2) / ray_dir_y);

		//Calculate height of line to draw on screen
		int line_height = (int)(height / perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		int draw_start = -line_height / 2 + height / 2;
		if(draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + height / 2;
		if(draw_end >= height)
			draw_end = height - 1;

		int	color;
		if (side == 0)
			color = 0xFF0000;
		else if (side == 1)
			color = 0x00FF00;
		else if (side == 2)
			color = 0x0000FF;
		else if (side == 3)
			color = 0xFFFF00;
		else
			color = 0xFFFFFF;

		render_vertical_line(dis, x, draw_start, draw_end, color);
		
		x++;
	}
}