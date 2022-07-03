/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/03 11:33:37 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_color	create_trgb(int t, int r, int g, int b)
{
	t_color	color;

	color.channel[0] = t;
	color.channel[1] = r;
	color.channel[2] = g;
	color.channel[3] = b;
	return (color);
}

int	get_numcolor(t_color color)
{
	return (color.channel[0] << 24 | color.channel[1] << 16
		| color.channel[2] << 8 | color.channel[3]);
}

t_color	lerp_color(t_color a, t_color b, double t)
{
	return (create_trgb(
			a.channel[0] + (b.channel[0] - a.channel[0]) * t,
			a.channel[1] + (b.channel[1] - a.channel[1]) * t,
			a.channel[2] + (b.channel[2] - a.channel[2]) * t,
			a.channel[3] + (b.channel[3] - a.channel[3]) * t
		));
}

t_color	gradient_color(int i, int max, t_palette palette)
{
	double	index;
	double	t;
	int		c;

	index = i / max;
	c = palette.size - 1;
	t = fmod(index, 1.0f / c) * c;
	return (lerp_color(palette.colors[(int)(index * c) + 1],
		palette.colors[(int)(index * c)],
		(int)((t + 1) - t))
	);
}

t_color	get_fractol_color(t_fractolinfo *info, t_vector2 pixel, int iteration)
{
	t_palette	palette;
	t_color		color;

	(void)pixel;
	if (iteration == info->max_iteration)
		return (create_trgb(0, 0, 0, 0));
	palette.size = 5;
	palette.colors = malloc(sizeof(t_palette) * palette.size);
	if (!palette.colors)
		return (create_trgb(0, 255, 255, 255));
	palette.colors[0] = create_trgb(0, 127, 22, 55);
	palette.colors[1] = create_trgb(0, 4, 120, 120);
	palette.colors[2] = create_trgb(0, 255, 183, 51);
	palette.colors[3] = create_trgb(0, 245, 115, 54);
	palette.colors[4] = create_trgb(0, 194, 33, 33);
	color = gradient_color(iteration, info->max_iteration, palette);
	free(palette.colors);
	return (color);
}
