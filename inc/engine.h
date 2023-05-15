/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongspa <seongspa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:30:34 by seongspa          #+#    #+#             */
/*   Updated: 2023/05/03 20:19:00 by seongspa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# define WINDOW_W	(800)
# define WINDOW_H	(600)

# include "key_macos.h"
# include "map.h"
# include "display.h"
# include "camera.h"
# include "texture.h"

typedef struct s_engine
{
	void		*ctx;
	void		*window;
	t_map		*map;
	t_display	display;
	t_camera	cam;
	t_texture	texs[4];
}	t_engine;

void	destroy_engine(t_engine *eng);
int		expose_hook(t_engine *egn);
int		close_hook(t_engine *egn);
int		key_hook(int key, t_engine *egn);

#endif