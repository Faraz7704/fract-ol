/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/25 19:07:22 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_vector2	zoom_pos_in;

static void	zoom_in(int x, int y, double zoom, t_event_data *data)
{
	t_vector2			pos;
	t_rect				viewport;

	viewport = data->fractolinfo->viewport;
	pos = data->fractolinfo->mouse_pos;
	if (pos.x == 0 && pos.y == 0)
		pos = init_vector2(x, y);
	zoom_pos_in = init_vector2((x - pos.x) * zoom, (y - pos.y) * zoom);
	pos.x = pos.x + zoom_pos_in.x;
	pos.y = pos.y + zoom_pos_in.y;
	data->fractolinfo->mouse_pos = pos;
	pos = get_pixel_scaled(pos, viewport, data->fractolinfo->vp_offset);
	data->fractolinfo->zoom_offset = pos;
	mlx_string_put(data->appinfo->mlx, data->appinfo->window, pos.x, pos.y, 0xCCCCCC,
		"-");
}

static void	zoom_out(int x, int y, double zoom, t_event_data *data)
{
	t_vector2			pos;
	t_rect				viewport;

	(void)zoom;
	viewport = data->fractolinfo->viewport;
	// pos = zoom_pos_in;
	// if (pos.x == 0 && pos.y == 0)
		pos = init_vector2(x, y);
	pos.x = pos.x + zoom_pos_in.x;
	pos.y = pos.y + zoom_pos_in.y;
	pos = get_pixel_scaled(pos, viewport, data->fractolinfo->vp_offset);
	data->fractolinfo->zoom_offset = pos;
	mlx_string_put(data->appinfo->mlx, data->appinfo->window, pos.x, pos.y, 0xCCCCCC,
		"-");
}

static void	julia_motion(int x, int y, t_event_data *data)
{
	data->fractolinfo->complex = init_vector2(
			4 * ((double)x / WIDTH - 0.5),
			4 * ((double)(HEIGHT - y) / HEIGHT - 0.5));
	draw_fractol(data->appinfo, data->fractolinfo);
}

int	mouse_down_handler(int button, int x, int y, t_event_data *data)
{
	if (data->fractolinfo->is_help)
		return (0);
	if (button == ON_MOUSE_SCROLL_UP)
	{
		zoom_out(x, y, data->fractolinfo->zoom, data);
		data->fractolinfo->zoom *= ZOOM_FACTOR;
		draw_fractol(data->appinfo, data->fractolinfo);
	}
	else if (button == ON_MOUSE_SCROLL_DOWN)
	{
		data->fractolinfo->zoom /= ZOOM_FACTOR;
		zoom_in(x, y, data->fractolinfo->zoom, data);
		draw_fractol(data->appinfo, data->fractolinfo);
	}
	if (data->fractolinfo->zoom == 1)
	{
		data->fractolinfo->zoom_offset = init_vector2(0, 0);
		data->fractolinfo->mouse_pos = init_vector2(0, 0);
	}
	return (0);
}

int	mouse_move_handler(int x, int y, t_event_data *data)
{
	if (data->fractolinfo->is_help)
		return (0);
	if (data->fractolinfo->is_fixed_mouse)
		return (0);
	if (str_equal(data->fractolinfo->name, "Julia set"))
		julia_motion(x, y, data);
	return (0);
}
