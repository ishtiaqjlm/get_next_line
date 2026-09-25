/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishtiahm <ishtiahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 16:20:55 by ishtiahm          #+#    #+#             */
/*   Updated: 2026/09/25 16:09:20 by ishtiahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_append_stash(t_stash *stash, char *buffer, int bytes)
{
	int	i;

	if (stash->used + bytes + 1 > stash->capacity)
		if (!ft_grow_stash(stash, bytes))
			return (-1);
	i = 0;
	while (i < bytes)
	{
		stash->data[stash->used + i] = buffer[i];
		i++;
	}
	stash->used += bytes;
	stash->data[stash->used] = '\0';
	return (1);
}

char	*ft_get_line(t_stash *stash)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (stash->data[i] && stash->data[i] != '\n')
		i++;
	if (stash->data[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = stash->data[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}

void	ft_update_stash(t_stash *stash)
{
	int		i;
	int		j;

	i = 0;
	while (stash->data[i] && stash->data[i] != '\n')
		i++;
	if (stash->data[i] == '\n')
		i++;
	j = 0;
	while (stash->data[i + j] != '\0')
	{
		stash->data[j] = stash->data[i + j];
		j++;
	}
	stash->data[j] = '\0';
	stash->used = j;
}
