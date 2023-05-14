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