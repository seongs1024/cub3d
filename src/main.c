/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongspa <seongspa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:29:02 by seongspa          #+#    #+#             */
/*   Updated: 2023/05/03 20:46:55 by seongspa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "engine.h"

#include <stdlib.h>

t_map	*temp_map() {
	static char *maps[] = {
			"        1111111111111111111111111",
			"        1000000000110000000000001",
			"        1011000001110000000000001",
			"        1001000000000000000000001",
			"111111111011000001110000000000001",
			"100000000011000001110111111111111",
			"11110111111111011100000010001    ",
			"11110111111111011101010010001    ",
			"11000000110101011100000010001    ",
			"10000000000000001100000010001    ",
			"10000000000000001101010010001    ",
			"11000001110101011111011110N0111  ",
			"11110111 1110101 101111010001    ",
			"11111111 1111111 111111111111    ",
	};
	static t_map map = {
		.north_path = "./imgs/north.xpm",
		.south_path = "./imgs/south.xpm",
		.west_path = "./imgs/west.xpm",
		.east_path = "./imgs/east.xpm",
		.f_colors = {
			[0] = 220,
			[1] = 100,
			[2] = 0,
		},
		.c_colors = {
			[0] = 225,
			[1] = 30,
			[2] = 0,
		},
		.map_width = 33,
		.map_height = 14,
		.map = maps,
		.player_pos = {
			11,
			27,
		},
		.player_dir = 'N',
	};
	return (&map);
}

int	main(void)
{
	t_engine	engine;

	engine.ctx = mlx_init();
	engine.window = mlx_new_window(engine.ctx, WINDOW_W, WINDOW_H, "cub3D");

	engine.map = temp_map();

	engine.display.img = mlx_new_image(engine.ctx, WINDOW_W, WINDOW_H);
	engine.display.addr = mlx_get_data_addr(engine.display.img, \
		&engine.display.bits_per_pixel, \
		&engine.display.line_length, \
		&engine.display.endian);

	init_cam(&engine.cam, engine.map);

	if (load_texture(engine.ctx, engine.map->north_path, &engine.textures[0]) || \
		load_texture(engine.ctx, engine.map->east_path, &engine.textures[1]) || \
		load_texture(engine.ctx, engine.map->south_path, &engine.textures[2]) || \
		load_texture(engine.ctx, engine.map->west_path, &engine.textures[3]))
	{
		destroy_engine(&engine);
		return (1);
	}

	mlx_key_hook(engine.window, &key_hook, &engine);
	mlx_hook(engine.window, EVENT_EXPOSE, 0, &expose_hook, &engine);
	mlx_hook(engine.window, EVENT_EXIT, 0, &close_hook, &engine);
	mlx_loop_hook(engine.ctx, &frame_loop, &engine);
	mlx_loop(engine.ctx);
	return (0);
}
