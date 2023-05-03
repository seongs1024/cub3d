/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 20:22:09 by yback             #+#    #+#             */
/*   Updated: 2023/05/03 21:08:49 by yback            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

#include <stddef.h>

char	*ft_strchr(char *s, int c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(const char *s1, const char *s2);
char	*making_backup(int fd, char *backup);
char	*making_newbackup(char *backup);
char	*making_ans(char *backup);
char	*get_next_line(int fd);
char	*free_null(char **arr);

#endif