/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 21:07:17 by adleau            #+#    #+#             */
/*   Updated: 2018/01/28 15:31:46 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H
# include <engine/engine.h>
# include <sdl/sdl_wrapper.h>

/* s_wall
** stores the rays for the renderer
** x dimension : the point in the screen where the collumn will be place
** y dimension : size of the collumn
 */

typedef struct			s_wall
{
	t_2dvector			dimensions;
	t_2dvector			inmap;
	struct s_wall		*next;
}						t_wall;

/* s_rays
** holds 3 links of a linked list refering to the wall currently being calculate
** the first and the last are used to scale textures to the walls
 */

typedef struct			s_rays
{
	t_wall				*first;
	t_wall				*current;
	t_wall				*last;
}						t_rays;

void					raycaster(t_engine *eng);

#endif
