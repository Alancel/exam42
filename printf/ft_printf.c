#include <unistd.h>
#include <stdarg.h>

int ft_numlen(long num, int base)
{
	int i;

	i = 1;
	while (num >= base)
	{
		num /= base;
		i++;
	}
	return (i);
}

void ft_putnbr(long num, int base, char *base_str)
{
	while (num >= base)
		ft_putnbr(num / base, base, base_str);
	write(1, &base_str[num % base], 1);
}

int ft_printf(const char *format, ...)
{
	va_list args;
	char *str, *s;
	long nbr;
	int len, length, width, prec, neg, sp, zr;

	va_start(args, format);
	length = 0;
	str = (char *)format;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			len = 0;
			neg = 0;
			sp = 0;
			zr = 0;
			width = 0;
			prec = -1;
			while (*str >= '0' && *str <= '9')
			{
				width = width * 10 + (*str - 48);
				str++;
			}
			if (*str == '.')
			{
				str++;
				prec = 0;
				while (*str >= '0' && *str <= '9')
				{
					prec = prec * 10 + (*str - 48);
					str++;
				}
			}
			if (*str == 's')
			{
				s = va_arg(args, char *);
				if (!s)
					s = "(null)";
				while (s[len])
					len++;
			}
			if (*str == 'd')
			{
				nbr = va_arg(args, int);
				if (nbr < 0)
				{
					nbr = -nbr;
					neg = 1;
				}
				len = ft_numlen(nbr, 10) + neg;
			}
			if (*str == 'x')
			{
				nbr = va_arg(args, unsigned);
				len = ft_numlen(nbr, 16);
			}
			if (prec > len && *str != 's')
				zr = prec - len;
			else if (prec > -1 && prec < len && *str == 's')
				prec = len;
			else if (prec == 0 && (*str == 's' || nbr == 0))
				len = 0;
			sp = width - zr - neg - len;
			while (sp-- > 0)
				length += write(1, " ", 1);
			if (neg == 1)
				write(1, "-", 1);
			while (zr-- > 0)
				length += write(1, "0", 1);
			if (*str == 's')
				write(1, s, len);
			else if (len > 0 && *str == 'd')
				ft_putnbr(nbr, 10, "0123456789");
			else if (len > 0 && *str == 'x')
				ft_putnbr(nbr, 16, "0123456789abcdef");
			length += len;
		}
		else
			length += write(1, str, 1);
		str++;
	}
	va_end(args);
	return (length);
}
