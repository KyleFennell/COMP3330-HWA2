#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <list>
#include <iterator>
#include <iostream>
#include "Population.h"

using namespace std;
namespace HWA2{

	Population::Population(int popSizeIn){
		std::srand(std::time(0));
		popSize = popSizeIn;
		pop = new std::vector<Gene>;
		readDataset();
		std::cout << "dataset read" << std::endl;
		generatePopulation();
		std::cout << "population created" << std::endl;

	}


	void Population::readDataset(){
		dataset = new std::vector<std::vector<int> >;
		int ds[31][13] = {	{0, 0, 0 ,0 ,1, 0, 0, 1, 1, 0, 0, 0, 1},	//1864
							{1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1},	//1868
							{1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},	//1872
							{1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1},	//1880
							{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},	//1888
							{0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1},	//1900
							{1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},	//1904
							{1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1},	//1908
							{0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},	//1916
							{0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1},	//1924
							{1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},	//1928
							{0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1},	//1936
							{1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1},	//1940
							{1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1},	//1944
							{1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},	//1948
							{0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},	//1956
							{0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},	//1964
							{0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1},	//1972
							{1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0},	//1860
							{1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0},	//1876
							{1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0},	//1884
							{0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0},	//1892
							{0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0},	//1896
							{1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0},	//1912
							{1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0},	//1920
							{1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0},	//1932
							{1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0},	//1952
							{1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},	//1960
							{1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0},	//1968
							{1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0},	//1976
							{0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0}};	//1980

		for (int i = 0; i < 31; i++){
			std::vector<int> temp;
			for (int j = 0; j < 13; j++){
				temp.push_back(ds[i][j]);
			}
			dataset->push_back(temp);
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
		_bestGene = &pop->operator[](0);
	}

//------------------------------------------------------------------------------------------------------------------------

	double Population::calculateFitness(){
		double totalFitness = 0;
		for (std::size_t i = 0; i < pop->size(); i++){			// for each gene in the population
			Gene& temp = pop->operator[](i);
			double fitness = differentialScore(temp)*(1-((double)temp.cardinality()/temp.size()))*correctness(temp);
			temp.fitness(fitness);
			if (temp.fitness() > _bestGene->fitness()){
				_bestGene = &temp;
			}
			totalFitness += fitness;
		}
		return totalFitness/pop->size();
	}

	void Population::reproduce(int noOfCrosspoints, int mutationMethod){
		std::vector<Gene> pool;
		for (std::size_t i = 0; i < pop->size(); i++){		// for each gene in the population
			//cout << pop->at(i).fitness() << endl;
			for (int j = 0; j < pop->operator[](i).fitness()*100; j++){		// 
				pool.push_back(pop->operator[](i));

			}
		}
		// cout << pool.size() << endl;
		std::vector<Gene> newPop;
		for (std::size_t i = 0; i < pop->size(); i++){
			Gene parent1 = pool.operator[](std::rand()%pool.size());
			Gene parent2 = pool.operator[](std::rand()%pool.size());
			std::vector<int> child = nPointCrossover(parent1, parent2, noOfCrosspoints);
			mutate(child, mutationMethod);
			newPop.push_back(Gene(child));
		}
		// cout << "crossovers complete" << endl;
		//history->push_back(pop);
		*pop = newPop;
	}

	void Population::mutate(std::vector<int>& child, int mutationMethod){
		if(std::rand()%10 == 1){
			int index = std::rand()%sizeof(child);
			child[index] = (child[index]+1)%2;			
		}
	}

//------------------------------------------------------------------------------------------------------------------------

	double Population::differentialScore(const Gene& gene) const{
		// cout << "differentialScore entered" << endl;
		std::vector<std::vector<int> >* sets = new std::vector<std::vector<int> >;
		// cout << "cardinality: " << gene.cardinality() << ":" << gene.activeIndexs().size()<< endl;
		// cout << "dataset size: " << dataset->size() << endl;
		for (size_t i = 0; i < dataset->size(); i++){ 					// loop through the dataset
			// GETTING STUCK HERE ON SECOND ROUND
			// cout << "dataset position: ";
			// cout << i << endl;
			std::vector<int> seti(gene.activeIndexs().size());				// new temp vector to hold this set
			for (int k = 0; k < gene.activeIndexs().size(); k++){			// decode the active set
				// cout << gene.activeIndexs()[k] << " ";
				seti[k] = dataset->operator[](i)[gene.activeIndexs()[k]];	
			}
			if (std::find(sets->begin(), sets->end(), seti) == sets->end()){	// if the set is new
				// cout << "\na " << sets->size() << endl;
				sets->push_back(seti);										// add it to the list of sets
				// cout << "b " << sets->size() << endl;
			}
			// cout << "i " << i << endl;
		}
		// cout << "leaving differentialScore" << endl;
		return (double)sets->size()/gene.size();
	}

	double Population::correctness(const Gene& gene) const{
		// cout << "correctness entered" << endl;
		std::list<std::vector<int> >* sets = new std::list<std::vector<int> >;
		std::list<std::vector<int> >* classSets = new std::list<std::vector<int> >;
		for (std::size_t j = 0; j < dataset->size(); j++){ 					// loop through the dataset
			std::vector<int> seti(gene.cardinality()+1);						// new temp vector to hold this set
			for (int k = 0; k < gene.cardinality(); k++){					// decode the active set
				seti[k] = dataset->operator[](j)[gene.activeIndexs()[k]];
			}
			seti[gene.cardinality()] = 2;
			if (std::find(sets->begin(), sets->end(), seti) == sets->end()){	// if the set is new
				sets->push_front(seti);										// add it to the list of sets
			}
			seti[gene.cardinality()] = dataset->operator[](j)[gene.size()];
			if (std::find(classSets->begin(), classSets->end(), seti) == classSets->end()){	// if the set is new
				classSets->push_front(seti);									// addbestGene it to the list of sets
			}
		}
		// cout << sets->size() << ":" << classSets->size() << ":" << gene.cardinality() << endl;
		if (sets->size() == classSets->size())
			return 1;
		return 0.5;
	}

//------------------------------------------------------------------------------------------------------------------------

	std::vector<int> Population::nPointCrossover(const Gene& parent1, const Gene& parent2, int noOfCrosspoints){
		
		std::vector<int> childGene;
		std::vector<int> crossPoints;
		const Gene* activeParent = &parent1;
		
		for (std::size_t i = 0; crossPoints.size() < noOfCrosspoints; i++){		// creating the crossover points
			int crosspoint = std::rand()%parent1.size();
			if (std::find(crossPoints.begin(), crossPoints.end(), crosspoint) == crossPoints.end()){
				crossPoints.push_back(crosspoint);
				// cout << crosspoint << endl;
			}
		}
		// cout << "crossover points found" << endl;
		for (std::size_t i = 0; i < parent1.size(); i++){
			childGene.push_back(activeParent->gene()[i]);
			if (std::find(crossPoints.begin(), crossPoints.end(), i) != crossPoints.end()){
				if (activeParent == &parent1){
					activeParent = &parent2;
				}
				else{
					activeParent = &parent1;
				}
			}
		}
		// cout << "crossover complete" << endl;
		return childGene;
	}

	Gene Population::bestGene() const{
		return *_bestGene;
	}
}