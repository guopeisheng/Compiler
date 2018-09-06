#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class instruction {
public:
	string label = "";
	string opcode = "";
	
	vector<string> leftOperands;
	vector<string> rightOperands;
	
	int line_number = 0;
};