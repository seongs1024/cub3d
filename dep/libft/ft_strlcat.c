/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:17:11 by yback             #+#    #+#             */
/*   Updated: 2022/07/12 15:03:38 by yback            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	if (dstsize > 0)
	{	
		while (*src && i < dstsize - 1)
			dst[i++] = *src++;
		if (i < dstsize)
			dst[i] = '\0';
	}
	while (*src++)
		i++;
	return (i);
}
