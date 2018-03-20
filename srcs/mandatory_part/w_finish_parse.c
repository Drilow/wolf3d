/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_finish_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:10:49 by mabessir          #+#    #+#             */
/*   Updated: 2018/03/20 16:33:24 by mabessir         ###   ########.fr       */
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
		if (ft_atoi(str + i) > 5 || ft_atoi(str + i) < 0)
			free_wolf(wolf, 7);
		else if (ft_isdigit(str[i]) && (ft_isdigit(str[i + 1]) ||
		str[i + 1] == ']') && ft_atoi(str + i) < 6)
			walltab[j].x = ft_atoi(str + i);
	}
	if ((str = ft_strrchr(line, '[')))
	{
		if (ft_isdigit(str[i]) && (ft_isdigit(str[i + 1]) ||
		str[i + 1] == ']') && ft_atoi(str + i) < 18)
			walltab[j].y = ft_atoi(str + i);
		if (ft_atoi(str + i) > 17 || ft_atoi(str + i) < 0)
			free_wolf(wolf, 7);
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

void			check_properly_do(t_wolf *wolf, char *line)
{
	if (ft_strncmp(line, "{", 1) &&
	ft_strncmp(line, "w3dmapformat:", ft_strlen("w3dmapformat:")) &&
	ft_strncmp(line, "X: ", ft_strlen("X: ")) &&
	ft_strncmp(line, "Y: ", ft_strlen("Y: ")) &&
	ft_strncmp(line, "CameraDirection:", ft_strlen("CameraDirection:")) &&
	ft_strncmp(line, "WALL", ft_strlen("WALL")) &&
	ft_strncmp(line, "}", 1))
		free_wolf(wolf, 6);
	if (wolf->i > 9)
		free_wolf(wolf, 4);
	if (wolf->map.size.x > 5000 || wolf->map.size.x < 0)
		free_wolf(wolf, 5);
	if (wolf->map.size.y > 5000 || wolf->map.size.y < 0)
		free_wolf(wolf, 5);
}

int				get_map_infos(t_wolf *wolf, t_w3dmap *map, char *line)
{
	int	i;

	i = -1;
	check_properly_do(wolf, line);
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
	{
		map->cam.orientation = ft_atoi(line +
		ft_strlen("CameraDirection:"));
		if (map->cam.orientation > 360 || map->cam.orientation < 0)
			free_wolf(wolf, 8);
	}
	wolf->i++;
	return (0);
}
