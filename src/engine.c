/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongspa <seongspa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:45:42 by seongspa          #+#    #+#             */
/*   Updated: 2023/05/03 19:56:48 by seongspa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "engine.h"

void	destroy_engine(t_engine *egn)
{
	if (egn->display.img)
	{
		mlx_destroy_image(egn->ctx, egn->display.img);
		egn->display.img = 0;
	}
	if (egn->textures[0].img)
	{
		mlx_destroy_image(egn->ctx, egn->textures[0].img);
		egn->textures[0].img = 0;
	}
	if (egn->textures[1].img)
	{
		mlx_destroy_image(egn->ctx, egn->textures[1].img);
		egn->textures[1].img = 0;
	}
	if (egn->textures[2].img)
	{
		mlx_destroy_image(egn->ctx, egn->textures[2].img);
		egn->textures[2].img = 0;
	}
	if (egn->textures[3].img)
	{
		mlx_destroy_image(egn->ctx, egn->textures[3].img);
		egn->textures[3].img = 0;
	}
	if (egn->window)
	{
		mlx_destroy_window(egn->ctx, egn->window);
		egn->window = 0;
	}
	system("leaks cub3D");
	exit(0);
}

int	expose_hook(t_engine *egn)
{
	printf("EXPOSE!\n");
	render_map_3d(&egn->display, &egn->cam, egn->map, WINDOW_W, WINDOW_H, egn->textures);
	mlx_put_image_to_window(egn->ctx, egn->window, egn->display.img, 0, 0);
	return (0);
}

int	close_hook(t_engine *egn)
{
	printf("EXIT!\n");
	destroy_engine(egn);
	return (0);
}

int	key_hook(int key, t_engine *egn)
{
	printf("KEY STROKE: %d\n", key);
	if (key == KEY_W)
		move(&egn->cam, egn->map, egn->cam.move_speed);
	else if (key == KEY_S)
		move(&egn->cam, egn->map, -egn->cam.move_speed);
	else if (key == KEY_A)
		turn(&egn->cam, -egn->cam.rot_speed);
	else if (key == KEY_D)
		turn(&egn->cam, egn->cam.rot_speed);
	else if (key == KEY_ESCAPE)
		close_hook(egn);
	render_map_3d(&egn->display, &egn->cam, egn->map, WINDOW_W, WINDOW_H, egn->textures);
	mlx_put_image_to_window(egn->ctx, egn->window, egn->display.img, 0, 0);
	return (0);
}

int	frame_loop(t_engine *egn)
{
	static int	time;

	time++;
	if (egn && time % 10000 == 0)
		printf("== TIME %d ==\n", time / 10000);
	return (0);
}
