/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:35:39 by eduarodr          #+#    #+#             */
/*   Updated: 2023/07/20 17:45:01 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_philo(t_philo *philo)
{
	if (status()->number_of_philosophers == 1)
	{
		print_action(philo, "is thinking");
		wait(philo, status()->time_to_die);
		print_action(philo, "has died");
		return ;
	}
	while (1)
	{
		if (check_things(philo))
			break ;
		forks(philo, 1);
		eating(philo);
		forks(philo, 0);
		sleeping(philo);
	}
	return ;
}

void	eating(t_philo *philo)
{
	print_action(philo, "is eating");
	pthread_mutex_lock(&status()->food);
	pthread_mutex_lock(&philo->meal);
	pthread_mutex_lock(&status()->philo->time);
	philo->last_meal = gettime() - status()->starting_time;
	philo->eat_count += 1;
	pthread_mutex_unlock(&status()->philo->time);
	pthread_mutex_unlock(&status()->food);
	pthread_mutex_unlock(&philo->meal);
	wait(philo, status()->time_to_eat);
	return ;
}

void	sleeping(t_philo *philo)
{
	print_action(philo, "is sleeping");
	wait(philo, status()->time_to_sleep);
	print_action(philo, "is thinking");
	return ;
}

void	forks(t_philo *philo, int stats)
{
	if (stats)
	{
		while (!check_forks(philo))
			{
				if (check_things(philo))
					return ;
			}
		if (philo->num % 2 == 0)
			fork_take(philo, 1);
		else
			fork_take(philo, 0);
		return ;
	}
	else if (!stats)
	{
		if (philo->num % 2 == 0)
			fork_leave(philo, 0);
		else
			fork_leave(philo, 1);
		return ;
	}
}

void	wait(t_philo *philo, time_t time)
{
	time_t	start;
	time_t	current;

	pthread_mutex_lock(&status()->philo->time);
	start = gettime();
	pthread_mutex_unlock(&status()->philo->time);
	while (1)
	{
		if (check_things(philo))
			break ;
		current = gettime();
		if ((current - start) >= time)
			return ;
	}
	return ;
}

int check_forks(t_philo *philo)
{
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_right.fork_lock);
		pthread_mutex_lock(&philo->fork_left->fork_lock);
	}
	else
	{		
		pthread_mutex_lock(&philo->fork_left->fork_lock);
		pthread_mutex_lock(&philo->fork_right.fork_lock);
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