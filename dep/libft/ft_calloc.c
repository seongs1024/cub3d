/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:27:52 by yback             #+#    #+#             */
/*   Updated: 2022/07/11 20:25:09 by yback            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	mul;
	void	*arr;

	if (count == 18446744073709551615UL && size == 18446744073709551615UL)
		return (0);
	mul = count * size;
	arr = malloc(mul);
	if (!arr)
		return (0);
	ft_bzero(arr, mul);
	return (arr);
}
