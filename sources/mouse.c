/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/26 20:50:33 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	zoom_in(int x, int y, t_event_data *data)
{
	t_vector2	pos;
	t_rect		viewport;
	double		ratio;
	double		zoom;

	viewport = data->fractolinfo->viewport;
	ratio = min(WIDTH / viewport.size.x, HEIGHT / viewport.size.y);
	zoom = data->fractolinfo->zoom / ZOOM_FACTOR;
	pos = init_vector2(x, y);
	pos = get_pixel_scaled(pos, viewport, data->fractolinfo->vp_offset);
	pos.x = data->fractolinfo->zoom_offset.x + (pos.x * zoom / ratio);
	pos.y = data->fractolinfo->zoom_offset.y + (pos.y * zoom / ratio);
	data->fractolinfo->zoom = zoom;
	data->fractolinfo->zoom_offset = pos;
	draw_fractol(data->appinfo, data->fractolinfo);
}

static void	zoom_out(int x, int y, t_event_data *data)
{
	t_vector2	pos;
	t_vector2	prev_pos;
	t_rect		viewport;
	double		ratio;
	double		zoom;

	zoom = data->fractolinfo->zoom * ZOOM_FACTOR;
	viewport = data->fractolinfo->viewport;
	pos = init_vector2(x, y);
	ratio = min(WIDTH / viewport.size.x, HEIGHT / viewport.size.y);
	pos = get_pixel_scaled(pos, viewport, data->fractolinfo->vp_offset);
	prev_pos.x = pos.x * data->fractolinfo->zoom / ratio;
	prev_pos.y = pos.y * data->fractolinfo->zoom / ratio;
	pos.x = data->fractolinfo->zoom_offset.x - ((pos.x * zoom / ratio)
			- prev_pos.x);
	pos.y = data->fractolinfo->zoom_offset.y - ((pos.y * zoom / ratio)
			- prev_pos.y);
	data->fractolinfo->zoom = zoom;
	data->fractolinfo->zoom_offset = pos;
	draw_fractol(data->appinfo, data->fractolinfo);
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
		zoom_out(x, y, data);
	else if (button == ON_MOUSE_SCROLL_DOWN)
		zoom_in(x, y, data);
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
