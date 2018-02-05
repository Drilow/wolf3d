#include <libft.h>
#include <full_run.h>
#include <mandatory_part/wolf.h>
#include <helpers/cleanup.h>
#include <helpers/str_helpers.h>
#include <fcntl.h>
#include <SDL.h>
#include <SDL_image.h>

/* get_map_infos function
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
	else if (!ft_strncmp(line, "WEST_WALL", ft_strlen("WEST_WALL")))
		map->walls[0] = IMG_Load(trimquote(ft_strdup(ft_strchr(line, '\"') + 1)));
	else if (!ft_strncmp(line, "EAST_WALL", ft_strlen("EAST_WALL")))
		map->walls[1] = IMG_Load(trimquote(ft_strdup(ft_strchr(line, '\"') + 1)));
	else if (!ft_strncmp(line, "NORTH_WALL", ft_strlen("NORTH_WALL")))
		map->walls[2] = IMG_Load(trimquote(ft_strdup(ft_strchr(line, '\"') + 1)));
	else if (!ft_strncmp(line, "SOUTH_WALL", ft_strlen("SOUTH_WALL")))
		map->walls[3] = IMG_Load(trimquote(ft_strdup(ft_strchr(line, '\"') + 1)));
	if (map->size.x != 0 && map->size.y != 0 && !map->map)
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
	if (!ft_strncmp(line, "CameraDirection:", ft_strlen("CameraDirection:")))
		map->cam.orientation = ft_atoi(line + ft_strlen("CameraDirection:"));
	return (0);
}

/* get_map function
** fills the map tab with the line feed
*/

void			get_map(t_wolf *wolf, t_w3dmap *map, char *line)
{
	printf("abc %p %d %d\n", map->map[0], map->size.y, wolf->parse.linesread);
	if (map->map && wolf->parse.linesread < map->size.y)
		remove_spaces(line, map->map[++(wolf->parse.linesread)]);
}

/* fill_parse_tab_and_map function
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

/* parse function
** entry pointo to the parse
 */

void			w3d_parse(t_wolf *wolf)
{
	while ((wolf->parse.beenread = get_next_line
	(wolf->parse.fd, &(wolf->parse.buf))) != -1)
	{
		if (wolf->parse.beenread == 0)
			break ;
		printf("bite\n");
		fill_parse_tab_and_map(wolf, wolf->parse.buf);
	}
	if (wolf->parse.beenread == -1)
		free_wolf(wolf, 1);
	wolf->parse.done = 1;
	close(wolf->parse.fd);
}

void		init_w3dparse(t_wolf *wolf, char *path)
{
	if (path == NULL)
		if (!(path = ft_strdup("maps/wolf3d/lvl1.w3dmap")))
			free_wolf(wolf, 1);
	if ((wolf->parse.fd = open(path, O_RDONLY)) == -1)
		free_wolf(wolf, 1);
	wolf->parse.beenread = -1;
	wolf->parse.linesread = -1;
	wolf->parse.done = 0;
}

void		init_w3dmap(t_wolf *wolf, t_w3dmap *map)
{
	int		i;

	map->map = NULL;
	map->size.x = 0;
	map->size.y = 0;
	map->pos.x = -1;
	map->pos.y = -1;
//	init_w3dcam(&(map->cam));
	if (!(map->walls = (SDL_Surface**)malloc(sizeof(SDL_Surface) * 4)))
		free_wolf(wolf, 1);
	i = -1;
	while (++i < 4)
	{
		if (!(map->walls[i] = SDL_CreateRGBSurfaceWithFormat(0, WIN_WD, WIN_HT, 32, SDL_PIXELFORMAT_RGBA32)))
			free_wolf(wolf, 1);
	}
}

/* init_wolf function
** initializes all the data relative to the w3d wolfine
*/

void		init_wolf(t_wolf *wolf, t_sdl_wrapper *wrap, char *path)
{
	init_w3dparse(wolf, path);
	init_w3dmap(wolf, &(wolf->map));
	wrap->drawn = 0;
	w3d_parse(wolf);
}

/* mandatory_part function
** entry point to the mandatory part
*/

void		mandatory_part(t_sdl_wrapper *wrap, char *path)
{
	t_wolf	wolf;

	if (wrap == NULL)
		init_sdl_wrap(wrap);
	else
		wolf.wrap = wrap;
	init_wolf(&wolf, wrap, path);
	wolf_loop(&wolf);
}
