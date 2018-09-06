#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <unordered_map>
#include <math.h>
#include <algorithm>
#include "opt.h"

using namespace std;


unordered_map<string, int> label_to_line_num;


void input_parse(string filename, vector<instruction> &instructions) {
	ifstream infile;
	infile.open(filename);
	string line = "";
	int line_number = 0;
	while (getline(infile, line)) {
		if (line.find("/") != string::npos) {
			// for (int i = 0; i < line.length(); i++) {
			// 	if (line[i] == '/') {
			// 		line = line.substr(0, i);
			// 	}
			// }
      line=line.substr(0, line.find("/"));
		}
		instruction instr;
		line_number++;
		instr.line_number = line_number;
		if (line.find("nop") != string::npos) {
					instr.label = line.substr(0, line.find(":"));
					instr.opcode = "nop";
					instructions.push_back(instr);
					label_to_line_num[instr.label] = instr.line_number;
		} 
    else {
			int i = 0;
			while (isalpha(line[i]) && i < line.length()) {
				i++;
			}
			i++;
			for (int j = i; j < line.length(); j++) {
				string opcode = "";
				opcode += line[j++];
				while ((isalnum(line[j]) || line[j] == '_') && j < line.length()) {
					opcode += line[j];
					j++;
				}
				instr.opcode = opcode;
				if (opcode == "halt") {
					instructions.push_back(instr);
					return;
				}
				else if (opcode == "output" || opcode == "coutput" || opcode == "write" || opcode == "cwrite") {
					while (line[j] == ' ' && j < line.length()) {
						j++;
					}
					string tmp = "";
					tmp += line[j++];
					while (line[j] != ' ' && j < line.length()) {
						tmp += line[j];
						j++;
					}
					instr.leftOperands.push_back(tmp);
					instructions.push_back(instr);
					break;
				}
				else if (opcode == "br") {
					while (line[j] != '-' && j < line.length()) {
						j++;
					}
					j+=2;
					while (line[j] == ' ' && j < line.length()) {
						j++;
					}
					string tmp = "";
					while (isalnum(line[j]) && j < line.length()) {
						tmp += line[j];
						j++;
					}
					instr.rightOperands.push_back(tmp);
					instructions.push_back(instr);
					break;
				}
				else if (opcode == "cbr") {
					while (line[j] == ' ' && j < line.length()) {
						j++;
					}
					string left = "";
					left += line[j++];
					while (isalnum(line[j]) && j < line.length()) {
						left += line[j];
						j++;
					}
					instr.leftOperands.push_back(left);
					while (line[j] != '-' && j < line.length()) {
						j++;
					}
					j+=2;
					while (line[j] == ' ' && j < line.length()) {
						j++;
					}
					string right1 = "";
					right1 += line[j++];
					while (line[j] != ',' && j < line.length()) {
						right1 += line[j];
						j++;
					}
					j++;
					while (line[j] == ' ' && j < line.length()) {
						j++;
					}
					string right2 = "";
					right2 += line[j++];
					while (isalnum(line[j]) && j < line.length()) {
						right2 += line[j];
						j++;
					}
					instr.rightOperands.push_back(right1);
					instr.rightOperands.push_back(right2);
					instructions.push_back(instr);
					break;
				}
				else if (opcode == "read" || opcode == "cread") {
					while (line[j] == ' ' && j < line.length()) {
						j++;
					}
					j+=2;
					while (line[j] == ' ' && j < line.length()) {
						j++;
					}
					string tmp = "";
					while (isalnum(line[j]) && j < line.length()) {
						tmp += line[j];
						j++;
					}
					instr.rightOperands.push_back(tmp);
					instructions.push_back(instr);
					break;
				}
				else if (opcode == "not" || opcode == "loadI" || opcode == "load"
						|| opcode == "cload" || opcode == "store" || opcode == "cstore" || opcode == "i2i"
						|| opcode == "c2c" || opcode == "i2c" || opcode == "c2i")
				{
					while (line[j] == ' ' && j < line.length()) {
						j++;
					}
					string left = "";
					left += line[j++];
					while (isalnum(line[j]) && j < line.length()) {
						left += line[j];
						j++;
					}
					while (line[j] != '=' && j < line.length()) {
						j++;
					}
					j+=2;
					while (line[j] == ' ' && j < line.length()) {
						j++;
					}
					string right = "";
					right += line[j++];
					while (isalnum(line[j]) && j < line.length()) {
						right += line[j];
						j++;
					}
					instr.leftOperands.push_back(left);
					instr.rightOperands.push_back(right);
					instructions.push_back(instr);
					break;
				}
				else if (opcode == "storeAI" || opcode == "storeAO" || opcode == "cstoreAI" || opcode == "cstoreAO") {
					while (line[j] == ' ' && j < line.length()) {
						j++;
					}
					string left = "";
					left += line[j++];
					while (isalnum(line[j]) && j < line.length()) {
						left += line[j];
						j++;
					}
					while (line[j] != '=' && j < line.length()) {
						j++;
					}
					j+=2;
					while (line[j] == ' ' && j < line.length()) {
						j++;
					}
					string right1 = "";
					right1 += line[j++];
					while (line[j] != ',' && j < line.length()) {
						right1 += line[j];
						j++;
					}
					j++;
					while (line[j] == ' ' && j < line.length()) {
						j++;
					}
					string right2 = "";
					right2 += line[j++];
					while (isalnum(line[j]) && j < line.length()) {
						right2 += line[j];
						j++;
					}
					instr.leftOperands.push_back(left);
					instr.rightOperands.push_back(right1);
					instr.rightOperands.push_back(right2);
					instructions.push_back(instr);
					break;
				}
				else {
					while (line[j] == ' ' && j < line.length()) {
						j++;
					}
					string left1 = "";
					left1 += line[j++];
					while (line[j] != ',' && j < line.length()) {
						left1 += line[j];
						j++;
					}
					j++;
					while (line[j] == ' ' && j < line.length()) {
						j++;
					}
					string left2 = "";
					left2 += line[j++];
					while (isalnum(line[j]) && j < line.length()) {
						left2 += line[j];
						j++;
					}
					while (line[j] != '=' && j < line.length()) {
						j++;
					}
					j+=2;
					while (line[j] == ' ' && j < line.length()) {
						j++;
					}
					string right = "";
					right += line[j++];
					while (isalnum(line[j]) && j < line.length()) {
						right += line[j];
						j++;
					}
					instr.leftOperands.push_back(left1);
					instr.leftOperands.push_back(left2);
					instr.rightOperands.push_back(right);
					instructions.push_back(instr);
					break;
				}
			}
		}

	}
}

void output_reduction(vector<instruction> instructions) {
	ofstream outfile;
	outfile.open ("output.txt", ios::out);
	for (auto instr : instructions) {
		if (instr.opcode == "halt") {
			outfile << instr.opcode << endl;
		}
		else if (instr.opcode == "nop") {
			outfile << instr.label+": "+instr.opcode << endl;
		}
		else if (instr.opcode == "output" || instr.opcode == "coutput" || instr.opcode == "write" || instr.opcode == "cwrite") {
			outfile << instr.opcode + " " + instr.leftOperands[0] << endl;
		}
		else if (instr.opcode == "read" || instr.opcode == "cread") {
			outfile << instr.opcode + " => " + instr.rightOperands[0] << endl;
		}
		else if (instr.opcode == "br") {
			outfile << instr.opcode + " -> " + instr.rightOperands[0] << endl;
		}
		else if (instr.opcode == "cbr") {
			outfile << instr.opcode + " " + instr.leftOperands[0] + " -> " + instr.rightOperands[0] + ", " + instr.rightOperands[1] << endl;
		}
		else if (instr.opcode == "not" || instr.opcode == "loadI" || instr.opcode == "load"
				|| instr.opcode == "cload" || instr.opcode == "store" || instr.opcode == "cstore" || instr.opcode == "i2i"
				|| instr.opcode == "c2c" || instr.opcode == "i2c" || instr.opcode == "c2i")
		{
			outfile << instr.opcode + " " + instr.leftOperands[0] + " => " + instr.rightOperands[0] << endl;
		}
		else if (instr.opcode == "storeAI" || instr.opcode == "storeAO" || instr.opcode == "cstoreAI" || instr.opcode == "cstoreAO") {
			outfile << instr.opcode + " " + instr.leftOperands[0] + " => " + instr.rightOperands[0] + ", " + instr.rightOperands[1] << endl;
		}
		else {
			outfile << instr.opcode + " " + instr.leftOperands[0] + ", " + instr.leftOperands[1] + " => " + instr.rightOperands[0] << endl;
		}
	}
  outfile.close();
}

void get_leader_and_last( vector<instruction> instructions, vector<int> &leader, vector<int> &last) {
	leader.push_back(1);
	for (auto instr : instructions) {
		if (instr.opcode == "br" || instr.opcode == "cbr") {
      bool find=false;
      for (int lead: leader){
        if (lead==label_to_line_num[instr.rightOperands[0]]){
          find=true;
        }
      }
      if (!find) {
        leader.push_back(label_to_line_num[instr.rightOperands[0]]);
      }

      find=false;
      for (int lead: leader){
        if (lead==label_to_line_num[instr.rightOperands[1]]){
          find=true;
        }
      }
      if (!find) {
        leader.push_back(label_to_line_num[instr.rightOperands[1]]);
      }
		}
	}

  int total_line_number = instructions.size();
	for (int cur_line: leader) {
    bool find=false;
    for (int lead: leader){
      if (lead==cur_line + 1){
        find=true;
      }
    }

		while (cur_line <= total_line_number && !find) {
			cur_line++;

      find=false;
      for (int lead: leader){
        if (lead==cur_line + 1){
          find=true;
        }
      }
		}
		last.push_back(cur_line);
	}
}

bool is_power_of_two(int x)
{
    return (x & (x - 1)) == 0;
}

void lvn(vector<int> leader, vector<int> last, vector<instruction> &instructions) {
	int num_of_blocks = leader.size();
	for (int i = 0; i < num_of_blocks; i++) {
		int begin = leader[i] - 1;
		int end = last[i] - 1;

		unordered_map <string, int> def2vn;
		unordered_map <string, int> oprend2vn;
		unordered_map <int, string> vn2operand;
		int new_value_number = 0;

		for (int j = begin; j <= end; j++) {
      if (instructions[j].opcode == "halt"){
        break;
      }
			else if (instructions[j].opcode == "nop" || instructions[j].opcode == "not" || instructions[j].opcode == "store"
				|| instructions[j].opcode == "storeAI" || instructions[j].opcode == "storeAO" || instructions[j].opcode == "cstore"
				|| instructions[j].opcode == "cstoreAI" || instructions[j].opcode == "cstoreAO"  || instructions[j].opcode == "i2i"
				|| instructions[j].opcode == "c2c" || instructions[j].opcode == "i2c" || instructions[j].opcode == "c2i"
				|| instructions[j].opcode == "br" || instructions[j].opcode == "cbr" || instructions[j].opcode == "halt"
				|| instructions[j].opcode == "read" || instructions[j].opcode ==  "cread" || instructions[j].opcode == "output"
				|| instructions[j].opcode == "coutput" || instructions[j].opcode == "write" || instructions[j].opcode == "cwrite"
				|| instructions[j].opcode == "loadI" || instructions[j].opcode == "load" || instructions[j].opcode ==  "cload") {
				continue;
			}
			else {
				// if (instructions[j].opcode == "multI") {
				// 	if (is_power_of_two(stoi(instructions[j].leftOperands[1]))) {
				// 		double tmp_d = sqrt(stoi(instructions[j].leftOperands[1]));
				// 		int tmp = tmp_d;
				// 		instruction instr;
				// 		instr.opcode = "lshiftI";
				// 		instr.leftOperands.push_back(instructions[j].leftOperands[0]);
				// 		instr.leftOperands.push_back(to_string(tmp));
				// 		instr.rightOperands.push_back(instructions[j].rightOperands[0]);
				// 		instructions[j] = instr;
				// 	}
				// }
				if (oprend2vn.find(instructions[j].leftOperands[0]) == oprend2vn.end()) {
					oprend2vn[instructions[j].leftOperands[0]] = new_value_number;
					new_value_number ++;
				}
				if (oprend2vn.find(instructions[j].leftOperands[1]) == oprend2vn.end()) {
					oprend2vn[instructions[j].leftOperands[1]] = new_value_number;
					new_value_number ++;
				}

				string expr = to_string(oprend2vn[instructions[j].leftOperands[0]]) + instructions[j].opcode + to_string(oprend2vn[instructions[j].leftOperands[1]]);
				if (def2vn.find(expr) != def2vn.end()) {
					if (oprend2vn[vn2operand[def2vn[expr]]] == def2vn[expr]) {
						instruction instr;
						instr.opcode = "i2i";
						instr.leftOperands.push_back(vn2operand[def2vn[expr]]);
						instr.rightOperands.push_back(instructions[j].rightOperands[0]);
						instructions[j] = instr;
					}
					oprend2vn[instructions[j].rightOperands[0]] = def2vn[expr];
				}
				else {
					oprend2vn[instructions[j].rightOperands[0]] = new_value_number;
					def2vn[expr] = new_value_number;
					vn2operand[new_value_number] = instructions[j].rightOperands[0];
					new_value_number++;
				}
			}
		}

	}
}

void get_largest_reg_and_label(vector<instruction> instructions, int &largest_reg, int &largest_label) {
	for (auto instr : instructions) {
		if (instr.label != "") {
			int label_value = stoi(instr.label.substr(1, instr.label.length() - 1));
			if (label_value > largest_label) {
				largest_label = label_value;
			}
		}
		if (instr.rightOperands.size() != 0) {
			for (auto operend : instr.rightOperands) {
				if (operend[0] != 'r') {
					continue;
				}
				int register_value = stoi(operend.substr(1, operend.length() -  1));
				if (register_value > largest_reg) {
					largest_reg = register_value;
				}
			}
		}
	}
}


void lu(vector<int> leader, vector<int> last,vector<instruction> &instructions, int largest_reg, int largest_label)
{
	vector<instruction> new_instructions;

	int num_of_blocks = leader.size();
	for (int i = 0; i < num_of_blocks; i++) {
		int begin = leader[i] - 1;
		int end = last[i] - 1;

		if (instructions[end - 1].opcode == "halt") {
			for (int k = begin; k <= end - 1; k++) {
				new_instructions.push_back(instructions[k]);
			}
			instructions=new_instructions;
			return;
		}
		if (instructions[begin].label != "" && instructions[end].opcode == "cbr" &&
     instructions[begin].label == instructions[end].rightOperands[0] && instructions[end - 2].opcode == "addI") {
				instruction instr_nop;
				instr_nop.opcode = "nop";
				instr_nop.label = instructions[begin].label;
				new_instructions.push_back(instr_nop);

				instruction instr_sub;
				instr_sub.opcode = "sub";
				instr_sub.leftOperands.push_back(instructions[end - 1].leftOperands[1]);
				instr_sub.leftOperands.push_back(instructions[end - 1].leftOperands[0]);
        largest_reg++;
				instr_sub.rightOperands.push_back("r" + to_string(largest_reg));
				new_instructions.push_back(instr_sub);


				instruction instr_rshiftI;
				instr_rshiftI.opcode = "rshiftI";
				instr_rshiftI.leftOperands.push_back("r" + to_string(largest_reg));
				instr_rshiftI.leftOperands.push_back("2");
				instr_rshiftI.rightOperands.push_back("r" + to_string(largest_reg));
				new_instructions.push_back(instr_rshiftI);

				instruction instr_lshiftI;
				instr_lshiftI.opcode = "lshiftI";
				instr_lshiftI.leftOperands.push_back("r" + to_string(largest_reg));
				instr_lshiftI.leftOperands.push_back("2");
				instr_lshiftI.rightOperands.push_back("r" + to_string(largest_reg));
				new_instructions.push_back(instr_lshiftI);


				instruction instr_add;
				instr_add.opcode = "add";
				instr_add.leftOperands.push_back(instructions[end - 1].leftOperands[0]);
				instr_add.leftOperands.push_back("r" + to_string(largest_reg));
				largest_reg++;
				instr_add.rightOperands.push_back("r" + to_string(largest_reg));
				new_instructions.push_back(instr_add);


				instruction instr_cbr;
				instr_cbr.opcode = "cbr";
				instr_cbr.leftOperands.push_back("r" + to_string(largest_reg));
				largest_label++;
				string largest_label_backup_tag_1 = "L" + to_string(largest_label);
				instr_cbr.rightOperands.push_back(largest_label_backup_tag_1);
				largest_label++;
				string largest_label_backup_tag_2 = "L" + to_string(largest_label);
				instr_cbr.rightOperands.push_back(largest_label_backup_tag_2);
				new_instructions.push_back(instr_cbr);

				instruction instr_nop_2;
				instr_nop_2.opcode = "nop";
				instr_nop_2.label = largest_label_backup_tag_1;
				new_instructions.push_back(instr_nop_2);

				for (int cnt = 1; cnt <= 4; cnt++) {
					for (int j = begin + 1; j <= end - 2; j++) {
						new_instructions.push_back(instructions[j]);
					}
				}

				instruction instr_cmp_LE;
				instr_cmp_LE.opcode = "cmp_LE";
				instr_cmp_LE.leftOperands.push_back(instructions[end - 1].leftOperands[0]);
				instr_cmp_LE.leftOperands.push_back("r" + to_string(largest_reg));
				instr_cmp_LE.rightOperands.push_back(instructions[end].leftOperands[0]);
				new_instructions.push_back(instr_cmp_LE);

				instruction instr_cbr_2;
				instr_cbr_2.opcode = "cbr";
				instr_cbr_2.leftOperands.push_back(instructions[end].leftOperands[0]);
				instr_cbr_2.rightOperands.push_back(largest_label_backup_tag_1);
				instr_cbr_2.rightOperands.push_back(largest_label_backup_tag_2);
				new_instructions.push_back(instr_cbr_2);

        instruction instr_nop_3;
				instr_nop_3.opcode = "nop";
				instr_nop_3.label = largest_label_backup_tag_2;
				new_instructions.push_back(instr_nop_3);

				new_instructions.push_back(instructions[end - 1]);

				instruction instr_cbr_3;
				instr_cbr_3.opcode = "cbr";
				instr_cbr_3.leftOperands.push_back(instructions[end].leftOperands[0]);
				largest_label++;
				string largest_label_backup_tag_3 = "L" + to_string(largest_label);
				instr_cbr_3.rightOperands.push_back(largest_label_backup_tag_3);
				instr_cbr_3.rightOperands.push_back(instructions[end].rightOperands[1]);
				new_instructions.push_back(instr_cbr_3);

        instruction instr_nop_4;
				instr_nop_4.opcode = "nop";
				instr_nop_4.label = largest_label_backup_tag_3;
				new_instructions.push_back(instr_nop_4);

				for (int j = begin + 1; j <= end - 2; j++) {
					new_instructions.push_back(instructions[j]);
				}

				new_instructions.push_back(instructions[end - 1]);
				new_instructions.push_back(instr_cbr_3);
		}
		else {
			for (int j = begin; j <= end; j++) {
				new_instructions.push_back(instructions[j]);
			}
			continue;
		}
	}
}

void update_label_to_line_num(vector<instruction> &instructions, unordered_map<string, int> &label_to_line_num) {
	int line_number = 1;
	for (auto instr : instructions) {
		instr.line_number = line_number;
		line_number ++;
		if (instr.label != "") {
			label_to_line_num[instr.label] = instr.line_number;
		}
	}
}


int main(int argc, char** argv) {
	string runType;
	string runType2;
	if (argc < 3 || argc > 4) {
		cout << "argc < 3 or argc > 4" << endl;
		return 0;
	}

	runType = argv[1];
	if (argc == 3){
    vector<instruction> instructions;
    input_parse(argv[2], instructions);
    vector<int> leader;
    vector<int> last;
    get_leader_and_last(instructions, leader, last);
    
		if (runType == "v") {
  		lvn(leader, last, instructions);
  		output_reduction(instructions);
		}
		else if (runType == "u") {
			int largest_reg = -1;
			int largest_label = -1;
			get_largest_reg_and_label(instructions, largest_reg, largest_label);
			sort(leader.begin(), leader.end());
			sort(last.begin(), last.end());
			lu(leader, last, instructions, largest_reg, largest_label);
			output_reduction(instructions);
		}
		else {
			cout << "wrong runType. If 3 args, then must be v or u" << endl;
			return 0;
		}
	}
	else if (argc == 4) {
		runType2=argv[2];

		if ( (runType2=="v" && runType=="u" ) || (runType2=="u" && runType=="v" ) ){
      vector<instruction> instructions;
  		input_parse(argv[3], instructions);
  		vector<int> leader;
  		vector<int> last;
  		get_leader_and_last(instructions, leader, last);
  		lvn(leader, last, instructions);

  		update_label_to_line_num(instructions, label_to_line_num);

  		vector<int> leader2;
  		vector<int> last2;
  		get_leader_and_last(instructions, leader2, last2);
  		int largest_reg = -1;
  		int largest_label = -1;
  		get_largest_reg_and_label(instructions, largest_reg, largest_label);
  		sort(leader2.begin(), leader2.end());
  		sort(last2.begin(), last2.end());
  		lu(leader2, last2, instructions, largest_reg, largest_label);
  		output_reduction(instructions);
		}

		else{
			cout << "wrong runType. If 4 args, then must be v,  u or u,  v" << endl;
			return 0;
		}
  }
	return 0;
}