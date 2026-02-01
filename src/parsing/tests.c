#include <stdio.h>

size_t	n_cmds(char *line)
{
	size_t	i;
	short	squote;
	short	dquote;
	size_t	count;

	squote = 0;
	dquote = 0;
	count = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\"' && !squote)
			dquote = 1 - dquote;
		if (line[i] == '\'' && !dquote)
			squote = 1 - squote;
		else if (!dquote && !squote && line[i] == '|')
			count++;
	}
	if (squote || dquote)
		return (0);
	return (count + 1);
}

int main()
{
	printf("%lu\n", n_cmds("a b | \"\'\"\'|\'"));
}