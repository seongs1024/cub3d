#ifndef TEXTURE_H
# define TEXTURE_H

typedef struct s_texture
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}   t_texture;

int	init_textures(void *ctx, char **map_path, t_texture *texs);
int	color(t_texture *texture, int x, int y);

#endif