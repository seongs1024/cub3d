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
#include "mlx.h"
#include "engine.h"

void	destroy_engine(t_engine *eng)
{
	if (eng->window)
	{
		mlx_destroy_window(eng->ctx, eng->window);
		eng->window = 0;
	}
	system("leaks cub3D");
	exit(0);
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
	mlx_clear_window(egn->ctx, egn->window);
	if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
	{
		/* move camera */
	}
	else if (key == KEY_ESCAPE)
		close_hook(egn);
	return (0);
}

int	render_loop(t_engine *egn)
{
	static int	time;

	time++;
	if (egn && time % 10000 == 0)
		printf("== TIME %d ==\n", time / 10000);
	return (0);
}
