/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 13:04:10 by adleau            #+#    #+#             */
/*   Updated: 2018/01/21 15:51:11 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/engine.h>
#include <SDL.h>
#include <libft.h>
#include <cleanup/cleanup.h>
#include <parser/parser.h>
#include <fcntl.h>

/* get_scancode function
** gets the SDL_Scancode value matching the scancode set in the conf file
 */

SDL_Scancode		get_scancode(t_engine *eng, char *line)
{
	int				fd;
	int				r;
	char			*linesdl;
	char			*conv;
	SDL_Scancode	scode;

	conv = NULL;
	linesdl = NULL;
	if ((fd = open("ext/SDL2/include/SDL2/SDL_scancode.h", O_RDONLY)) == -1)
		free_everything(eng, 1);
	while ((r = get_next_line(fd, &linesdl)))
	{
		if ((conv = ft_strstr(linesdl, ft_strjoin(line, " "))))
			scode = ft_atoi(ft_strchr(conv, '=') + 1);
	}
	close(fd);
	if (conv)
		free(conv);
	if (linesdl)
		free(linesdl);
	return (scode);
}

/* parse_binds function
** parses the keybinds conf file
 */

void			parse_binds(t_engine *eng, t_binds *binds, char *path)
{
	char		*line;
	int			fd;
	int			r;

	if ((fd = open(path, O_RDONLY)) == -1)
		free_everything(eng, 1);
	while ((r = get_next_line(fd, &line)) != -1)
	{
		if (r == 0)
			break ;
		if (!ft_strncmp(line, "UP:", ft_strlen("UP:")))
			binds->up = get_scancode(eng, line + ft_strlen("UP:"));
		else if (!ft_strncmp(line, "DOWN:", ft_strlen("DOWN:")))
			binds->down = get_scancode(eng, line + ft_strlen("DOWN:"));
		else if (!ft_strncmp(line, "LEFT:", ft_strlen("LEFT:")))
			binds->left = get_scancode(eng, line + ft_strlen("LEFT:"));
		else if (!ft_strncmp(line, "RIGHT:", ft_strlen("RIGHT:")))
			binds->right = get_scancode(eng, line + ft_strlen("RIGHT:"));
		else if (!ft_strncmp(line, "MENU:", ft_strlen("MENU:")))
			binds->menu = get_scancode(eng, line + ft_strlen("MENU:"));
	}
	if (r == -1)
		free_everything(eng, 1);
	close(fd);
	if (line)
		free(line);
}
