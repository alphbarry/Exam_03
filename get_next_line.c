/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:26:33 by alphbarr          #+#    #+#             */
/*   Updated: 2024/08/16 18:12:46 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	return (NULL);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_strcpy(char *dst, char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

char	*ft_strdup(char *s)
{
	int		i;
	int		len;
	char	*duplicate;

	len = ft_strlen(s);
	i = 0;
	duplicate = (char *)malloc(sizeof(char) * (len + 1));
	if (!duplicate)
		return (NULL);
	while (s[i])
	{
		duplicate[i] = s[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
	{
		free(s1);
		return (NULL);
	}
	ft_strcpy(join, s1);
	ft_strcpy(join + ft_strlen(s1), s2);
	free(s1);
	return (join);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	char		*newline;
	int			countread;

	line = ft_strdup(buf);
	while (!(newline = ft_strchr(line, '\n')) && (countread = read(fd, buf, BUFFER_SIZE)))
	{
		buf[countread] = '\0';
		line = ft_strjoin(line, buf);
		if (!line)
			return (NULL);
	}
	if (countread < 0 || (countread == 0 && ft_strlen(line) == 0))
		return (free(line), NULL);

	if (newline)
	{
		ft_strcpy(buf, newline + 1);
		*(newline + 1) = '\0';
	}
	else
		buf[0] = '\0';

	return (line);
}

# include <fcntl.h>
# include <stdio.h>

int main() {
    int fd = open("text.txt", O_RDONLY);  // Abre el archivo en modo de solo lectura
    if (fd == -1)
	{
        perror("Error al abrir el archivo");
        return 1;
    }
    char *line;
    while ((line = get_next_line(fd)) != NULL)
	{  // Llama a get_next_line en un bucle
        printf("%s", line);  // Imprime la línea
        free(line);          // Libera la línea leída después de imprimir
    }
    close(fd);  // Cierra el archivo después de leer todas las líneas
    return 0;
}

