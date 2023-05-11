/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:38:20 by vfedorov          #+#    #+#             */
/*   Updated: 2023/03/02 14:38:20 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_fd(int fd, char *tmp_str_dat, char *org)
{
	int		read_lf;
	char	*reserv;

	read_lf = 1;
	reserv = NULL;
	while (read_lf != '\0')
	{
		read_lf = read(fd, tmp_str_dat, BUFFER_SIZE);
		if (read_lf == -1)
			return (0);
		else if (read_lf == 0)
			break ;
		tmp_str_dat[read_lf] = '\0';
		if (!org)
			org = ft_strdup("");
		reserv = org;
		org = ft_strjoin(reserv, tmp_str_dat);
		free(reserv);
		reserv = NULL;
		if (ft_strchr(tmp_str_dat, '\n'))
			break ;
	}
	return (org);
}

char	*rem(char *line)

{
	size_t	count;
	char	*reserv;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0' || line[1] == '\0')
		return (0);
	reserv = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (*reserv == '\0')
	{
		free(reserv);
		reserv = NULL;
	}
	line[count + 1] = '\0';
	return (reserv);
}

char	*get_next_line(int fd)

{
	char		*line;
	char		*buf;
	static char	*res[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	line = read_fd(fd, buf, res[fd]);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	res[fd] = rem(line);
	return (line);
}
