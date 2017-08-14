#include <cstdlib>
#include <iostream>
#include "Population.h"

using namespace HWA2;
using namespace std;
int main(int argc, char* args[]){

	Population population(10);
	double fitness, bestFitness = 0;
	int iterations = 0, itWithoutImprovement = 0;
	while(itWithoutImprovement < 20){
		// cout << "new iteration" << endl;
		fitness = population.calculateFitness();
		// cout << "fitness calculated" << endl;
		population.reproduce(1, 0);
		// cout << "reproduction complete" << endl;

		if (fitness-bestFitness > 0){
			bestFitness = fitness;
			itWithoutImprovement = 0;
		}
		itWithoutImprovement++;
		iterations++;
		// cout << iterations << endl;
		// cout << "GENERATION FINISHED" << endl;
	}

	cout << "final fitness: " << bestFitness << endl;
	cout << "in " << iterations << " iterations" << endl;
	cout << "Best gene: " << population.bestGene() << endl;

	return 0;
}