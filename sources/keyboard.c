/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/22 18:02:51 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	help(t_event_data *data)
{
	data->fractolinfo->is_help = data->fractolinfo->is_help == 0;
	if (data->fractolinfo->is_help)
		draw_help(data->appinfo, data->fractolinfo);
	else
		draw_fractol(data->appinfo, data->fractolinfo);
}

static void	move(int button, t_event_data *data)
{
	t_vector2	offset;

	offset = data->fractolinfo->zoom_offset;
	if (button == ON_ARROW_LEFT)
		data->fractolinfo->zoom_offset = init_vector2(offset.x - 10, offset.y);
	else if (button == ON_ARROW_RIGHT)
		data->fractolinfo->zoom_offset = init_vector2(offset.x + 10, offset.y);
	else if (button == ON_ARROW_UP)
		data->fractolinfo->zoom_offset = init_vector2(offset.x, offset.y - 10);
	else if (button == ON_ARROW_DOWN)
		data->fractolinfo->zoom_offset = init_vector2(offset.x, offset.y + 10);
	draw_fractol(data->appinfo, data->fractolinfo);
}

static void	change_max_iteration(int button, t_event_data *data)
{
	if (button == ON_KEY_PLUS || button == ON_NUMPAD_PLUS)
		data->fractolinfo->max_iteration++;
	if (button == ON_KEY_MINUS || button == ON_NUMPAD_MINUS)
		data->fractolinfo->max_iteration--;
	if (data->fractolinfo->max_iteration < 0)
		data->fractolinfo->max_iteration = 0;
	draw_fractol(data->appinfo, data->fractolinfo);
}

static void	fixed_mouse_move(t_event_data *data)
{
	data->fractolinfo->is_fixed_mouse = data->fractolinfo->is_fixed_mouse == 0;
	draw_fractol(data->appinfo, data->fractolinfo);
}

int	key_down_handler(int button, t_event_data	*data)
{
	if (button == ON_KEY_ESC)
		exit_app(data);
	else if (button == ON_KEY_H)
		help(data);
	if (data->fractolinfo->is_help)
		return (0);
	if (button == ON_KEY_F)
		fixed_mouse_move(data);
	else if (button == ON_KEY_R)
	{
		fractol_reset(data->fractolinfo);
		draw_fractol(data->appinfo, data->fractolinfo);
	}
	else if (button == ON_ARROW_LEFT || button == ON_ARROW_RIGHT
		|| button == ON_ARROW_UP || button == ON_ARROW_DOWN)
		move(button, data);
	else if (button == ON_KEY_PLUS || button == ON_NUMPAD_PLUS
		|| button == ON_KEY_MINUS || button == ON_NUMPAD_MINUS)
		change_max_iteration(button, data);
	return (0);
}
