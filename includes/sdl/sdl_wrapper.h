/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_wrapper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:35:49 by adleau            #+#    #+#             */
/*   Updated: 2018/01/11 19:54:04 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_WRAPPER_H
# define SDL_WRAPPER_H
# define WIN_WD 640
# define WIN_HT 480


struct SDL_Window;
union SDL_Event;


typedef struct			s_sdl_wrapper
{
	struct SDL_Window	*screen;
	union SDL_Event		*event;
}						t_sdl_wrapper;

#endif
