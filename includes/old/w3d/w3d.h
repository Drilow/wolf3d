/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:29:01 by adleau            #+#    #+#             */
/*   Updated: 2018/01/16 14:29:03 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3D_H
# define W3D_H
# include <w3d/map.h>
# include <calcs/calcs.h>

typedef struct				s_w3d
{
	struct s_w3dmap			map;
	struct s_calcs			calcs;
}							t_w3d;

#endif
