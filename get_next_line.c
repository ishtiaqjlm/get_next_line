/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishtiahm <ishtiahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 01:27:37 by ishtiahm          #+#    #+#             */
/*   Updated: 2026/09/24 19:39:58 by ishtiahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free_all(t_stash *stash)
{
	free(stash->data);
	return (NULL);
}

void	ft_read_stash(int fd, t_stash *stash, char *buffer)
{
	int		bytes;
	char	*temp;

	while (!ft_strchr(stash->data, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			ft_free_all(stash);
			return	;
		}
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		temp = ft_strjoin(stash->data, buffer);
		if (!temp)
		{
			ft_free_all(stash);
			return	;
		}
		free(stash);
		stash->data = temp;
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static t_stash	stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	ft_read_stash(fd, &stash, buffer);
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
