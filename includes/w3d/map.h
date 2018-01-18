/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 19:03:14 by adleau            #+#    #+#             */
/*   Updated: 2018/01/18 14:06:11 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3DMAP_H
# define W3DMAP_H

/* w3dmap
** holds informations specific to w3d map
 */

typedef struct		s_w3dmap
{
	char			**map_tab;
	t_2dvector		pos;
	char			**walls;
}					t_w3dmap;

#endif
