/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_finish_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:10:49 by mabessir          #+#    #+#             */
/*   Updated: 2018/03/14 12:12:11 by mabessir         ###   ########.fr       */
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

int				ft_wallstexture(t_vector_2d walltab[], int j,
t_wolf *wolf, char *line)
{
	int		i;
	char	*str;

	i = 1;
	if ((str = ft_strchr(line, '[')))
	{
		if (ft_isdigit(str[i]) && (ft_isdigit(str[i + 1]) ||
		str[i + 1] == ']') && atoi(str + i) < 6)
			walltab[j].x = atoi(str + i);
		else if (walltab[j].x > 5)
			free_wolf(wolf, 1);
	}
	if ((str = ft_strrchr(line, '[')))
	{
		if (ft_isdigit(str[i]) && (ft_isdigit(str[i + 1]) ||
		str[i + 1] == ']') && atoi(str + i) < 18)
			walltab[j].y = atoi(str + i);
		else
			free_wolf(wolf, 1);
	}
	j++;
	return (j);
}

void			alloc_map_mem(t_wolf *wolf, t_w3dmap *map, int i)
{
	if (!(map->map = (char**)malloc(sizeof(char*) * (map->size.y + 1))))
		free_wolf(wolf, 1);
	while (++i <= map->size.y)
	{
		map->map[i] = 0;
		if (!(map->map[i] = (char*)malloc(sizeof(char) * (map->size.x + 1))))
			free_wolf(wolf, 1);
		ft_memset(map->map[i], 0, map->size.x);
	}
}

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
	else if (!ft_strncmp(line, "WALL", ft_strlen("WALL")))
		map->j = ft_wallstexture(map->walltab, map->j, wolf, line);
	if (map->size.x != 0 && map->size.y != 0 && !map->map)
		alloc_map_mem(wolf, map, i);
	if (!ft_strncmp(line, "CameraDirection:", ft_strlen("CameraDirection:")))
		map->cam.orientation = ft_atoi(line + ft_strlen("CameraDirection:"));
	return (0);
}
