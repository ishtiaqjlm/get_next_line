/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishtiahm <ishtiahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 16:20:55 by ishtiahm          #+#    #+#             */
/*   Updated: 2026/09/18 19:22:37 by ishtiahm         ###   ########.fr       */
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

char	*ft_get_line(char *stash)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_strchr(const char *s, int c)
{
	int i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
    if (s[i] == c)
        return ((char*)&s[i]);
    return (NULL);
}

char *ft_update_stash(char *stash)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	len = ft_strlen(stash) - i;
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	j = 0;
	while (stash[i+j] != '\0')
	{
		new[j] = stash[i + j];
		j++;
	}
	new[j] = '\0';
	free(stash);
	return (new);
}
