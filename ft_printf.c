/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:38:13 by alphbarr          #+#    #+#             */
/*   Updated: 2024/08/09 14:11:58 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdarg.h>
#include <unistd.h>

void put_str(char *s, int *len) {
    if (!s)
        s = "(null)";
    while (*s)
        *len += write(1, s++, 1);
}

void put_dig(int n, int base, int *len) {
    char *hexa = "0123456789abcdef";
    unsigned int num;

    if (n < 0 && base == 10)
	{
		*len += write(1, "-", 1);
        num = -n;                 // Convierte a positivo
    }
	else
        num = (unsigned int)n;
    if (num >= (unsigned int)base)
        put_dig(num / base, base, len);
    *len += write(1, &hexa[num % base], 1);
}

int ft_printf(char *f, ...) {
    int len = 0;
    va_list args;

    va_start(args, f);
    while (*f) {
        if (*f == '%' && *(f + 1)) {
            f++;
            if (*f == 's')
                put_str(va_arg(args, char *), &len);
            else if (*f == 'd')
                put_dig(va_arg(args, int), 10, &len);
            else if (*f == 'x')
                put_dig(va_arg(args, unsigned int), 16, &len);
        } else {
            len += write(1, f, 1);
        }
        f++;
    }
    return (va_end(args), len);
}/*
#include <stdio.h>
int	main(void)
{
	int					a;
	int					b;
	int					num;
	unsigned int		unum;
	unsigned long long	ptr;

	//  char *str = "\001\002\007\v\010\f\r\n";
	num = 12345;
	unum = -10;
	ptr = (unsigned long long)&num;
	b = printf("%d", 10);
	printf("\n");
	a = ft_printf("%d", 10);
	printf("\n");
	printf("mi printf devuelve: %d\n", a);
	printf("printf original devuelve: %d\n", b);
	ft_printf("Unsigned number: %u\n", unum);
	ft_printf("Hexadecimal: %x\n", unum);
	printf("%x\n", -10);
	ft_printf("Hexadecimal (uppercase): %X\n", unum);
	ft_printf("Pointer: %p\n", ptr);
	return (0);
}*/
