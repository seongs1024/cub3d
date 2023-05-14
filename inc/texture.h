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

int	load_texture(void *ctx, char *path, t_texture *texture);
int	color(t_texture *texture, int x, int y);

#endif