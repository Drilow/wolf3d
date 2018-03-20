/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 20:47:12 by adleau            #+#    #+#             */
/*   Updated: 2018/03/06 20:47:15 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3D_PARSE_H
# define W3D_PARSE_H

typedef struct			s_w3dparse
{
	int					fd;
	char				*buf;
	int					beenread;
	int					linesread;
	int					done;
}						t_w3dparse;

#endif
