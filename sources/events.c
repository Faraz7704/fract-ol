/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:05:07 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/24 21:16:59 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_event_data	init_event_data(t_appinfo *appinfo,
						t_fractolinfo *fractolinfo)
{
	t_event_data	data;

	data.appinfo = appinfo;
	data.fractolinfo = fractolinfo;
	return (data);
}

void	register_events(t_appinfo *appinfo, t_event_data *event_data)
{	
	mlx_hook(appinfo->window, 17, 0, exit_app, event_data);
	mlx_hook(appinfo->window, 4, 0, mouse_down_handler, event_data);
	mlx_hook(appinfo->window, 6, 0, mouse_move_handler, event_data);
	mlx_hook(appinfo->window, 2, 0, key_down_handler, event_data);
}
