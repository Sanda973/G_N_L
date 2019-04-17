/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgury <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:07:57 by sgury             #+#    #+#             */
/*   Updated: 2019/04/17 10:01:03 by sgury            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# define BUFF_SIZE 100
# define FD_MAX 4864

int		get_next_line(const int fd, char **line);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnew(size_t size);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strchr(const char *s, int c);
void	ft_strdel(char **as);

#endif
