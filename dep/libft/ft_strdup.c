/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:32:51 by yback             #+#    #+#             */
/*   Updated: 2022/07/12 14:38:17 by yback            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*arr;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	arr = (char *)malloc(sizeof(char) * i + 1);
	if (!arr)
		return (0);
	i = 0;
	while (s1[i])
	{
		arr[i] = s1[i];
		i++;
	}
	arr[i] = 0;
	return (arr);
}
