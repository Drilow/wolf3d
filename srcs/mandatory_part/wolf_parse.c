/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:23:53 by adleau            #+#    #+#             */
/*   Updated: 2018/03/20 18:38:37 by mabessir         ###   ########.fr       */
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
			if (map[r.y][r.x] == 'S' && r.y > 0)
				return (r);
		}
	}
	return (r);
}

void			check_map(t_wolf *wolf, char **map, t_w3dmap wmap)
{
	int i;
	int j;

	i = -1;
	if (wmap.size.x == 0 || wmap.size.y == 0)
		free_wolf(wolf, 6);
	while (++i < wmap.size.y)
	{
		j = -1;
		while (++j < wmap.size.x)
		{
			if (map[0][j] == '0' ||
			map[wmap.size.y - 1][j] == '0' || map[0][j] == 'S')
				free_wolf(wolf, 9);
			if (map[i][0] == '0' || map[i][0] == 'S' ||
			map[i][wmap.size.x - 1] == '0')
				free_wolf(wolf, 9);
			if (map[i][j] == 'S')
				wolf->spawn++;
			if (map[i][j] != '0' && map[i][j] != 'S')
				map[i][j] = '1';
		}
		if (map[i][wmap.size.x - 1] == 'S')
			free_wolf(wolf, 9);
	}
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
		free(wolf->parse.buf);
		wolf->parse.buf = NULL;
	}
	if (wolf->parse.beenread == -1)
		free_wolf(wolf, 1);
	check_map(wolf, wolf->map.map, wolf->map);
	if (wolf->spawn != 1)
		free_wolf(wolf, 9);
	wolf->map.pos = get_starting(wolf->map.map);
	wolf->parse.done = 1;
	if (wolf->i != 9)
		free_wolf(wolf, 5);
	close(wolf->parse.fd);
}
