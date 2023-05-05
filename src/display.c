#include <math.h>
#include "display.h"

void	pixel_put(t_display *dis, int x, int y, int color)
{
	char	*dst;

	dst = dis->addr + (y * dis->line_length + x * (dis->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	pixel_clear(t_display *dis, int width, int height, int color)
{
	char	*dst;
	while (--width >= 0)
	{
		int		h = height;
		while (--h >= 0)
		{
			dst = dis->addr + (h * dis->line_length + width * (dis->bits_per_pixel / 8));
			*(unsigned int*)dst = color;
		}
	}
}

void	render_map(t_display *dis, t_map *map)
{
	for (int j = 0; j < map->map_height; j++)
	{
		for (int i = 0; i < map->map_width; i++)
		{
			const int RECT = 20;
			if (map->map[j][i] == '1')
			{
				for (int k = 0; k < RECT; k++)
				{
					for (int l = 0; l < RECT; l++)
					{
						pixel_put(dis, RECT * i + k, RECT * j + l, 0x00FF0000);
					}
				}
			}
			else if (map->map[j][i] == '0')
			{
				for (int k = 0; k < RECT; k++)
				{
					for (int l = 0; l < RECT; l++)
					{
						pixel_put(dis, RECT * i + k, RECT * j + l, 0x00FFFFFF);
					}
				}
			}
		}
	}

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

void	render_map_3d(t_display *dis, t_camera *cam, t_map *map, int width, int height)
{
	int	x;

	pixel_clear(dis, width, height, 0x000000);
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
		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);
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
			side_dist_x = (map_x + 1.0 - cam->pos_y) * delta_dist_x;
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
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			//Check if ray has hit a wall
			if (map->map[map_x][map_y] != '0') hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (map_x - cam->pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - cam->pos_y + (1 - step_y) / 2) / ray_dir_y;

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
		if (map->map[map_y][map_x] == '1')
			color = 0xFF0000;
		else if (map->map[map_y][map_x] == 'N')
			color = 0xFFFF00;
		else
			color = 0xFFFFFF;
		
		if (side == 1)
			color = color / 2;

		render_vertical_line(dis, x, draw_start, draw_end, color);
		
		x++;
	}
}