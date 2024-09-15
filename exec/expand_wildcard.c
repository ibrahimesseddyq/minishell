void expand_wildcards_in_list(t_arg_node *args)
{
	t_arg_node *current = args;

	while (current)
	{
		if (strchr(current->arg, '*'))
		{
			char **expanded_args = expand_wildcard(current->arg);

			if (expanded_args && expanded_args[0])
			{
				t_arg_node *new_start_node = replace_node_args(current, expanded_args, count_args(expanded_args));
				if (new_start_node)
				{
					current = new_start_node;
					while (current && current->next)
					{
						current = current->next;
					}
				}
			}
		}
		current = current->next;
	}
}
char	**expand_wildcard(const char *pattern)
{
	glob_t globbuf;
	char **result = NULL;

	if (glob(pattern, GLOB_NOCHECK, NULL, &globbuf) == 0)
	{
		result = gcalloc(sizeof(char *) * (globbuf.gl_pathc + 1));
		for (size_t i = 0; i < globbuf.gl_pathc; i++)
		{
			result[i] = ft_strdup(globbuf.gl_pathv[i]);
		}
		result[globbuf.gl_pathc] = NULL;
	}

	return result;
}