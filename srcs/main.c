#include "my.h"

char	is_c(char *str)
{
	size_t	count;

	count = -1;
	while (str[++count])
	{
		if (str[count] == '.' && str[count + 1] == 'c')
			return (1);
	}
	return (0);
}

size_t	ft_strlen(const char const *str)
{
	size_t	count;

	count = -1;
	while (str[++count])
		;
	return (count);
}

char	*create_src(char *dir, char *name)
{
	size_t	cn[2] = {-1, -1};
	char	*new;

	if (name == NULL)
		return (0);
	if (dir == NULL)
		return (0);
	if (!(new = malloc(sizeof(*new) * (ft_strlen(dir) + ft_strlen(name) + 2))))
		return (0);
	while (dir[++cn[0]])
		new[cn[0]] = dir[cn[0]];
	new[cn[0]] = '/';
	while (name[++cn[1]])
		new[++cn[0]] = name[cn[1]];
	new[++cn[0]] = '\0';
	return (new);
}

char	findc(char *name, int out)
{
	DIR				*fd;
	struct dirent	*dir;
	struct stat		buff;
	char			*src;
	char			f;
	const char		*msg = " content :\n";

	f = 1;
	src = NULL;
	if (!(fd = opendir(name)))
		return (0);
	while ((dir = readdir(fd)))
	{
		if (!(src = create_src(name, dir->d_name)))
			return (0);
		lstat(src, &buff);
		if ((S_ISDIR(buff.st_mode)) && (*dir->d_name != '.'))
		{
			printf("\x1b[1;31mEntering in : %s !\n\x1b[0;00m", dir->d_name);
			findc(src, out);
		}
		else if (is_c(dir->d_name))
		{
			if (f)
			{
				printf("\x1b[1;33mSource File Found In %s :\n\x1b[0;00m", name);
				write(out, "\n", 1);
				write(out, name, strlen(name));
				write(out, msg, strlen(msg));
			}
			f = 0;
			write(out, dir->d_name, strlen(dir->d_name));
			write(out, " \\\n", 3);
			//printf("\x1b[0;33m%s\n\x1b[0;00m", dir->d_name);
		}
		free(src);
	}
	closedir(fd);
	return (1);
}

int		main(void)
{
	int		out;
	char	*current;
	const char	*str = "###LIST OF .C####";

	current = NULL;
	if ((out = open("save", O_CREAT | O_RDWR, 0666)) == -1)
	{
		printf("\x1b[1;31mopen error.\n\x1b[0;00m");
		return (0);
	}
	write(out, str, strlen(str));
	write(out, "\n", 1);
	if (!(current = getcwd(current, 0)))
		return (0);
	printf("\x1b[1;37mHi %s We Finding Source File .C In %s :\n\x1b[0;00m", getenv("USER"), current);
	printf("\x1b[1;31mEntering in : %s\n\x1b[0;00m", current);
	if (!(findc(current, out)))
	{
		printf("\x1b[1;31mmalloc error\n\x1b[0;00m");
		return (0);
	}
	printf("\x1b[1;37mAll Source File Found Was Written On \"save\" File.\n\x1b[0;00m");
	printf("\x1b[1;37mThx For Use.\n\x1b[0;00m");
	free(current);
	return (1);
}
