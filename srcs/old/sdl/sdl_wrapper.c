/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_wrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 19:54:22 by adleau            #+#    #+#             */
/*   Updated: 2018/01/21 20:52:47 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <SDL_image.h>
#include <cleanup/cleanup.h>
#include <sdl/sdl_wrapper.h>
#include <libft.h>

void			init_sdl_wrap(t_sdl_wrapper *wrap)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		ft_putendl_fd("Failed to init SDL", 2);
	wrap->screen = NULL;
	IMG_Init(IMG_INIT_JPG);
	if (!(wrap->screen = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WD, WIN_HT, SDL_WINDOW_SHOWN)))
	{
		printf("fuuuu %s\n", SDL_GetError());
		exit(1);
	}
	if (!(wrap->menu = SDL_CreateRGBSurfaceWithFormat(0, WIN_WD, WIN_HT, 32, SDL_PIXELFORMAT_RGBA32)))
		exit(1);
	if (!(wrap->wolf = SDL_CreateRGBSurfaceWithFormat(0, WIN_WD, WIN_HT, 32, SDL_PIXELFORMAT_RGBA32)))
		exit(1);
}
