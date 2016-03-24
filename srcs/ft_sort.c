/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 15:02:28 by rbaran            #+#    #+#             */
/*   Updated: 2016/03/24 14:27:11 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_entry	*ft_sortentry(t_entry *begin_entries, int flag)
{
	t_entry	*turtle_entry;
	t_entry	*entries;
	t_entry	*max;
	t_entry	*limit;

	limit = NULL;
	while (ft_lastentry(begin_entries, limit) != begin_entries)
	{
		entries = ft_lastentry(begin_entries, limit);
		if (flag == 0)
			max = ft_findmax_name(begin_entries, limit);
		else
			max = ft_findmax_path(begin_entries, limit);
		turtle_entry = ft_lastentry(begin_entries, max);
		if (max == begin_entries)
			begin_entries = begin_entries->next;
		else if (max->next != limit)
			turtle_entry->next = max->next;
		max->next = entries->next;
		if (max != entries)
			entries->next = max;
		limit = max;
	}
	return (begin_entries);
}