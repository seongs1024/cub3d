/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongspa <seongspa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:30:52 by seongspa          #+#    #+#             */
/*   Updated: 2023/05/15 13:30:52 by seongspa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "map.h"
# include "camera.h"
# include "texture.h"

typedef struct s_display
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_display;

void	init_display( void *ctx, t_display *dis, int width, int height);
void	render_map(t_display *dis, t_camera *cam, t_map *map, t_texture *texs);

#endif