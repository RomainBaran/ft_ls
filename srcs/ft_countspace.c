/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 16:19:36 by rbaran            #+#    #+#             */
/*   Updated: 2016/04/06 18:06:16 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

size_t		ft_countnb(long int nb)
{
	size_t	res;

	res = 1;
	if (nb == 0)
		res++;
	else
		while (nb)
		{
			res++;
			nb /= 10;
		}
	return (res);
}

static void		ft_checkspaces(t_entry *entries, size_t spaces[5])
{
	size_t			nb;
	struct passwd	*name;
	struct group	*grp;

	spaces[0] = (nb = ft_countnb(entries->stats.st_nlink)) > spaces[0] ? nb : spaces[0];
	if ((name = getpwuid(entries->stats.st_uid)))
	{
		if ((nb = ft_strlen(name->pw_name) > spaces[1]))
			spaces[1] = nb;
	}
	else if ((nb = ft_countnb(entries->stats.st_uid)) > spaces[1])
		spaces[1] = nb;
	if ((grp = getgrgid(entries->stats.st_gid)))
	{
		if ((nb = ft_strlen(grp->gr_name) > spaces[2]))
			spaces[2] = nb;
	}
	else if ((nb = ft_countnb(entries->stats.st_gid)) > spaces[2])
		spaces[2] = nb;
	if (!S_ISCHR(entries->stats.st_mode) && !S_ISBLK(entries->stats.st_mode))
	{
		if ((nb = ft_countnb(entries->stats.st_size)) > spaces[3])
			spaces[3] = nb;
	}
	else
	{
		if ((nb = ft_countnb(MAJOR(entries->stats.st_rdev))) > spaces[3])
			spaces[3] = nb;
		if ((nb = ft_countnb(MINOR(entries->stats.st_rdev))) > spaces[4])
			spaces[4] = nb;
	}
	if ((nb = ft_countnb(entries->stats.st_nlink)) > spaces[0])
		spaces[0] = nb;
	if ((nb = ft_strlen(getpwuid(entries->stats.st_uid)->pw_name)) > spaces[1])
		spaces[1] = nb;
	if ((nb = ft_strlen(getgrgid(entries->stats.st_gid)->gr_name)) > spaces[2])
		spaces[2] = nb;
	if ((nb = ft_countnb(entries->stats.st_size)) > spaces[3])
		spaces[3] = nb;
}

size_t		*ft_countspace(t_entry *entries, int flag)
{
	static size_t	spaces[5] = {0, 0, 0, 0, 0};

	if (flag == SET)
		while (entries)
		{
			ft_checkspaces(entries, spaces);
			entries = entries->next;
		}
	else
		ft_bzero(spaces, sizeof(spaces));
	return ((size_t*)spaces);
}
