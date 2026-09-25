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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";
	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
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
