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

t_camera temp_cam(t_map *map)
{
	t_camera	cam;

	cam.pos_x = map->player_pos[0];
	cam.pos_y = map->player_pos[0];
	cam.dir_x = -1; // [TODO] replace it w.r.t. player_dir of map
	cam.dir_y = 0;
	cam.plane_x = 0;
	cam.plane_y = 0.66;
	cam.move_speed = 0.05;
	cam.rot_speed = 0.05;
	return (cam);
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

	engine.cam = temp_cam(engine.map);

	mlx_key_hook(engine.window, &key_hook, &engine);
	mlx_hook(engine.window, EVENT_EXIT, 0, &close_hook, &engine);
	mlx_loop_hook(engine.ctx, &frame_loop, &engine);
	mlx_loop(engine.ctx);
	return (0);
}
