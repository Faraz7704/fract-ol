/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_log.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:01:39 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/22 17:54:15 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_LOG_H
# define DEBUG_LOG_H

# define ERR_APP_INIT	    "ERROR: Can\'t initialize app"
# define ERR_FRACTOL_INIT	"ERROR: Can\'t initialize fractol"
# define ERR_WINDOW_INIT	"ERROR: Can\'t initialize window"
# define ERR_IMAGE_INIT		"ERROR: Can\'t initialize image"
# define ERR_FRACTAL_NAME	"ERROR: Argument name invalid"

void	debug_log(char *log);
void	print_help(void);

#endif