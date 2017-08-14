#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <list>
#include <iostream>
#include "Population.h"

namespace HWA2{

	Population::Population(int popSizeIn){
		std::srand(std::time(0));
		popSize = popSizeIn;
		generatePopulation();

	}


	void Population::readDataset(){
		int ds[9][12] = {	{0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1},
							{0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
							{0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
							{0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
							{1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
							{1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1},
							{1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
							{0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
							{1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1}};

		for (int i = 0; i < sizeof(ds); i++){
			std::cout << i << std::endl;
			// dataset[i] = new std::vector<int>;
			for (int j = 0; j < sizeof(ds[i]); j++){
				dataset[i].push_back(ds[i][j]);
			}
		}
	}

	void Population::generatePopulation(){
		for (int i = 0; i < popSize; i++){
			std::vector<int> gene;
			for (std::size_t j = 0; j < dataset->operator[](0).size()-1; j++){
				gene.push_back(std::rand()%2);
			}
			pop->insert(pop->end(), Gene(gene));
		}
	}

//------------------------------------------------------------------------------------------------------------------------

	double Population::calculateFitness(){
		double totalFitness = 0;
		for (std::size_t i = 0; i < pop->size(); i++){			// for each gene in the population
			Gene temp = pop->operator[](i);
			double fitness = differentialScore(temp)*((1-temp.cardinality())/temp.size())*correctness(temp);
			temp.fitness(fitness);
			totalFitness += fitness;
		}
		return totalFitness/pop->size();
	}

	void Population::reproduce(int noOfCrosspoints, int mutationMethod){
		std::vector<Gene> pool;
		for (std::size_t i = 0; i < pop->size(); i++){
			for (int j = 0; j < pop->operator[](i).fitness()*100; j++){
				pool.push_back(pop->operator[](i));
			}
		}
		std::vector<Gene> newPop;
		for (std::size_t i = 0; i < pop->size(); i++){
			Gene parent1 = pool.operator[](std::rand()%pool.size());
			Gene parent2 = pool.operator[](std::rand()%pool.size());
			std::vector<int> child = nPointCrossover(parent1, parent2, noOfCrosspoints);
			mutate(child, mutationMethod);
			newPop.push_back(*(new Gene(child)));
		}
		history->push_back(pop);
		*pop = newPop;
	}

	void Population::mutate(std::vector<int>& child, int mutationMethod){
		int index = std::rand()%sizeof(child);
		child[index] = (child[index]+1)%2;
	}

//------------------------------------------------------------------------------------------------------------------------

	double Population::differentialScore(const Gene& gene) const{
		std::list<int*> sets;
		for (std::size_t j = 0; j < dataset->size(); j++){ 		// loop through the dataset

			int* seti = new int[gene.cardinality()];			// new temp vector to hold this set
			for (int k = 0; k < gene.cardinality(); k++){	// decode the active set
				seti[gene.activeIndexs()[k]] = dataset->operator[](j)[gene.activeIndexs()[k]];	
			}
			if (std::find(sets.begin(), sets.end(), seti) == sets.end()){	// if the set is new
				sets.push_front(seti);										// add it to the list of sets
			}
		}
		return sets.size()/gene.size();
	}

	double Population::correctness(const Gene& gene) const{
		std::list<int*> sets;
		std::list<int*> classSets;
		for (std::size_t j = 0; j < dataset->size(); j++){ 		// loop through the dataset
			int* seti = new int[gene.cardinality()+1];			// new temp vector to hold this set
			for (int k = 0; k < gene.cardinality(); k++){		// decode the active set
				seti[k] = dataset->operator[](j)[gene.activeIndexs()[k]];
			}
			seti[gene.cardinality()] = 2;
			if (std::find(sets.begin(), sets.end(), seti) == sets.end()){	// if the set is new
				sets.push_front(seti);										// add it to the list of sets
			}
			seti[gene.cardinality()] = dataset->operator[](j)[gene.size()];
			if (std::find(classSets.begin(), classSets.end(), seti) == classSets.end()){	// if the set is new
				classSets.push_front(seti);									// add it to the list of sets
			}
		}
		if (sets.size() == classSets.size())
			return 1;
		return 0.5;
	}

//------------------------------------------------------------------------------------------------------------------------

	std::vector<int> Population::nPointCrossover(const Gene& parent1, const Gene& parent2, int noOfCrosspoints){
		std::vector<int> childGene;
		std::vector<int> crossPoints;
		Gene* activeParent;
		*activeParent = parent1;
		for (std::size_t i = 0; crossPoints.size() <= noOfCrosspoints; i++){
			int crosspoint = std::rand()%parent1.size();
			if (std::find(crossPoints.begin(), crossPoints.end(), crosspoint) != crossPoints.end()){
				crossPoints.push_back(crosspoint);
			}
		}
		for (std::size_t i = 0; i < parent1.size(); i++){
			childGene[i] = activeParent->gene()[i];
			if (std::find(crossPoints.begin(), crossPoints.end(), i) != crossPoints.end()){
				if (*activeParent == parent1){
					*activeParent = parent2;
				}
				else{
					*activeParent = parent1;
				}
			}
		}
		return childGene;
	}
}