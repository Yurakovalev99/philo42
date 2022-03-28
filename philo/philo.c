/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:58:05 by ysachiko          #+#    #+#             */
/*   Updated: 2022/03/28 18:03:15 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	struct timeval	tv;

	if (philo->left == philo->right)
		return (1);
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
	return (0);
}

void	eating(t_philo *philo)
{
	struct timeval	tv;

	philo->last_after_eat = philo->last_time_eat;
	ft_custom_printf(philo, "is eating\n");
	ft_sleep(philo->info->time_eat);
	pthread_mutex_unlock(philo->left_fork_m);
	pthread_mutex_unlock(philo->right_fork_m);
	gettimeofday(&tv, NULL);
	philo->last_time_eat = time_to_ms(tv);
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

void	*func(void *arg)
{
	t_philo	*args;
	struct timeval	tv;

	args = arg;
	gettimeofday(&tv, NULL);
	if (args->num % 2 == 0)
		usleep(500);
	while (args->last_time_eat - args->last_after_eat  < args->info->time_die)
	{
		// printf("%lld\n", time_to_ms(tvalSecond, args->last_time_eat));
		if(take_forks(args))
			break;
		eating(args);
		sleeping(args);
		thinking(args);
	}
	gettimeofday(&tv, NULL);
	printf("TV = %lld\n", (tv.tv_sec * 1000 + tv.tv_usec / 1000) - args->time_start);
	printf("Philosoph %d is dead :(\n", args->num);
	exit (0);
	// printf("%d\n", args->time_die);
	return (NULL);
}
