/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:58:05 by ysachiko          #+#    #+#             */
/*   Updated: 2022/04/02 18:31:14 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->finish_mutex);
	if (philo->info->finish == 1)
	{
		pthread_mutex_unlock(&philo->info->finish_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->finish_mutex);
	pthread_mutex_lock(philo->right_fork_m);

	if (ft_custom_printf(philo, "has taken a fork"))
		return (1);
	// printf("philo %d takes left fork\n", philo->num + 1);
	pthread_mutex_lock(philo->left_fork_m);
	if (ft_custom_printf(philo, "has taken a fork"))
		return (1);
	// printf("philo %d takes right fork\n", philo->num + 1);
	return (0);
}

int	eating(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&philo->info->finish_mutex);
	if (philo->info->finish == 0)
		philo->last_time_eat = time_to_ms(tv);
	else if (philo->info->finish == 1)
	{
	pthread_mutex_unlock(philo->right_fork_m);
	pthread_mutex_unlock(philo->left_fork_m);
	pthread_mutex_unlock(&philo->info->finish_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->finish_mutex);
	// pthread_mutex_lock(&philo->check_mutex);
	// philo->last_after_eat = philo->last_time_eat;
	if (ft_custom_printf(philo, "is eating"))
		return (1);
	// pthread_mutex_unlock(&philo->check_mutex);
	if(ft_sleep(philo->info->time_eat, philo))
		return (1);

	pthread_mutex_unlock(philo->right_fork_m);
	pthread_mutex_unlock(philo->left_fork_m);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (ft_custom_printf(philo, "is thinking"))
		return (1);
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (ft_custom_printf(philo, "is sleeping"))
		return (1);
	if (ft_sleep(philo->info->time_sleep, philo))
		return (1);
	return (0);
}

void	*func(void *arg)
{
	t_philo	*args;
	struct timeval	tv;
	// int	local;
	// pthread_t	thread;

	args = arg;
	if (args->num % 2 == 0)
		usleep(15000);
	gettimeofday(&tv, NULL);
	while (1)
	{
		// printf("%lld\n", time_to_ms(tvalSecond, args->last_time_eat));
		if (take_forks(args))
			break;
		if (eating(args))
			break;
		if (sleeping(args))
			break;
		if (thinking(args))
			break;
	}
	printf ("end of thread");
	// printf("TV = %lld\n", (tv.tv_sec * 1000 + tv.tv_usec / 1000) - args->time_start);
	// printf("Philosoph %d is dead :(\n", args->num + 1);
	// exit (0);
	// printf("%d\n", args->time_die);
	return (NULL);
}
