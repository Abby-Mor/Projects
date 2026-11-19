#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, i;
	printf("n = ");
	scanf("%d", &n);
	double first, second, third, fourth, divide = 1;
	double pi = 0;
	for(int i = 0; i <= n; i++){
		first = 4.0/((8*i)+1);
		second = 2.0/((8*i)+4);
		third = 1.0/((8*i)+5);
		fourth = 1.0/((8*i)+6);
		pi += (first - second - third - fourth)*(1/divide);
		divide *= 16.;
	}
	
	printf("PI = %.10f\n", pi);
	return 0;
}
