/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 11:59:30 by adleau            #+#    #+#             */
/*   Updated: 2018/01/28 14:58:23 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cleanup/cleanup.h>
#include <parser/parser.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <SDL_image.h>
#include <engine/engine.h>
#include <helpers/helpers.h>

/* get_map_infos function
** reads if there is some, and fills the information relative to the map
** into the map structure, returns 1 if done
 */

int				get_map_infos(t_engine *eng, t_w3dmap *map, char *line)
{
	int			i;

	i = -1;
	if (ft_strchr(line, '}'))
		return (1);
	if (!ft_strncmp(line, "X: ", ft_strlen("X: ")))
		map->size.x = ft_atoi(line + ft_strlen("X: "));
	else if (!ft_strncmp(line, "Y: ", ft_strlen("Y: ")))
		map->size.y = ft_atoi(line + ft_strlen("Y: "));
	else if (!ft_strncmp(line, "WEST_WALL", ft_strlen("WEST_WALL")))
		map->walls[0] = trimquote(ft_strdup(ft_strchr(line, '\"') + 1));
	else if (!ft_strncmp(line, "EAST_WALL", ft_strlen("EAST_WALL")))
		map->walls[1] = trimquote(ft_strdup(ft_strchr(line, '\"') + 1));
	else if (!ft_strncmp(line, "NORTH_WALL", ft_strlen("NORTH_WALL")))
		map->walls[2] = trimquote(ft_strdup(ft_strchr(line, '\"') + 1));
	else if (!ft_strncmp(line, "SOUTH_WALL", ft_strlen("SOUTH_WALL")))
		map->walls[3] = trimquote(ft_strdup(ft_strchr(line, '\"') + 1));
	if (map->size.x != 0 && map->size.y != 0 && !map->map_tab)
	{
		if (!(map->map_tab = (char**)malloc(sizeof(char*) * (map->size.y + 1))))
			free_everything(eng, 1);
		while (++i <= map->size.y)
		{
			map->map_tab[i] = 0;
			if (!(map->map_tab[i] = (char*)malloc(sizeof(char) * (map->size.x + 1))))
				free_everything(eng, 1);
			ft_memset(map->map_tab[i], 0, map->size.x);
		}
	}
	if (!ft_strncmp(line, "CameraDirection:", ft_strlen("CameraDirection:")))
		map->camera.orientation = ft_atoi(line + ft_strlen("CameraDirection:"));
	return (0);
}

/* get_map function
** fills the map tab with the line feed
*/

void			get_map(t_engine *eng, t_w3dmap *map, char *line)
{
	if (map->map_tab && eng->parser.linesread < map->size.y)
		remove_spaces(line, map->map_tab[++(eng->parser.linesread)]);
}

/* fill_parse_tab_and_map function
** handles the parse for each line
 */

void			fill_parse_tab_and_map(t_engine *eng, char *line)
{
	if (eng->parser.done != 2)
	{
		if (get_map_infos(eng, &(eng->parser.map), line))
			eng->parser.done = 2;
		else
			eng->parser.done = 0;
	}
	else if (eng->parser.done == 2)
		get_map(eng, &(eng->parser.map), line);
}

/* parser function
** entry pointo to the parser
 */

void			parse_w3d(t_engine *eng, char *path)
{
	eng->parser.map.map_tab = NULL;
	if ((eng->parser.fd = open(path, O_RDONLY)) < 0)
		free_everything(eng, 1);
	while ((eng->parser.beenread = get_next_line
	(eng->parser.fd, &(eng->parser.line))) != -1)
	{
		if (eng->parser.beenread == 0)
			break ;
		fill_parse_tab_and_map(eng, eng->parser.line);
	}
	if (eng->parser.beenread == -1)
		free_everything(eng, 1);
//	printf("maptab pointer %p, map size %d %d, camera orientation %f, walls : %s | %s | %s | %s\n", eng->parser.map.map_tab, eng->parser.map.size.x, eng->parser.map.size.y, eng->parser.map.camera.orientation, eng->parser.map.walls[0], eng->parser.map.walls[1], eng->parser.map.walls[2], eng->parser.map.walls[3]);
	eng->parser.done = 1;
	close(eng->parser.fd);
}
