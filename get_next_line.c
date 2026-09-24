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

char	*ft_free_all(char *buffer, char *stash)
{
	free(buffer);
	free(stash);
	return (NULL);
}
char	*ft_read_stash(int fd, char *stash, char *buffer)
{
	int		bytes;
	char	*temp;
	while (!ft_strchr(stash, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			return (ft_free_all(buffer, stash));
		}
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		temp = ft_strjoin(stash, buffer);
		if (!temp)
		{
			return (ft_free_all(buffer, stash));
		}
		free(stash);
		stash = temp;
	}
	return (stash);
}
char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	stash = ft_read_stash(fd, stash, buffer);
	free(buffer);
	if (!stash)
    	return (NULL);
	if (!*stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = ft_get_line(stash);
	stash = ft_update_stash(stash);
	return (line);
}
