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

#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "engine.h"

void	destroy_engine(t_engine *egn)
{
	if (egn->display.img)
		mlx_destroy_image(egn->ctx, egn->display.img);
	if (egn->texs[0].img)
		mlx_destroy_image(egn->ctx, egn->texs[0].img);
	if (egn->texs[1].img)
		mlx_destroy_image(egn->ctx, egn->texs[1].img);
	if (egn->texs[2].img)
		mlx_destroy_image(egn->ctx, egn->texs[2].img);
	if (egn->texs[3].img)
		mlx_destroy_image(egn->ctx, egn->texs[3].img);
	if (egn->window)
		mlx_destroy_window(egn->ctx, egn->window);
	// if (egn->map)
	// 	free_yback(egn->map);
	system("leaks cub3D");
	exit(0);
}

int	expose_hook(t_engine *egn)
{
	render_map(&egn->display, &egn->cam, egn->map, egn->texs);
	mlx_put_image_to_window(egn->ctx, egn->window, egn->display.img, 0, 0);
	return (0);
}

int	close_hook(t_engine *egn)
{
	destroy_engine(egn);
	return (0);
}

int	key_hook(int key, t_engine *egn)
{
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
	render_map(&egn->display, &egn->cam, egn->map, egn->texs);
	mlx_put_image_to_window(egn->ctx, egn->window, egn->display.img, 0, 0);
	return (0);
}