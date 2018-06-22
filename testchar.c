#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int		main()
{
	wchar_t f = 64;
	wchar_t d = 177;
	wchar_t	c = 0x1234;
	wchar_t e = L'是';

//	setlocale(LC_ALL, "en_US.UTF-8");
	setlocale(LC_ALL, "");
	printf("f : %c\nd : %c\nc : %c\ne : %c\n", f, d, c, e);
	printf("F : %C\nD : %C\nC : %C\nE : %C\n", f, d, c, e);
	return 0;
}
