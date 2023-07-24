int	is_space(char c)
{
	if ((c == ' ') || (c == '\t'))
		return (1);
	return (0);
}

int	count_words(char *str)
{
	int idx;
	int	begin_space;
    int j;

	begin_space = 0;
	while (str[begin_space] != '\0' && is_space(str[begin_space]))
		begin_space++;
	idx = begin_space;
	while (str[idx] != '\0')
	{
		if (str[idx] != '\0' && !is_space(str[idx]) && is_space(str[idx - 1]))
		{
			while (str[idx] != '\0' && !is_space(str[idx]))
			{
				j++;
				idx++;
			}
			j++;
		}
		idx++;
	}
	return (j);
}

char *remove_space(char *str)
{
	int i;
	char *res;
	int j;
	int len;

	i = 0;
	j = 0;
	len = count_words(str) + 1;
	res = (char *)malloc(len);
	if (res == NULL)
		return (NULL);
	while (str[i] != '\0' && is_space(str[i]))
		i++;
	while (str[i] != '\0')
	{
		if (str[i] != '\0' && !is_space(str[i]) && is_space(str[i - 1]))
		{
			while (str[i] != '\0' && !is_space(str[i]))
			{
				res[j] = str[i];
				printf ("%c\n", res[j]);
				j++;
				i++;
			}
			if (str[i] != '\0' && (j + 2) < len) {
				res[j] = str[i];
				j++;
			}
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

int	main(int ac, char **av)
{
	if (ac > 1)
	{
		printf ("[%s]\n", remove_space(av[1]));
	}
	return (0);
}