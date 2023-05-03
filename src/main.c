/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongspa <seongspa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:29:02 by seongspa          #+#    #+#             */
/*   Updated: 2023/05/03 20:01:37 by seongspa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "engine.h"

int	main(void)
{
	t_engine	engine;

	engine.ctx = mlx_init();
	engine.window = mlx_new_window(engine.ctx, WINDOW_W, WINDOW_H, "cub3D");
	mlx_key_hook(engine.window, &key_hook, &engine);
	mlx_hook(engine.window, EVENT_EXIT, 0, &close_hook, &engine);
	mlx_loop_hook(engine.ctx, &render_loop, &engine);
	mlx_loop(engine.ctx);
	return (0);
}
