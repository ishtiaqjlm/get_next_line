/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishtiahm <ishtiahm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 01:26:15 by ishtiahm          #+#    #+#             */
/*   Updated: 2026/09/25 15:35:09 by ishtiahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_stash
{
        char    *data;
        size_t  used;
        size_t  capacity;
}       t_stash;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
int	        ft_append_stash(t_stash *stash, char *buffer, int bytes);
char	*ft_get_line(t_stash *stash);
void	ft_update_stash(t_stash *stash);
char	*ft_strchr(const char *s, int c);
int	        ft_grow_stash(t_stash *stash, size_t bytes);
int	        ft_read_stash(int fd, t_stash *stash, char *buffer);
char	*ft_free_all(t_stash *stash);
int	        ft_check_stash(t_stash *stash);
#endif
