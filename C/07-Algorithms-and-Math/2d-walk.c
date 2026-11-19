#include <stdio.h>
#include <stdlib.h>


	//Fill in code below
	//When deciding which way to go for the next step, generate a random number as follows.
	//r = rand() % 4;
	

	//The random walk should stop once the x coordinate or y coordinate reaches $-n$ or $n$. 
	//The function should return the fraction of the visited $(x, y)$ coordinates inside (not including) the square.
	/*Imagine a random walker starting For example, when the walker
is at (x, y), with equal probability 1/4, their next location is at (x, y − 1), (x + 1, y), (x, y + 1), or (x − 1, y).
Given a positive integer n, a square is defined by the following four points: (−n, −n), (−n, n), (n, n), and
(n, −n). We are interested in knowing, on average, what fraction of points within this square the walker
visits before they touch one of the edges of the square, given they start their walk from (0, 0).

*/
double two_d_random(int n){
	// This function should return the fraction mentioned above. n is the integer mentioned above to define the square boundary.
	int x = 0;
	int y = 0;
	int size = 2*n-1;
	int visited[size][size]; //making an array to keep track of where weve been and filling it
	for (int i=0; i < (size); i++){
		for (int j=0; j < (size); j++){
			visited[i][j] = 0;
		}
	}
	visited[n-1][n-1] = 1; 
	
	while (1) { 
		
		int r = rand() % 4; //Treat r = 0, 1, 2, 3 as up, right, down and left respectively.
		//move based on r
		if (r == 0){
			y += 1;
		}
		else if(r==1){
			x += 1;
		}	
		else if(r==2){
			y -= 1;
		}
		else{
			x -= 1;
		}

		if ((x == n) || (x == -n) || (y == n) || (y == -n)){ //The random walk should stop once the x coordinate or y coordinate reaches −n or n.
			break;
		}
		//we break before we add so that it doesnt add the edges if it hits it.
		//add to array, make sure no negatives
		int ix = x + (n - 1);
		int iy = y + (n - 1);

		visited[ix][iy] = 1;
	
	}
	double count = 0.0;
	for (int i=0; i < size; i++){

		for (int j=0; j < size; j++){

			if (visited[i][j] == 1) count++;
		}
	}
	return count/(size*size);
// return the fraction of the visited (x, y) coordinates inside (not including) the square.
}
//Do not change the code below
int main(int argc, char *argv[])
{
	int trials = 1000;
	int i, n, seed;
	if (argc == 2) seed = atoi(argv[1]);
	else seed = 12345;

	srand(seed);
	for(n=1; n<=64; n*=2)
	{	
		double sum = 0.;
		for(i=0; i < trials; i++)
		{
			double p = two_d_random(n);
			sum += p;
		}
		printf("%d %.3lf\n", n, sum/trials);
	}
	return 0;

}

