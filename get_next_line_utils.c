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
		line = malloc(i + 2);
	else
		line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (stash[j])
	{
		line[j] = stash[j];
		if (stash[j] == '\n')
			break ;
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_strchr(char *s, int c)
{
	int i;
	
	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
    
    if (s[i] == c) 
        return (char*)&s[i];
    return (NULL);
}