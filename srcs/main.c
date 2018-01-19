/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 18:47:13 by adleau            #+#    #+#             */
/*   Updated: 2018/01/19 13:02:03 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <engine/engine.h>

int		main(int ac, char **av)
{
	(void)av;
	if (ac == 1)
	{
		ft_putendl("If you want to load a custom map : \n./wolf3d [w3d | doom | duke] [path to map].");
		engine();
	}
	else if (ac == 3)
	{
		;
	}
	ft_putendl("Usage : ./wolf3d | ./wolf3d [w3d | doom | duke] [path to map].");
	return (0);
}
