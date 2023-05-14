#include <math.h>
#include "display.h"

int	rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

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

void	render_floor_and_ceiling(t_display *dis, int width, int height, t_map *map)
{
	int	x;

	x = 0;
	while (x < width)
	{
		render_vertical_line(dis, x, 0, height / 2, rgb_to_int(map->c_colors[0], map->c_colors[1], map->c_colors[2]));
		render_vertical_line(dis, x, height / 2, height - 1, rgb_to_int(map->f_colors[0], map->f_colors[1], map->f_colors[2]));
		x++;
	}
}

void	render_map_3d(t_display *dis, t_camera *cam, t_map *map, int width, int height, t_texture *texs)
{
	int	x;

	render_floor_and_ceiling(dis, width, height, map);
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

		// calculate value of wall_x
		double wall_x;
		if (side == 3 || side == 1)
			wall_x = cam->pos_y + perp_wall_dist * ray_dir_y;
		else
			wall_x = cam->pos_x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);

		// x coordinate on the texture
		int tex_x = (int)(wall_x * (double)texs[side].width);
		if ((side == 3 || side == 1) && ray_dir_x < 0)
			tex_x = texs[side].width - tex_x - 1;
		if ((side == 0 || side == 2) && ray_dir_y > 0)
			tex_x = texs[side].width - tex_x - 1;

		// How much to increase the texture coordinate perscreen pixel
		double step = 1.0 * texs[side].height / line_height;
		// Starting texture coordinate
		double tex_pos = (draw_start - height / 2 + line_height / 2) * step;
		for (int y = draw_start; y < draw_end; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texs[side].height - 1) in case of overflow
			int tex_y = (int)tex_pos & (texs[side].height - 1);
			tex_pos += step;
			int color = texs[side].addr[texs[side].height * tex_y + tex_x];
			pixel_put(dis, x, y, color);
		}
		
		x++;
	}
}