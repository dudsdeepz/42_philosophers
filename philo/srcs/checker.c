/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:33:14 by eduarodr          #+#    #+#             */
/*   Updated: 2023/07/20 20:03:19 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_things(t_philo *philo)
{
	long int	current;

	check_full();
	pthread_mutex_lock(&status()->philo->time);
	current = (gettime() - status()->starting_time);
	pthread_mutex_unlock(&status()->philo->time);
	check_dead(philo, current);
	pthread_mutex_lock(&status()->life);
	pthread_mutex_lock(&status()->food);
	if (status()->is_dead || status()->is_full)
	{
		pthread_mutex_unlock(&status()->food);
		pthread_mutex_unlock(&status()->life);
		return (1);
	}
	pthread_mutex_unlock(&status()->food);
	pthread_mutex_unlock(&status()->life);
	return (0);
}

void	check_dead(t_philo *philo, long int current)
{
	pthread_mutex_lock(&status()->life);
	if (status()->is_dead)
	{
		pthread_mutex_unlock(&status()->life);
		return ;
	}
	pthread_mutex_lock(&status()->food);
	if ((current - philo->last_meal) >= status()->time_to_die)
	{
		pthread_mutex_unlock(&status()->food);
		printf("%s%li %s%i %s %s\n", YELLOW, \
			current, RED, philo->num, DEFAULT, "has died");
		status()->is_dead = 1;
		pthread_mutex_unlock(&status()->life);
		return ;
	}
	pthread_mutex_unlock(&status()->food);
	pthread_mutex_unlock(&status()->life);
	usleep(20);
	return ;
}

void	check_full(void)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	pthread_mutex_lock(&status()->food);
	if (status()->is_full
		|| status()->number_of_times_each_philosopher_must_eat == -1)
	{
		pthread_mutex_unlock(&status()->food);
		return ;
	}
	while (i < status()->number_of_philosophers)
	{
		if (status()->philo[i].eat_count
			>= status()->number_of_times_each_philosopher_must_eat)
			counter++;
		i++;
	}
	if (counter == status()->number_of_philosophers)
		status()->is_full = 1;
	pthread_mutex_unlock(&status()->food);
	return ;
}

int	check_forks(t_philo *philo)
{
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_left->fork_lock);
		pthread_mutex_lock(&philo->fork_right.fork_lock);
	}
	else
	{
		pthread_mutex_lock(&philo->fork_right.fork_lock);
		pthread_mutex_lock(&philo->fork_left->fork_lock);
	}
	if (philo->fork_left->fork_take == 0 && philo->fork_right.fork_take == 0)
	{
		pthread_mutex_unlock(&philo->fork_right.fork_lock);
		pthread_mutex_unlock(&philo->fork_left->fork_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->fork_right.fork_lock);
	pthread_mutex_unlock(&philo->fork_left->fork_lock);
	return (0);
}
