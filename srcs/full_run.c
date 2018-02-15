/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:46:37 by adleau            #+#    #+#             */
/*   Updated: 2018/02/15 13:46:39 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <helpers/loop.h>
#include <menu.h>
#include <stdio.h>

/* full_run function
** is called if the user runs the program without parameters
*/

void			full_run(void)
{
	t_engine	eng;

	init_engine(&eng);
	engine_loop(&eng);
}
