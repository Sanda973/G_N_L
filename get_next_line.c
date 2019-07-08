/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_new_version.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgury <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 13:26:19 by sgury             #+#    #+#             */
/*   Updated: 2019/07/05 16:19:58 by sgury            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_line_len(char *content)
{
	int	len;

	len = 0;
	while (content[len] != '\n' && content[len] != '\0')
		len++;
	if (content[len] == '\n' || content[len] == '\0')
		return (len);
	return (-1);
}

static int	ft_get_new_line(char **line, char **content, int fd, int len)
{
	char	*tmp;

	if (content[fd][len] == '\n')
	{
		if ((*line = ft_strsub(content[fd], 0, len)) == NULL)
			return (-1);
		if ((tmp = ft_strdup(content[fd] + len + 1)) == NULL)
			return (-1);
		free(content[fd]);
		content[fd] = tmp;
	}
	else
	{
		if ((*line = ft_strdup(content[fd])) == NULL)
			return (-1);
		ft_strdel(&content[fd]);
	}
	return (1);
}

static int	ft_add_new_content(int fd, char **content)
{
	char	buff[BUFF_SIZE + 1];
	char	*tmp;
	int		ret;

	ret = 1;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if ((tmp = ft_strjoin(content[fd], buff)) == NULL)
			return (-1);
		free(content[fd]);
		content[fd] = tmp;
		if (ft_strchr(content[fd], '\n') > 0)
			return (ret);
	}
	return (ret);
}

int			get_next_line(const int fd, char **line)
{
	static char	*content[FD_MAX];
	int			line_len;
	int			read_ret;

	line_len = 0;
	read_ret = 1;
	if (line == NULL || BUFF_SIZE < 1 || fd < 0 || fd > FD_MAX)
		return (-1);
	if (content[fd] == NULL)
		if ((content[fd] = ft_strnew(1)) == NULL)
			return (-1);
	line_len = ft_line_len(content[fd]);
	if (content[fd][line_len] == '\n')
		return (ft_get_new_line(line, content, fd, line_len));
	read_ret = ft_add_new_content(fd, content);
	if (read_ret < 0)
		return (-1);
	if (read_ret == 0 && content[fd][0] == '\0')
	{
		if (content[fd])
			free(content[fd]);
		return (0);
	}
	line_len = ft_line_len(content[fd]);
	return (ft_get_new_line(line, content, fd, line_len));
}
