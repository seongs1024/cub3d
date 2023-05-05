#include "display.h"

void	pixel_put(t_display *dis, int x, int y, int color)
{
	char	*dst;

	dst = dis->addr + (y * dis->line_length + x * (dis->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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