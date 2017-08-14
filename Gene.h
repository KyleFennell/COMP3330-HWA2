#ifndef Gene_H
#define Gene_H
#include <cstdlib>
#include <vector>
#include <iostream>

namespace HWA2{

	class Gene{

	public:

		Gene();

		Gene(std::vector<int>&);

		std::vector<int> gene() const;

		float fitness() const;

		void fitness(double);

		int cardinality() const;

		std::vector<int> activeIndexs() const;

		int size() const;

		bool operator==(const Gene&);

	private:

		std::vector<int> _gene;
		double _fitness;

	};
	
	std::ostream& operator<<(std::ostream&, const Gene&);

}

#endif