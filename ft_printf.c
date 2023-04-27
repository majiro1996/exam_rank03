
/*Assignment name  : ft_printf
Expected files   : ft_printf.c
Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
--------------------------------------------------------------------------------

Write a function named `ft_printf` that will mimic the real printf but
it will manage only the following conversions: s,d and x.

Your function must be declared as follows:

int ft_printf(const char *, ... );

Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
To test your program compare your results with the true printf.

Exemples of the function output:

call: ft_printf("%s\n", "toto");
out: toto$

call: ft_printf("Magic %s is %d", "number", 42);
out: Magic number is 42%

call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
out: Hexadecimal for 42 is 2a$*/

#include <stdarg.h>
#include <unistd.h>

void ft_put_str(char *str, int *len)
{
	int c;

	c = 0;
	if (!str)
		str = "(null)";
	while (str[c])
	{
		*len += write(1, &str[c], 1);
		c++;
	}
}

void ft_put_nbr(long long int nbr, int base, int *len)
{
	char *str = "0123456789abcdef";

	if (nbr < 0)
	{
		nbr = nbr * -1;
		*len += write(1, "-", 1);
	}
	if (nbr >= base)
		ft_put_nbr(nbr/base, base, len);
	*len = write(1, &str[nbr % base], 1);
}

int ft_printf(const char *format, ...)
{
	va_list param;
	int		len;
	int 	c;
	
	c = 0;
	len = 0;
	va_start(param, format);
	while (format[c])
	{
		if (format[c] == '%' && (format[c + 1] == 's' || format[c + 1] == 'x' || format[c + 1] == 'd'))
		{
			c++;
			if (format[c] == 's')
					ft_put_str(va_arg(param, char *), &len);
			if (format[c] == 'd')
					ft_put_nbr((long long int)va_arg(param, int), 10,  &len);
			if(format[c] == 'x')
					ft_put_nbr((long long int)va_arg(param, unsigned int), 16, &len);
		}
		else
			len += write(1, &format[c], 1);
		c++;
	}
	va_end(param);
	return (len);
}

int main(void)
{
	ft_printf("hola holita %s\n", "vecinito");
	ft_printf("decimal %d\n", 42);
	ft_printf("hexadecimal %x\n", 42);
}
