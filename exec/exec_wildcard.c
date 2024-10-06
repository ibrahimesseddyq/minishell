/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 20:07:37 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/06 20:28:00 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_expanded_string(t_lst *env, t_arg_node *lst)
{
	char	*exp_str_empty;
	char	*expanded_str;

	exp_str_empty = NULL;
	expanded_str = ft_expand(lst->arg, env);
	if (!ft_strcmp(lst->arg, "\"\"")
		|| !ft_strcmp(lst->arg, "\'\'") || !expanded_str[0])
	{
		exp_str_empty = (char *)gcalloc(2);
		exp_str_empty[0] = *get_splitted_char(3);
		exp_str_empty[1] = '\0';
		return (exp_str_empty);
	}
	else
		return (expanded_str);
}

char	*expand_wd(char *expanded_arg)
{
	char			**pattern;
	char			**found_files;
	int				found_count;
	t_wildcard_data	data;
	char			*pwd;

	found_files = NULL;
	pattern = gcalloc(sizeof(char *) * 2);
	pwd = ft_strdup(".");
	found_count = 0;
	pattern[0] = ft_strdup(expanded_arg);
	pattern[1] = ft_strdup("");
	data.pattern = pattern;
	data.found_files = &found_files;
	data.found_count = &found_count;
	return (expand_wildcard(pwd, 0, &data));
}

char	*expand_wd_redir(char *expanded_arg)
{
	char			**pattern;
	char			**found_files;
	int				found_count;
	t_wildcard_data	data;
	char			*pwd;

	found_files = NULL;
	pattern = gcalloc(sizeof(char *) * 2);
	pwd = ft_strdup(".");
	found_count = 0;
	pattern[0] = ft_strdup(expanded_arg);
	pattern[1] = ft_strdup("");
	data.pattern = pattern;
	data.found_files = &found_files;
	data.found_count = &found_count;
	return (expand_wildcard(pwd, 0, &data));
}
