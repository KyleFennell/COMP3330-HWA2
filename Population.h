#ifndef Population_H
#define Population_H
#include <cstdlib>
#include <vector>
#include "Gene.h"

namespace HWA2{
	
	class Population{
	
	public:

		Population();

		Population(int);

		void readDataset();

		double calculateFitness();

		void reproduce(int, int);

		void mutate(std::vector<int>&, int);

		Gene bestGene() const;

	private:

		void generatePopulation();

		double differentialScore(const Gene&) const;

		double correctness(const Gene&) const;

		std::vector<int> nPointCrossover(const Gene&, const Gene&, int);

		std::vector<Gene> *pop;
		std::vector<std::vector<int> > *dataset;
		std::vector<std::vector<Gene>* > *history;
		Gene* _bestGene;
		int popSize;

	};
}

#endif