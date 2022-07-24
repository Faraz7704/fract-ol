/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/24 22:17:01 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	change_palette(t_event_data *data)
{
	data->fractolinfo->palette_index = (data->fractolinfo->palette_index + 1)
		% 4;
	draw_fractol(data->appinfo, data->fractolinfo);
}

static void	help(t_event_data *data)
{
	data->fractolinfo->is_help = data->fractolinfo->is_help == 0;
	if (data->fractolinfo->is_help)
		draw_help(data->appinfo, data->fractolinfo);
	else
		draw_fractol(data->appinfo, data->fractolinfo);
}

int	key_down_handler(int button, t_event_data *data)
{
	if (button == ON_KEY_ESC)
		exit_app(data);
	else if (button == ON_KEY_H)
		help(data);
	if (data->fractolinfo->is_help)
		return (0);
	if (button == ON_KEY_1 || button == ON_KEY_2 || button == ON_KEY_3)
		change_fractol(button, data);
	else if (button == ON_KEY_F)
		fix_mouse_movement(data);
	else if (button == ON_KEY_C)
		change_palette(data);
	else if (button == ON_KEY_R)
		reset_control(data);
	else if (button == ON_ARROW_LEFT || button == ON_ARROW_RIGHT
		|| button == ON_ARROW_UP || button == ON_ARROW_DOWN)
		move_control(button, data);
	else if (button == ON_KEY_PLUS || button == ON_NUMPAD_PLUS
		|| button == ON_KEY_MINUS || button == ON_NUMPAD_MINUS)
		change_max_iteration(button, data);
	return (0);
}
