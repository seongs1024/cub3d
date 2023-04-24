/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:35:22 by yback             #+#    #+#             */
/*   Updated: 2022/07/12 11:55:01 by yback            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned int	num;
	unsigned char	*arr;

	num = (unsigned char)c;
	arr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (arr[i] == num)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
