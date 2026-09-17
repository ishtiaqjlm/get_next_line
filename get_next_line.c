/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishtiahm <ishtiahm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 01:27:37 by ishtiahm          #+#    #+#             */
/*   Updated: 2026/09/17 01:27:37 by ishtiahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*buffer;
    char	*temp;
    static char	*stash;
	int		bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	buffer[bytes] = '\0';
    if (bytes == 0)
    {
        free(buffer);
        return (NULL);
    }
    while (bytes > 0)
    {
        if (buffer[bytes - 1] == '\n')
        {
            buffer[bytes - 1] = '\0';
            return (buffer);
        }
        temp = ft_strjoin(stash, buffer);
        free(stash);
        stash = temp;
        bytes = read(fd, buffer, BUFFER_SIZE);
        buffer[bytes] = '\0';
    }
    return (buffer);
}
