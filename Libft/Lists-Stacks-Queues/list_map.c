/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 19:33:17 by akharrou          #+#    #+#             */
/*   Updated: 2019/03/04 13:17:20 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**    NAME
**         list_map -- create a new list out of mapped element of another list.
**
**    SYNOPSIS
**         #include <../libft.h>
**
**         int
**         list_map(t_list **dest, t_list *src, t_list *(*f)(t_list *elem));
**
**    PARAMETERS
**
**         t_list **dest                   Pointer to the destination pointer
**                                         of the new list.
**
**         t_list *src                     Pointer to the head of the source
**                                         list.
**
**         t_list *(*f)(t_list *elem)      Mapping function that takes a list
**                                         elements, and returns a different
**                                         list element.
**
**    DESCRIPTION
**         Creates a new list out of mapped elements from the 'src' list,
**         storing the head of the new list in (*dest). The mapped elements
**         are generated by the mapping function 'f()'.
**
**    RETURN VALUES
**         Returns 0 if successful; otherwise -1.
*/

#include "../Includes/stdlib_42.h"
#include "../Includes/list.h"

int		list_map(t_list **dest, t_list *src, t_list *(*f)(t_list *elem))
{
	t_list	*new_elem;
	t_list	*previous;

	if (src && *f)
	{
		(*dest) = (*f)(src);
		previous = (*dest);
		src = src->next;
		while (src)
		{
			new_elem = (*f)(src);
			previous->next = new_elem;
			previous = new_elem;
			src = src->next;
		}
		previous->next = NULL;
		return (0);
	}
	return (-1);
}
