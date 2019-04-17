/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgury <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:06:12 by sgury             #+#    #+#             */
/*   Updated: 2019/04/17 10:14:02 by sgury            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_line_len(char *content)
{
	int	len;

	len = 0;
	while (content[len] != '\n' && content[len] != '\0')
		len++;
	if (len == 0 && content[len] == '\n')
		return (1);
	if (content[len] == '\n')
		return (len);
	return (-1);
}

static int	ft_get_new_content(const int fd, char **content)
{
	char	buff[BUFF_SIZE + 1];
	char	*tmp;
	int		ret;

	ret = read(fd, buff, BUFF_SIZE);
	if (ret < 0)
		return (ret);
	buff[BUFF_SIZE] = '\0';
	if ((tmp = ft_strjoin(*content, buff)) == NULL)
		return (-1);
	*content = tmp;
	return (ret);
}

static char	*ft_get_new_line(char *content, char *line, int len)
{
	char	*tmp;

	if ((tmp = ft_strnew(len)) == NULL)
		return (NULL);
	ft_memmove(tmp, content, len);
	tmp[len] = '\0';
	line = tmp;
	ft_strdel(&tmp);
	return (line);
}

int			get_next_line(const int fd, char **line)
{
	static char	*content;
	char		*tmp;
	int			line_len;
	int			buff_ret;

	line_len = 0;
	buff_ret = 0;
	if (line == NULL || fd < 0 || BUFF_SIZE < 1 || fd > FD_MAX)
		return (-1);
	if (content == NULL)
		buff_ret = ft_get_new_content(fd, &content);
	while ((line_len = ft_line_len(content)) < 1)
		if ((buff_ret = ft_get_new_content(fd, &content)) == 0)
			break ;
	if (buff_ret < 0)
		return (-1);
	if (buff_ret == 0 && line_len < 1)
		return (0);
	if (content != NULL)
		if ((*line = ft_get_new_line(content, *line, line_len)) == NULL)
			return (-1);
	tmp = ft_strchr(content, '\n');
	content = tmp + 1;
	return (1);
}
