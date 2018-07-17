/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprior <lprior@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 00:14:58 by asyed             #+#    #+#             */
/*   Updated: 2018/07/16 18:01:57 by lprior           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		*init_page(size_t pagesize)
{
	void	*tmp;

	printf("\nin init page, pagesize = [%zu]\n", pagesize);
	if ((tmp = mmap(NULL, pagesize, PROT_ALL, FT_MAP_ANON, -1, 0))
				== MAP_FAILED)
		return (NULL);
	return (tmp);
}

int			next_page(t_header **l_page, void **curr_page, size_t pagesize)
{
	void	*tmp;

	if (!(tmp = init_page(pagesize)))
		return (-1);
	(*l_page)->next_page = tmp;
	(*l_page)->chksum = chksum(*l_page);
	*curr_page = tmp;
	(*l_page) = (t_header *)(*curr_page);
	return (0);
}


//gets the system_size with getpagesize
//page is parsed based on large and is either set to x + sizeof(t_header)if true, or ((x + sizeof(t_header)) * MAX_PER_PAGE) if small or tiny
//after page it it for some reason it returns page + (page % sys_size));
int		align_pagesize(size_t x, int large)
{
	static int	sys_size = 0;//he keeps this static because he only needs to call it once
	size_t		page;

	// printf("in align pagesize x = %lu large = %d\n", x, large);
	if (!sys_size)
		sys_size = getpagesize();
	if (large)
		page = x + sizeof(t_header);//he does sizeof(t_haeder) because later he will be casting a memory block found by mmap to a t_header
	else
		page = PAGESIZE(x);
	printf("\npage = %zu and sys_size = %d\n", page, sys_size);
	printf("align_pagesize = [%zu]\n", page + (page % sys_size));
	return (page + (page % sys_size));
}

static int	in_large(void *ptr, int page_index)
{
	void	*head;
	void	*l_ptr;
	size_t	pagesize;

	if (page_index == LARGE_IND)
	{
		if (!(head = g_pages[LARGE_IND]))
			return (0);
		l_ptr = head;
		pagesize = align_pagesize(((t_header *)head)->len, 1);
		while (l_ptr && l_ptr < head + pagesize)
		{
			if (ptr >= head && ptr <= head + pagesize)
				return (1);
			head = ((t_header *)l_ptr)->next_page;
			l_ptr = head;
		}
	}
	return (0);
}

int			non_allocated(void *ptr, int page_index)
{
	void	*head;
	void	*l_ptr;
	size_t	pagesize;

	if (page_index < LARGE_IND)
	{
		head = g_pages[page_index];
		l_ptr = head;
		pagesize = align_pagesize(get_memseg_size(page_index), 0);
		while (l_ptr && l_ptr < (head + pagesize))
		{
			if (ptr >= head && ptr < (head + pagesize))
				return (1);
			if (((t_header *)l_ptr)->next_page)
			{
				head = ((t_header *)l_ptr)->next_page;
				l_ptr = head;
				continue ;
			}
			l_ptr = OFFP_HEADER(((t_header *)l_ptr));
		}
		return (non_allocated(ptr, page_index + 1));
	}
	return (in_large(ptr, page_index));
}
