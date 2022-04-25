/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:30:37 by ysachiko          #+#    #+#             */
/*   Updated: 2022/04/25 19:17:43 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	exit_all(t_data *data)
{
	int	i;

	i = 0;
	sem_close(data->print);
	sem_close(data->general);
	kill(0, SIGKILL);
}

void	*moni(void *arg)
{
	t_data	*data;

	data = arg;
	usleep(1000);
	while (1)
	{
		if (ft_time() - data->last_meal > data->die_time)
		{
			exit_all(data);
			break ;
		}
	}
	return (NULL);
}

void	monitoring(t_data *data)
{
	pthread_t	monitoring;

	pthread_create(&monitoring, NULL, moni, data);
	pthread_detach(monitoring);
}
