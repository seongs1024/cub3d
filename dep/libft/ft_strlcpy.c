/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:01:41 by yback             #+#    #+#             */
/*   Updated: 2022/07/12 15:57:03 by yback            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	cnt;

	cnt = 0;
	if (size > 0)
	{
		while (src[cnt] && cnt < size - 1)
		{
			dst[cnt] = src[cnt];
			cnt++;
		}
		dst[cnt] = '\0';
	}
	while (src[cnt])
		cnt++;
	return (cnt);
}
