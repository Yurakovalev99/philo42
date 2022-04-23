/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:08:12 by ysachiko          #+#    #+#             */
/*   Updated: 2022/04/23 15:17:52 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void take_forks(t_data *data)

{
	sem_wait(data->general);
	sem_wait(data->forks);
	sem_wait(data->forks);
	sem_post(data->general);
}

void	ft_action(t_data *data)

{
	while (data->cycles)
	{
		take_forks(data);
		eating(data);
		sleeping(data);
	}
}

void    eating(t_data *data)

{
	printf("eating\n");
	ft_sleep(data->eat_time);
	// sem_wait(data->general);
	data->last_meal = ft_time();
	// sem_post(data->general);
	sem_post(data->forks);
	sem_post(data->forks);
}

void    sleeping(t_data *data)

{
	printf("sleeping\n");
	ft_sleep(data->sleep_time);
	printf("thinking\n");
}
