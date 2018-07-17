/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprior <lprior@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:37:08 by asyed             #+#    #+#             */
/*   Updated: 2018/07/16 18:05:03 by lprior           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <stdio.h>
void			*g_pages[3] = {NULL, NULL, NULL};
pthread_mutex_t	g_mutex[3] = {
	PTHREAD_MUTEX_INITIALIZER,
	PTHREAD_MUTEX_INITIALIZER,
	PTHREAD_MUTEX_INITIALIZER
};

static int	finite_block(void **curr_page, t_header **l_page,
						size_t req_len, size_t pagesize)
{
	if ((*l_page)->len >= req_len)
	{
		(*l_page)->used = 1;
		return (0);
	}
	else if ((*l_page)->next_page)
	{
		*curr_page = (*l_page)->next_page;
		*l_page = (t_header *)(*curr_page);
	}
	else if (OFFP_HEADER((*l_page)) < (*curr_page + pagesize))
		*l_page = OFFP_HEADER((*l_page));
	else
		next_page(l_page, curr_page, pagesize);
	return (1);
}

static int	infinite_block(void **curr_page, t_header **l_page,
						size_t req_len, size_t pagesize)
{
	void	*void_page;

	printf("\nin infinite block\n");
	void_page = (void *)(*l_page);
	printf("void_page = %p and plus 1 = %p\n", (t_header *)void_page, (t_header *)void_page + 1);
	if ((void_page + req_len + sizeof(t_header)) <= (*curr_page + pagesize))
	{
		printf("in if ((void_page + req_len + sizeof(t_header)) <= (*curr_page + pagesize))\n");
		(*l_page)->used = 1;
		(*l_page)->len = req_len;
		void_page = *l_page;//whats this line for? It doesnt change the pointer adress at all!
		if ((void_page + (*l_page)->len + sizeof(t_header)) <= (*curr_page + pagesize - sizeof(t_header)))
		{
			printf("now in if ((void_page + (*l_page)->len + sizeof(t_header)) <= (*curr_page + pagesize - sizeof(t_header))) before %p after %p\n", *l_page, (t_header *)(void_page + sizeof(t_header) + (*l_page)->len));
			((t_header *)(void_page + sizeof(t_header) + (*l_page)->len))->next_page = (*l_page)->next_page;
			(*l_page)->next_page = NULL;
		}
		return (0);
	}
	else if ((*l_page)->next_page)
	{
		*curr_page = (*l_page)->next_page;
		*l_page = (t_header *)(*curr_page);
		return (1);
	}
	next_page(l_page, curr_page, pagesize);
	return (1);
}

int			used_seg(t_header **l_page, void **curr_page, size_t pagesize)
{
	if ((*l_page)->next_page)
	{
		*curr_page = (*l_page)->next_page;
		*l_page = (t_header *)(*curr_page);
		return (1);
	}
	if (OFFP_HEADER((*l_page)) >= (*curr_page + pagesize))
	{
		next_page(l_page, curr_page, pagesize);
		return (1);
	}
	return (0);
}

void		*find_space(void *curr_page, size_t pagesize, size_t req_len)
{
	t_header	*l_page;

	printf("\nfind space(void * curr_page %p(memory block), page_size = %zu and req_len = %zu))\n", curr_page,pagesize, req_len);
	l_page = (t_header *)curr_page;//this is why you need to 
	while (l_page && (void *)l_page < (curr_page + pagesize))
	{
		printf("iterating while loop\n");
		if (!l_page->used)
		{
			l_page->page_start = curr_page;
			printf("in if (!l_page->used):::l_page->page_start is being initialize to curr_page\n");
			if (!l_page->len)
			{
				printf("in if (!l_page->len) going to infinite_block(&curr_page, &l_page, %zu, %zu\n", req_len, pagesize);
				if (infinite_block(&curr_page, &l_page, req_len, pagesize))
					continue ;
			}
			else if (finite_block(&curr_page, &l_page, req_len, pagesize))
			{
				continue ;
			}
			return ((void *)l_page);
		}
		if (used_seg(&l_page, &curr_page, pagesize))
		{
			printf("in if (used_seg(&l_page, &curr_page, pagesize))\n");
			continue ;
		}
		l_page = OFFP_HEADER(l_page);
	}
	return (NULL);
}

void		*malloc(size_t size)
{
	printf("size = %zu\n", size);
	if (size == 0)
		size = 1;
	if (size <= TINY)
	{
		printf("in TINY\n");
		return (size_spacer(TINY_IND, align_pagesize(TINY, 0), size));
	}
	if (size > TINY && size < LARGE)
	{
		printf("in MIDDLE\n");
		return (size_spacer(SMALL_IND, align_pagesize(LARGE, 0), size));
	}
	return (alloc_large(LARGE_IND,
			align_pagesize(size, 1), size));
}
