/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 16:53:20 by yback             #+#    #+#             */
/*   Updated: 2022/07/12 15:59:20 by yback            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*arr;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (0);
	arr = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!arr)
		return (0);
	while (s[i])
	{
		arr[i] = f(i, s[i]);
		i++;
	}
	arr[i] = 0;
	return (arr);
}
