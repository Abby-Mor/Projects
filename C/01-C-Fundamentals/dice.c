//In this assignment, we implement a function that simulates the outcome of tossing of 3 dice.
//We will learn how to generate random numbers, and how to seed a random number generator.
//For example, we use the following code to generate a random number between 1 and 6.
// rand() % 6 + 1
//The following code set the seed of the random number generator to 12345.
// srand(12345);

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//TO DO
//Implement a function named cum_prob below.
//This function takes an integer k, and a long integer trials as inputs.
//This function returns a double value.
//In the fucntion, we toss the 3 dice multiple times. The number of tosses is trials.
//We count the number of times that the outcomes of the 3 dice add up to at least k.
////And we then use this number and trials to calculate the probability that 
//the sum of the 3 dice is at least k.
//Finally, we return this probablity. 

double cum_prob(int k, long trials)
{
	long count = 0; // Count of successful outcomes

	for (long i = 0; i < trials; i++) {
		// Simulate tossing 3 dice
		int die1 = rand() % 6 + 1;
		int die2 = rand() % 6 + 1;
		int die3 = rand() % 6 + 1;

		// Calculate the sum of the three dice
		int sum = die1 + die2 + die3;

		// Check if the sum is at least k
		if (sum >= k) {
			count++;
		}
	}
	// Calculate the probability
	double probability = (double)count / trials;
	return probability;
}





//Do not change the following code.
int main()
{
	long n = 10000000;
	int k;

	printf("Enter k :");	
	scanf("%d", &k);
	assert(k>= 3 && k<=18);
	srand(12345);
	printf("P(sum of the 3 dice is at least %d) = %.5lf\n", k, cum_prob(k, n));
	return 0;
}
