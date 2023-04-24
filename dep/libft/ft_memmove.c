/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 17:05:57 by yback             #+#    #+#             */
/*   Updated: 2022/07/12 13:42:14 by yback            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (src < dst && dst < src + len)
	{
		while (len > 0)
		{
			--len;
			((unsigned char *)dst)[len] = ((const unsigned char *)src)[len];
		}
		return (dst);
	}
	return (ft_memcpy(dst, src, len));
}
