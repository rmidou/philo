/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:04:24 by rmidou            #+#    #+#             */
/*   Updated: 2024/04/14 13:45:09 by rmidou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	args(char **av, t_main *philo)
{
	if (ft_isdigit(av[1]) && ft_isdigit(av[2]) && ft_isdigit(av[3])
		&& ft_isdigit(av[4]))
	{
		if (ft_atoi(av[1]) == 1)
			init_philo1(ft_atoi(av[2]));
		else
		{
			philo->nb_philo = ft_atoi(av[1]);
			philo->ttd = ft_atoi(av[2]);
			philo->tte = ft_atoi(av[3]);
			philo->tts = ft_atoi(av[4]);
			philo->nbr_philo_eat = 2147483647;
		}
	}
	else
	{
		printf("philosophers: wrong arguments: <number_of_philosophers> "
			"<time_to_die> <time_to_eat> <time_to_sleep>"
			"[number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	if (ft_isdigit(av[5]))
		philo->nbr_philo_eat = ft_atoi(av[5]);
	return (1);
}

void	init(t_main *main)
{
	int	i;

	i = 0;
	main->philos = malloc(sizeof(t_philo) * main->nb_philo);
	main->forks = malloc(sizeof(pthread_mutex_t) * main->nb_philo);
	while (i < main->nb_philo)
	{
		ft_bzero(&main->philos[i], sizeof(t_philo));
		main->philos[i].main = main;
		main->philos[i].fork1 = &(main->forks[i]);
		main->philos[i].fork2 = &(main->forks[(i + 1) % main->nb_philo]);
		main->philos[i].ttd = main->ttd;
		main->philos[i].tte = main->tte;
		main->philos[i].tts = main->tts;
		main->philos[i].id = i + 1;
		main->philos[i].eat = 0;
		i++;
	}
}

void	create_mutex(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->nb_philo)
	{
		pthread_mutex_init(&(main->forks[i]), NULL);
		i++;
	}
}

void	init_philo(t_main *main)
{
	int	i;

	i = -1;
	create_mutex(main);
	while (++i < main->nb_philo)
	{
		pthread_create(&(main->philos[i].thread),
			NULL, &routine, &main->philos[i]);
	}
	check_death(main);
	i = -1;
	while (++i < main->nb_philo)
		pthread_join(main->philos[i].thread, NULL);
}

void	init_philo1(int ttd)
{
	printf("%d %d %s\n", 0, 1, "has taken a fork");
	ft_usleep(ttd);
	printf("%d %d %s\n", ttd, 1, "died");
	exit(0);
}
