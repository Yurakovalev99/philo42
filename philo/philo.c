/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:58:05 by ysachiko          #+#    #+#             */
/*   Updated: 2022/03/29 17:42:46 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	struct timeval	tv;

	pthread_mutex_lock(philo->left_fork_m);
	gettimeofday(&tv, NULL);
	philo->time = time_to_ms(tv);
	ft_custom_printf(philo, "has taken a fork");
	// printf("philo %d takes left fork\n", philo->num + 1);
	pthread_mutex_lock(philo->right_fork_m);
	gettimeofday(&tv, NULL);
	philo->time = time_to_ms(tv);
	ft_custom_printf(philo, "has taken a fork");
	// printf("philo %d takes right fork\n", philo->num + 1);
}

void	eating(t_philo *philo)
{
	struct timeval	tv;

	pthread_mutex_lock(&philo->check_mutex);
	philo->last_after_eat = philo->last_time_eat;
	ft_custom_printf(philo, "is eating\n");
	ft_sleep(philo->info->time_eat);
	pthread_mutex_unlock(&philo->check_mutex);
	pthread_mutex_unlock(philo->right_fork_m);
	pthread_mutex_unlock(philo->left_fork_m);
	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&philo->check_mutex);
	philo->last_time_eat = time_to_ms(tv);
	pthread_mutex_unlock(&philo->check_mutex);
}

void	thinking(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	philo->time = time_to_ms(tv);
	ft_custom_printf(philo, "is thinking\n");
}

void	sleeping(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	philo->time = time_to_ms(tv);
	ft_custom_printf(philo, "is sleeping\n");
	ft_sleep(philo->info->time_sleep);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	long long	ms;

	philo = arg;
	while(!philo->info->finish)
	{
		usleep(50);
		pthread_mutex_lock(&philo->check_mutex);
		pthread_mutex_lock(&philo->info->finish_m);
		ms = philo->last_time_eat - philo->last_after_eat;
		if ((ms > philo->info->time_die) && !philo->info->finish)
		{
			pthread_mutex_lock(&philo->info->finish_mutex);
			philo->info->finish = 1;
			pthread_mutex_unlock(&philo->info->finish_mutex);
			pthread_mutex_unlock(philo->right_fork_m);
			pthread_mutex_unlock(philo->left_fork_m);
			printf("Philosoph %d is dead :(\n", philo->num + 1);
		}
		pthread_mutex_unlock(&philo->info->finish_m);
		pthread_mutex_unlock(&philo->check_mutex);
	}
	return(NULL);
}

void	*func(void *arg)
{
	t_philo	*args;
	struct timeval	tv;
	pthread_t	thread;

	args = arg;
	usleep(50);
	gettimeofday(&tv, NULL);

	pthread_create(&thread, NULL, monitor, (void *)(args));
	pthread_detach(thread);
	while (!args->info->finish)
	{
		// printf("%lld\n", time_to_ms(tvalSecond, args->last_time_eat));
			take_forks(args);
			eating(args);
			sleeping(args);
			thinking(args);
	}
	gettimeofday(&tv, NULL);
	// printf("TV = %lld\n", (tv.tv_sec * 1000 + tv.tv_usec / 1000) - args->time_start);
	// printf("Philosoph %d is dead :(\n", args->num + 1);
	// exit (0);
	// printf("%d\n", args->time_die);
	return (NULL);
}
