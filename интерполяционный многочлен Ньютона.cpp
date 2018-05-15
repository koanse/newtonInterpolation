#include <stdio.h>
#include <conio.h>
#include <math.h>

void err1();
void err2();


main()
{
    FILE *input;
	input = fopen("input.dat", "r");
	if(!input) { err1(); return 0; }				// проверка существования файла	
	
	
	unsigned int n, i, j, code, combinations, sum;	// code - для кодирования при перемножении
	double *x, *y, *Y, *tmpY, *a, tmp;				// Y - разделенные разности
													// n - количество точек
	
	fscanf(input, "%d", &n);
	x = new double[n];
	y = new double[n];
	Y = new double[n];
	tmpY = new double[n];
	a = new double[n];
	
	for(i = 0; i < n; i++)
	{
		if(!fscanf(input, "%lf", &x[i])) { err1(); return 0; }
		if(i > 0 && x[i] <= x[i-1]) { err2(); return 0; }
	}
	for(i = 0; i < n; i++)
		if(!fscanf(input, "%lf", &y[i])) { err1(); return 0; }
	fclose(input);
    
	for(i = 0; i < n; i++)
		printf("x[%d] = %.3lf\ty[%d] = %.3lf\n", i, x[i], i, y[i]);

	for(i = 0; i < n; i++)
		tmpY[i] = y[i];

	Y[0] = y[0];
	
	for(i = 0; i < n - 1; i++)
	{
		for(j = 0; j < n - i; j++)
			tmpY[j] = (tmpY[j+1] - tmpY[j]) / (x[j+1+i] - x[j]);
		Y[i+1] = tmpY[0];
	}

	printf("---\ni\ty(x0,x1,...,xi)\n");
	for(i = 0; i < n; i++) printf("%d\t%.3lf\n", i, Y[i]);
	printf("---\nAnswer\n");


	// Нахождение коэффициентов многочлена
    for(i = 0; i < n; i++)
		a[i] = 0.0;
	
	for(i = 0; i < n; i++)
	{
		combinations = powf(2, i);
		for(code = 0; code < combinations; code++)
		{
			sum = 0;
			tmp = 1;
			for(j = 0; j < i; j++)
			{
				sum += code << (32 - i + j) >> 31;
				if(!(code << (32 - i + j) >> 31))
					tmp *= -x[j];
			}
            a[sum] += tmp * Y[i];
		}
	}

	for(i = 0; i < n; i++) printf("a[%d] = %.6lf\n", i, a[i]);
	getch();

	return 0;
}

void err1()
{
	printf("Impossible to read from the file");
	getch();
	return;
}

void err2()
{
	printf("Wrong input data");
	getch();
	return;
}