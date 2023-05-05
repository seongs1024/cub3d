#ifndef DISPLAY_H
# define DISPLAY_H

# include "map.h"

typedef struct s_display
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_display;

void	render_map(t_display *dis, t_map *map);

#endif