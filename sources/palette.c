/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/24 22:35:49 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	first_pal(t_palette *palette)
{
	palette->colors[0] = create_trgb(0, 100, 45, 120);
	palette->colors[1] = create_trgb(0, 4, 120, 120);
	palette->colors[2] = create_trgb(0, 4, 120, 120);
	palette->colors[3] = create_trgb(0, 34, 24, 72);
	palette->colors[4] = create_trgb(0, 34, 24, 72);
}

static void	sec_pal(t_palette *palette)
{
	palette->colors[0] = create_trgb(0, 41, 52, 41);
	palette->colors[1] = create_trgb(0, 4, 120, 41);
	palette->colors[2] = create_trgb(0, 4, 120, 41);
	palette->colors[3] = create_trgb(0, 23, 24, 72);
	palette->colors[4] = create_trgb(0, 23, 24, 72);
}

static void	third_pal(t_palette *palette)
{
	palette->colors[0] = create_trgb(0, 82, 11, 41);
	palette->colors[1] = create_trgb(0, 111, 98, 62);
	palette->colors[2] = create_trgb(0, 111, 98, 62);
	palette->colors[3] = create_trgb(0, 55, 14, 62);
	palette->colors[4] = create_trgb(0, 55, 14, 62);
}

static void	forth_pal(t_palette *palette)
{
	palette->colors[0] = create_trgb(0, 73, 33, 80);
	palette->colors[1] = create_trgb(0, 122, 55, 80);
	palette->colors[2] = create_trgb(0, 122, 55, 80);
	palette->colors[3] = create_trgb(0, 76, 43, 75);
	palette->colors[4] = create_trgb(0, 76, 43, 75);
}

t_palette	get_palette(int index)
{
	t_palette	palette;

	palette.size = 5;
	palette.colors = malloc(sizeof(t_palette) * palette.size);
	if (!palette.colors)
		return (palette);
	if (index == 0)
		first_pal(&palette);
	else if (index == 1)
		sec_pal(&palette);
	else if (index == 2)
		third_pal(&palette);
	else if (index == 3)
		forth_pal(&palette);
	return (palette);
}
