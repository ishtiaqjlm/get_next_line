/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishtiahm <ishtiahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 01:27:37 by ishtiahm          #+#    #+#             */
/*   Updated: 2026/09/25 18:23:43 by ishtiahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free_all(t_stash *stash)
{
	free(stash->data);
	return (NULL);
}

int	ft_grow_stash(t_stash *stash, size_t bytes)
{
	char	*new_data;
	size_t	i;

	if (stash->capacity == 0)
		stash->capacity = 16;
	while (stash->used + bytes + 1 > stash->capacity)
		stash->capacity *= 2;
	new_data = malloc(stash->capacity);
	if (!new_data)
		return (0);
	i = 0;
	while (i < stash->used)
	{
		new_data[i] = stash->data[i];
		i++;
	}
	new_data[i] = '\0';
	free(stash->data);
	stash->data = new_data;
	return (1);
}

int	ft_read_stash(int fd, t_stash *stash, char *buffer)
{
	int	bytes;
	int	result;

	while (!ft_strchr(stash->data, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			ft_free_all(stash);
			return (-1);
		}
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		result = ft_append_stash(stash, buffer, bytes);
		if (result == -1)
			return (-1);
	}
	return (1);
}

int	ft_check_stash(t_stash *stash)
{
	if (!stash->data)
		return (0);
	if (!*stash->data)
	{
		ft_free_all(stash);
		return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	char			*line;
	static t_stash	stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (ft_read_stash(fd, &stash, buffer) == -1)
	{
		free(buffer);
		return (NULL);
	}
	if (!ft_check_stash(&stash))
	{
		free(buffer);
		return (NULL);
	}
	line = ft_get_line(&stash);
	free(buffer);
	ft_update_stash(&stash);
	return (line);
}
