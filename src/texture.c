#include "mlx.h"
#include "texture.h"

int	load_texture(void *ctx, char *path, t_texture *texture)
{
	texture->img = mlx_xpm_file_to_image(ctx, path, &texture->width, &texture->height);
	if (!texture->img)
		return (-1);
	texture->addr = (int *)mlx_get_data_addr(
		texture->img, \
		&texture->bits_per_pixel, \
		&texture->line_length, \
		&texture->endian);
	return (0);
}

int	init_textures(void *ctx, char **map_path, t_texture *texs)
{
	if (load_texture(ctx, map_path[0], &texs[0]) || \
		load_texture(ctx, map_path[1], &texs[1]) || \
		load_texture(ctx, map_path[2], &texs[2]) || \
		load_texture(ctx, map_path[3], &texs[3]))
	{
		return (-1);
	}
	return (0);
}

int	color(t_texture *texture, int x, int y)
{
	return (texture->addr[texture->height * y + x]);
}