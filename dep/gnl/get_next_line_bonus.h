/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 20:22:09 by yback             #+#    #+#             */
/*   Updated: 2022/08/10 20:11:41 by yback            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

char	*ft_strchr(char *s, int c);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*making_backup(int fd, char *backup);
char	*making_newbackup(char *backup);
char	*making_ans(char *backup);
char	*get_next_line(int fd);
char	*free_null(char **arr);

#endif