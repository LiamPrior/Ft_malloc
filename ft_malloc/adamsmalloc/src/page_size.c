/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprior <lprior@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:26:22 by asyed             #+#    #+#             */
/*   Updated: 2018/07/16 18:49:23 by lprior           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

uint8_t	chksum(void *mem)
{
	uint8_t		sum;
	size_t		i;

	sum = 0;
	i = 0;
	((t_header *)mem)->chksum = 0;
	while (i++ < sizeof(t_header))
	{
		sum += *(unsigned char *)mem;
		mem++;
	}
	return (sum);
}

void	*size_spacer(int page_index, size_t pagesize, size_t size)
{
	void			**fetched_seg;
	pthread_mutex_t	*mutex_lock;
	void			*mem_seg;

	printf("\ninside size_spacer pageindex = %d pagesize = %zu size = %zu\n", page_index, pagesize, size);
	fetched_seg = &(g_pages[page_index]);
	mutex_lock = &(g_mutex[page_index]);//he has a seperate thread or whatever for each type of size is requested
	pthread_mutex_lock(mutex_lock);//locks in the process

	if (!*fetched_seg)
	{
		printf("if (!(*fetched_seg = init_page(pagesize)))\n");
		if (!(*fetched_seg = init_page(pagesize)))//fetched segment is equal to a new memory space
			return (NULL);
	}
	printf("after feteched_seg has been allocated with mmap now we are initializing mem_seg with find_space:)\n");
	if (!(mem_seg = find_space(*fetched_seg, pagesize, size)))
	{
		printf("if (!(mem_seg = find_space(*fetched_seg, pagesize, size))\n");
		return (NULL);
	}
	printf("after all that shit\n");
	((t_header *)mem_seg)->index = page_index;
	((t_header *)mem_seg)->chksum = chksum(mem_seg);
	pthread_mutex_unlock(mutex_lock);
	return (mem_seg + sizeof(t_header));
}

int		get_memseg_size(uint8_t index)
{
	if (index == TINY_IND)
		return (TINY);
	else if (index == SMALL_IND)
		return (LARGE - 1);
	else if (index == LARGE_IND)
		return (LARGE);
	else
		return (0);
}
