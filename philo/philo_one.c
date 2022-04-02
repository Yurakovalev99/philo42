/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:24:29 by ysachiko          #+#    #+#             */
/*   Updated: 2022/04/02 18:21:49 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	ft_sleep(long long time, t_philo *philo)
{
	long long	i;
	int			local;

	i = philo->num;
	i = timestamp();

	pthread_mutex_lock(&philo->info->finish_mutex);
	if (philo->info->finish)
	{
		pthread_mutex_unlock(&philo->info->finish_mutex);
		return (1);
	}
	local = philo->info->finish;
	pthread_mutex_unlock(&philo->info->finish_mutex);
	while (!local)
	{
		if (timestamp() - i >= time)
			break ;
		usleep(50);
	}
	return	(0);
}
