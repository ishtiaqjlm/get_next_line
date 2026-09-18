/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishtiahm <ishtiahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 01:27:37 by ishtiahm          #+#    #+#             */
/*   Updated: 2026/09/18 18:57:05 by ishtiahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*temp;
	char		*line;
	static char	*stash;
	int			bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes >= 0)
		buffer[bytes] = '\0';
	if (bytes == 0)
	{
		free(buffer);
		return (NULL);
	}
	while (!ft_strchr(stash, '\n'))
	{
		if (bytes <= 0)
			break ;
		buffer[bytes] = '\0';
		temp = ft_strjoin(stash, buffer);
		free(stash);
		stash = temp;
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	buffer[bytes] = '\0';
	line = ft_get_line(stash);
	return (line);
}
