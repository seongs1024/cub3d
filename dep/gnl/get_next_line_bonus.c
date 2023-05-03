/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:15:32 by yback             #+#    #+#             */
/*   Updated: 2023/05/03 23:07:25 by yback            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

char	*ft_strchr(char *s, int c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*making_backup(int fd, char *backup);
char	*making_newbackup(char *backup);
char	*making_ans(char *backup);


char	*free_null(char **arr)
{
	if (*arr)
		free(*arr);
	*arr = 0;
	return (*arr);
}

char	*making_backup(int fd, char *backup)
{
	char		*tmp;
	int			num;

	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (0);
	num = 1;
	while (!ft_strchr(backup, '\n') && num)
	{
		num = read(fd, tmp, BUFFER_SIZE);
		if (num == -1)
		{
			free_null(&tmp);
			return (0);
		}
		tmp[num] = 0;
		backup = ft_strjoin(backup, tmp);
	}
	free_null(&tmp);
	return (backup);
}

char	*making_newbackup(char *backup)
{
	char	*newbackup;
	int		i;
	int		j;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	newbackup = malloc(ft_strlen(backup) - i + 1);
	if (!newbackup)
		return (0);
	if (backup[i] != '\n')
		free_null(&newbackup);
	else
	{
		i++;
		j = 0;
		while (backup[i])
			newbackup[j++] = backup[i++];
		newbackup[j] = 0;
	}
	free_null(&backup);
	return (newbackup);
}

char	*making_ans(char *backup)
{
	int		i;
	char	*ans;

	i = 0;
	if (!backup[i])
		return (0);
	while (backup[i] && backup[i] != '\n')
		i++;
	ans = (char *)malloc(i + 2);
	if (!ans)
		return (0);
	i = 0;
	while (backup[i] != '\n' && backup[i])
	{
		ans[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
		ans[i++] = '\n';
	ans[i] = 0;
	return (ans);
}

char	*get_next_line(int fd)
{
	static char	*backup[49152];
	char		*ans;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, backup[fd], 0) == -1)
	{
		if (backup[fd])
			free_null(&backup[fd]);
		return (0);
	}
	backup[fd] = making_backup(fd, backup[fd]);
	if (!backup[fd])
	{
		free_null(&backup[fd]);
		return (0);
	}
	ans = making_ans(backup[fd]);
	backup[fd] = making_newbackup(backup[fd]);
	return (ans);
}
