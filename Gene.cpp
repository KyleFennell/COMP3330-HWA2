#include "Gene.h"

namespace HWA2{

	Gene::Gene(std::vector<int>& geneIn){
		_gene = geneIn;
		_fitness = 0;
	}

	std::vector<int> Gene::gene() const{
		return _gene;
	}

	float Gene::fitness() const{
		return _fitness;
	}
		
	void Gene::fitness(double fitnessIn){
		_fitness = fitnessIn;
	}

	int Gene::cardinality() const{
		int cardinality = 0;
		for (std::size_t i = 0; i < _gene.size(); i++){
			if (_gene[i] == 1){
				cardinality++;
			}
		}
		return cardinality;
	}

	std::vector<int> Gene::activeIndexs() const{
		// std::cout << "activeIndexs entered " << std::endl;
		std::vector<int> out(cardinality());
		int crntindex = 0;
		for (std::size_t i = 0; crntindex < cardinality(); i++){
			if (_gene[i] == 1){
				out[crntindex] = i;
				crntindex++;
			}
		}
		return out;
	}

	int Gene::size() const{
		return _gene.size();
	}

	bool Gene::operator==(const Gene& other){
		return (this->_gene == other.gene());
	}

	std::ostream& operator<<(std::ostream& stream, const Gene& gene){
		for (int i = 0; i < gene.cardinality(); i++){
			stream << gene.activeIndexs()[i] << " ";
		}
		return stream;
	}
}