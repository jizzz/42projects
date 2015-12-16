/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 11:47:52 by mseinic           #+#    #+#             */
/*   Updated: 2015/12/16 18:06:37 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void			tetris_init(char **tetris)
{
	int				i;

	i = -1;
	while (++i < 26)
		tetris[i] = NULL;
}

static char			**read_file(int fd)
{
	char			**tetris;
	char			buf[BUFF_SIZE];
	int				i;
	int				j;

	i = 0;
	j = 0;
	if ((tetris = (char **)malloc(sizeof(char *) * 27)) == NULL)
		return (NULL);
	tetris_init(tetris);
	ft_bzero(buf, BUFF_SIZE);
	if (read(fd, buf, BUFF_SIZE) < 0)
		return (NULL);
	if (ft_strlen(buf) < 20)
		return (NULL);
	while (buf[j] != '\0')
	{
		tetris[i] = ft_strsub(buf, 21 * i, 21);
		j += ft_strlen(tetris[i]);
		++i;
	}
	if (tetris[i - 1][20] == '\n')
		return (NULL);
	return (tetris);
}

static int			check_trash_tetris(char **tetris)
{
	int				i;
	int				n;

	while (*tetris != NULL)
	{
		i = 0;
		n = 0;
		while ((*tetris)[i] != '\0')
		{
			if ((i + 1) % 5 == 0 && (*tetris)[i] == '\n')
				i++;
			if ((*tetris)[i] != '.' && (*tetris)[i] != '#' && i < 20)
				return (0);
			++i;
		}
		++tetris;
	}
	return (1);
}

static int			check_tetris_status(char **tetris)
{
	int			i;
	char		letter;

	letter = 'a';
	while (*tetris != NULL)
	{
		i = 0;
		while ((*tetris)[i] && (*tetris)[i] != '#')
			++i;
		if ((*tetris)[i] && is_correct_tetris(*tetris, i, letter) != 4)
			return (0);
		++letter;
		++tetris;
	}
	return (1);
}

char				**check_file(int fd)
{
	char			**tetris;

	tetris = read_file(fd);
	if (!tetris)
		return (NULL);
	if (!check_trash_tetris(tetris))
	{
		clear_tab(tetris);
		return (NULL);
	}
	if (!check_tetris_status(tetris))
	{
		clear_tab(tetris);
		return (NULL);
	}
	return (tetris);
}
