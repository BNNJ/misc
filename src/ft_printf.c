#include "ft_printf.h"

int		ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		++len;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dest;

	len = 0;
	while (s1[len])
		++len;
	if (!(dest = (char*)malloc(len + 1)))
		return (NULL);
	while (*s1)
		*dest++ = *s1++;
	*dest = '\0';
	return (dest - len);
}

int		ft_findchar(const char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		++i;
	}
	return (-1);
}


char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(substr = malloc(len + 1)))
		return (NULL);
	while (i < len)
	{
		substr[i] = s[start + i];
		++i;
	}
	substr[i] = '\0';
	return (substr);
}

static int	ftpf_handle_litteral(char *str)
{
	return (write(1, str, ft_strlen(str)));
}

static int	ftpf_get_flags(va_list ap, const char *format)
{
	char c;

	if (format[1] == 'c')
		c = (char)va_arg(ap, int);
	return (write(1, &c, 1) + 1);
}

static int	ftpf_core(const char *format, va_list ap)
{
	int		i;

	if (!format)
		return (-1);
	while (*format)
	{
		if ((i = ft_findchar(format, '%')) < 0)
			i = ftpf_handle_litteral(ft_strdup(format));
		else if (i > 0)
			i = ftpf_handle_litteral(ft_strsub(format, 0, i));
		else
			i = ftpf_get_flags(ap, format);
		format += i;
	}
	return (i);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int ret;

	va_start(ap, format);
	ret = ftpf_core(format, ap);
	va_end(ap);
	return (ret);
}
