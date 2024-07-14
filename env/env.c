

void	env(char **env)
{
	t_lst *lst;
	t_lst *new;
	int i;

	i = 0;
	while (lst)
	{
		new = ft_lstadd_new_env(env[i],);
		i++;
		lst = lst->next;
	}
}