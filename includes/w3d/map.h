/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 19:03:14 by adleau            #+#    #+#             */
/*   Updated: 2018/01/16 12:51:54 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3DMAP_H
# define W3DMAP_H

typedef struct		s_2dvector
{
	int				x;
	int				y;
}					t_2dvector;

typedef struct		s_w3dmap
{
	char			**map_tab;
	t_2dvector		pos;
}					t_map;

#endif
