#include <vector>

int number_of_nodes(const vector<int> *from, const vector<int> *to);
bool number_in_multiplicity(int number, const vector<int> *m);

class Multiplicity{
	public:
   	vector<int> items;
      bool includes(int number);
};
 