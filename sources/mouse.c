/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/19 22:03:07 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	mouse_scroll(int x, int y, t_event_data *data)
{
	static t_vector2	prev_pos;
	static t_vector2	fix_pos;
	t_vector2			new_pos;
	double				zoom;

	zoom = data->fractolinfo->zoom;
	if (prev_pos.x == 0 && prev_pos.y == 0)
		prev_pos = init_vector2(x, y);
	new_pos.x = (x - prev_pos.x);
	new_pos.y = (y - prev_pos.y);
	if (fix_pos.x == 0 && fix_pos.y == 0)
		fix_pos = init_vector2(x, y);
	printf("new_pos x: %f, y: %f\n", new_pos.x, new_pos.y);
	new_pos.x = fix_pos.x + ((new_pos.x / WIDTH) * WIDTH * zoom);
	new_pos.y = fix_pos.y + ((new_pos.y / HEIGHT) * HEIGHT * zoom);
	data->fractolinfo->zoom_offset = new_pos;
	draw_fractol(data->appinfo, data->fractolinfo);
	prev_pos.x = x;
	prev_pos.y = y;
}

int	mouse_down_handler(int button, int x, int y, t_event_data *data)
{
	if (button == ON_MOUSE_SCROLL_UP)
	{
		data->fractolinfo->zoom *= ZOOM_FACTOR;
		mouse_scroll(x, y, data);
	}
	else if (button == ON_MOUSE_SCROLL_DOWN)
	{
		data->fractolinfo->zoom /= ZOOM_FACTOR;
		mouse_scroll(x, y, data);
	}
	return (0);
}
