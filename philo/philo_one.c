/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:24:29 by ysachiko          #+#    #+#             */
/*   Updated: 2022/03/30 19:03:04 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	ft_sleep(long long time, t_philo *philo)
{
	long long	i;

	i = philo->num;
	i = timestamp();

	// pthread_mutex_lock(&philo->check_mutex);
	while (!philo->info->finish)
	{
		if (timestamp() - i >= time)
			break ;
		usleep(50);
	}
	// pthread_mutex_unlock(&philo->check_mutex);
}
