/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:37:43 by yback             #+#    #+#             */
/*   Updated: 2023/05/03 23:15:45 by yback            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "get_next_line_bonus.h"
#include "libft.h"
#include <stdio.h>
#include <fcntl.h>

void	input_file(char *file_name)
{
	int 	fd;
	char	*line;
	char	**splitted_line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror("Error: Can not open file.");
		exit(1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		splitted_line = ft_split(line, ' ');
		printf("%s %s\n", splitted_line[0], splitted_line[1]);
	}
}

int main()
{
	t_map	*yback_map;

	ft_memset(&yback_map, 0, sizeof(yback_map));
	input_file("../maps/e3-no-wall2.cub");
}