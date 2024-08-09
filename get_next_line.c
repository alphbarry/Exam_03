/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:26:33 by alphbarr          #+#    #+#             */
/*   Updated: 2024/08/09 18:28:56 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	int		i;
	int		len;
	char	*duplicate;

	len = ft_strlen(s);
	i = 0;
	duplicate = (char *)malloc(sizeof(char) * len + 1);
	if (!duplicate)
		return (NULL);
	while (s[i])
	{
		duplicate[i] = s[i];
		index++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

char	*get_next_line(int fd)
{
	int		n;
	int		i;
	char	c;
	char	buffer[7000000];

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	n = read(fd, &c, 1);
	while (n > 0)
	{
		buffer[i++] = c;
		if (c == '\n')
			break ;
		n = read(fd, &c, 1);
	}
	if (n <= 0 && i == 0)
		return (NULL);
	buffer[i] = '\0';
	return (ft_strdup(buffer));
}
