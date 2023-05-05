#ifndef DISPLAY_H
# define DISPLAY_H

# include "map.h"
# include "camera.h"

typedef struct s_display
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_display;

void	render_map(t_display *dis, t_map *map);
void	render_map_3d(t_display *dis, t_camera *cam, t_map *map, int width, int height);

#endif