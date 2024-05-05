/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:14:05 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/05/04 16:00:30 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*dest;
	int		c;
	int		dest_size;

	dest = NULL;
	dest_size = 0;
	c = ft_getchar(fd);
	if (c != EOF)
		dest = ft_getstr(fd, c, dest_size);
	if (!dest)
		return (NULL);
	else
		return (dest);
}

char	*ft_getstr(int fd, int c, int dest_size)
{
	char	*temp;
	char	*dest;

	dest = NULL;
	while (c > 0)
	{
		if (c == '\n')
		{
			temp = ft_realloc(dest, dest_size + 2, 1);
			if (!temp)
				return (free(dest), NULL);
			free(dest);
			dest = temp;
			dest[dest_size] = c;
			dest[dest_size + 1] = '\0';
			return (dest);
		}
		temp = ft_realloc(dest, dest_size + 10, 0);
		if (!temp)
			return (free(dest), NULL);
		free(dest);
		dest = temp;
		dest[dest_size++] = c;
		c = ft_getchar(fd);
	}
	if (c == EOF && dest_size > 0)
	{
		temp = ft_realloc(dest, dest_size + 1, 0);
		if (!temp)
			return (free(dest), NULL);
		free(dest);
		dest = temp;
		dest[dest_size] = '\0';
		return (dest);
	}
	return (free(dest), NULL);
}

int	ft_getchar(int fd)
{
	static char	buf[BUFFER_SIZE];
	static char	*bufp = NULL;
	static int	n = 0;

	if (n == 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		bufp = buf;
		if (n == 0)
			return (EOF);
		else if (n == -1)
		{
			n = 0;
			ft_bzero(buf, BUFFER_SIZE);
			return (-2);
		}
	}
	if (n > 0)
	{
		n--;
		return ((unsigned char)*bufp++);
	}
	else
		return (EOF);
}
