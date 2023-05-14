#ifndef DISPLAY_H
# define DISPLAY_H

# include "map.h"
# include "camera.h"
# include "texture.h"

typedef struct s_display
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_display;

void	render_map(t_display *dis, t_camera *cam, t_map *map, t_texture *texs);

#endif