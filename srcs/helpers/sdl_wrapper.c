/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_wrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 19:54:22 by adleau            #+#    #+#             */
/*   Updated: 2018/03/15 15:16:58 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <SDL_image.h>
#include <helpers/cleanup.h>
#include <helpers/sdl_wrapper.h>
#include <libft.h>
#include <stdio.h>

void			init_sdl_wrap(t_sdl_wrapper *wrap)
{
	int			flags;
	int			initted;

	if (SDL_Init(SDL_INIT_EVERYTHING))
		ft_putendl_fd("Failed to init SDL", 2);
	wrap->screen = NULL;
	flags = IMG_INIT_PNG;
	initted = IMG_Init(flags);
	if ((initted & flags) != flags)
	{
		ft_putendl_fd
("IMG_Init: Failed to init required jpg and png support!\n", 2);
		exit(1);
	}
	if (!(wrap->screen = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_UNDEFINED,
SDL_WINDOWPOS_UNDEFINED, WIN_WD, WIN_HT, SDL_WINDOW_SHOWN)))
		exit(1);
	if (!(wrap->wolf = SDL_CreateRGBSurfaceWithFormat(0, WIN_WD, WIN_HT, 32,
SDL_PIXELFORMAT_RGBA32)))
		exit(1);
	wrap->renderer = NULL;
	wrap->tex = NULL;
}
