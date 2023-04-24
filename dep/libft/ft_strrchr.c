/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:41:24 by yback             #+#    #+#             */
/*   Updated: 2022/07/12 19:40:01 by yback            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*start;

	start = (char *)s;
	i = 0;
	while (*s++)
		;
	while (--s != start && *s != (char)c)
		;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
