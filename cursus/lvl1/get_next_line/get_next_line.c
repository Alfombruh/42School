/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daampuru <daampuru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:53:37 by daampuru          #+#    #+#             */
/*   Updated: 2022/05/30 23:07:20 by daampuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*mem;
	char		*temp;
	char		*line;
	ssize_t		rec;
	char		bf[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	temp = ft_strjoin(mem, "");
	mem = 0;
	rec = 1;
	while (!findchr(temp, '\n') && rec)
	{
		rec = read(fd, bf, BUFFER_SIZE);
		if (rec < 0)
		{
			free(temp);
			return (0);
		}
		if (!rec)
			break ;
		bf[rec] = '\0';
		if (!temp)
			temp = ft_strdup(bf);
		else
			temp = ft_strjoin(temp, bf);
	}
	if (!temp || !*temp)
	{
		free(temp);
		return (0);
	}
	line = ft_substr(temp, 0, findchr(temp, '\n') + 1);
	mem = ft_substr(temp, findchr(temp, '\n') + 1, ft_strlen(temp));
	if (rec <= 0)
		free(mem);
	free(temp);
	return (line);
}
