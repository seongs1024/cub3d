/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 16:00:32 by yback             #+#    #+#             */
/*   Updated: 2022/07/11 20:46:59 by yback            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	insize(long long num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		num *= -1;
		i++;
	}
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

void	func(char *arr, long long num, int size)
{
	if (num < 0)
		num *= -1;
	while (size >= 0)
	{
		arr[size--] = num % 10 + '0';
		num /= 10;
	}
}

char	*ft_itoa(int n)
{
	int			size;
	long long	num;
	char		*arr;

	num = n;
	size = insize(num);
	arr = (char *)malloc(sizeof(char) * size + 1);
	if (!arr)
		return (0);
	arr[size--] = '\0';
	if (n == 0)
	{
		arr[size] = '0';
		return (arr);
	}
	func(arr, num, size);
	if (n < 0)
		arr[0] = '-';
	return (arr);
}
