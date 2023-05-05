/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:28:36 by yback             #+#    #+#             */
/*   Updated: 2023/05/05 19:38:31 by yback            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

size_t	yb_strslen(char **strs)
{
	size_t	len;

	len = 0;
	while (strs[len])
		len++;
	return (len);
}

int	yb_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;

	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	yb_atoi_check(char *spl_color)
{
	int	num;

	num = ft_atoi(spl_color);
	if (!(0 <= num && num <= 255))
		return (-123);
	return (num);
}

int	yb_check_int(char **spl_color)
{
	int	i;

	i = -1;
	while (spl_color[++i])
	{
		if (ft_strchr(spl_color[i], '.') != 0)
			return (-1);
	}
	return (0);
}