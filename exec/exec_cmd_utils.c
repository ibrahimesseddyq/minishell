int is_num(char c)
{
	if(c >= '0' && c <= '9')
		return (1);
	return (0);
}

int check_export_errors(char *str)
{
	if(!str || is_num(str[0]) || str[0] == '=' || !str[0] || ft_strcmp(str,"\"\"") == 0 || ft_strcmp(str,"\'\'") == 0)
		return 1;
	return 0;
}

char *char_to_string(char c)
{
	char *str = gcalloc(2);
	if (!str)
		return NULL;
	str[0] = c;
	str[1] = '\0';
	return str;
}