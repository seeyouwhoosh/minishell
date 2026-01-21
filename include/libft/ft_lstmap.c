/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:48:33 by xwu               #+#    #+#             */
/*   Updated: 2025/07/17 17:37:18 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*ltemp;
	void	*lcontent;

	if (!lst || !f)
		return (NULL);
	newlst = NULL;
	while (lst)
	{
		lcontent = f(lst->content);
		ltemp = ft_lstnew(lcontent);
		if (!ltemp)
		{
			del(lcontent);
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, ltemp);
		lst = lst->next;
	}
	return (newlst);
}
