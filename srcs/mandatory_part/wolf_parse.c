/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:23:53 by adleau            #+#    #+#             */
/*   Updated: 2018/03/07 13:46:17 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <full_run.h>
#include <mandatory_part/wolf.h>
#include <helpers/cleanup.h>
#include <helpers/str_helpers.h>
#include <fcntl.h>
#include <SDL.h>
#include <SDL_image.h>

/*
** get_map_infos function
** reads if there is some, and fills the information relative to the map
** into the map structure, returns 1 if done
*/

int				get_map_infos(t_wolf *wolf, t_w3dmap *map, char *line)
{
	int			i;

	i = -1;
	if (ft_strchr(line, '}'))
		return (1);
	if (!ft_strncmp(line, "X: ", ft_strlen("X: ")))
		map->size.x = ft_atoi(line + ft_strlen("X: "));
	else if (!ft_strncmp(line, "Y: ", ft_strlen("Y: ")))
		map->size.y = ft_atoi(line + ft_strlen("Y: "));
	if (map->size.x != 0 && map->size.y != 0 && !map->map)
	{
		if (!(map->map = (char**)malloc(sizeof(char*) * (map->size.y + 1))))
			free_wolf(wolf, 1);
		while (++i <= map->size.y)
		{
			map->map[i] = 0;
			if (!(map->map[i] = (char*)malloc(sizeof(char) *
			(map->size.x + 1))))
				free_wolf(wolf, 1);
			ft_memset(map->map[i], 0, map->size.x);
		}
	}
	if (!ft_strncmp(line, "CameraDirection:", ft_strlen("CameraDirection:")))
		map->cam.orientation = ft_atoi(line + ft_strlen("CameraDirection:"));
	return (0);
}

/*
** get_map function
** fills the map tab with the line feed
*/

void			get_map(t_wolf *wolf, t_w3dmap *map, char *line)
{
	if (map->map && wolf->parse.linesread < map->size.y)
		remove_spaces(line, map->map[++(wolf->parse.linesread)]);
}

/*
** fill_parse_tab_and_map function
** handles the parse for each line
*/

void			fill_parse_tab_and_map(t_wolf *wolf, char *line)
{
	if (wolf->parse.done != 2)
	{
		if (get_map_infos(wolf, &(wolf->map), line))
			wolf->parse.done = 2;
		else
			wolf->parse.done = 0;
	}
	else if (wolf->parse.done == 2)
		get_map(wolf, &(wolf->map), line);
}

t_vector_2d		get_starting(char **map)
{
	t_vector_2d	r;

	r.y = -1;
	while (map[++(r.y)])
	{
		r.x = -1;
		while (map[r.y][++(r.x)])
		{
			if (map[r.y][r.x] == 'S')
				return (r);
		}
	}
	r.x = -1;
	r.y = -1;
	return (r);
}

/*
** parse function
** entry pointo to the parse
*/

void			w3d_parse(t_wolf *wolf)
{
	while ((wolf->parse.beenread =
	get_next_line(wolf->parse.fd, &(wolf->parse.buf))) != -1)
	{
		if (wolf->parse.beenread == 0)
			break ;
		fill_parse_tab_and_map(wolf, wolf->parse.buf);
	}
	if (wolf->parse.beenread == -1)
		free_wolf(wolf, 1);
	wolf->map.pos = get_starting(wolf->map.map);
	wolf->parse.done = 1;
	close(wolf->parse.fd);
}
