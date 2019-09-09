#include <iostream>
#include <sstream>
#include <fstream>

#include "HashTable.hpp"
#include "HeapPriorityQueue.hpp"

using namespace std;



void read_part_1_2(ifstream &inputfile, ofstream &outputfile) {
cout << "GG" << endl;
	HashTable<int> table(2);

	string lines;
	int counter;
	getline(inputfile, lines);
	stringstream convert(lines);
	convert >> counter;

	for (int i = 0; i < counter; i++) {
		char operation;
		string key;
		int value;
		string return_key;
		convert.clear();

		string str;
		getline(inputfile, str);
		convert.str(str);
		convert >> operation >> key >> value;

		if (i != 0) {
			outputfile << '\n';
		}

		int temp;
		bool is_out = false;

		switch(operation) {
			case 'p':
				try {
					temp = table.put(key, value);
				} catch (NotImplementedException& exception) {
					outputfile << "null";
					is_out = true;
				} 
				if (!is_out) {
					outputfile << temp;
				}
				break;

			case 'g':
				try {
					temp = table.get(key);
				} catch (NotImplementedException& exception) {
					outputfile << "null";
					is_out = true;
				}
				if (!is_out) {
					outputfile << temp;
				}
				break;

			case 'r':
				try {
					temp = table.replace(key, value);
				} catch (NotImplementedException& exception) {
					outputfile << "null";
					is_out = true;
				}
				if (!is_out) {
					outputfile << temp;
				}
				break;

			case 'd':
				try {
					temp = table.remove(key);
				} catch (NotImplementedException& exception) {
					outputfile << "null";
					is_out = true;
				}
				if (!is_out) {
					outputfile << temp;
				}
				break;

			case 's':
				outputfile << table.size();
				break;

			case 'c':
				if (table.contains(key)) {
					outputfile << '1';
				} else {
					outputfile << '0';
				}
				break;

			case 'm':
			convert.clear();
				convert.str(str);
				int new_value = -99;
				convert >> operation >> new_value;
				cout << new_value;
				outputfile << table.getCollision(new_value);
				break;
		}
	}

}





void read_part_3(ifstream &inputfile, ofstream &outputfile) {
	
	HeapPriorityQueue<int> queue(100);

	string lines;
	int counter;
	getline(inputfile, lines);
	stringstream convert(lines);
	convert >> counter;

	bool is_out = false;

	for (int i = 0; i < counter; i++) {
		char operation;
		int value;
		convert.clear();

		string str;
		getline(inputfile, str);
		convert.str(str);
		convert >> operation >> value;

		switch(operation) {
			case 'i':
				queue.insert(value);
				break;

			case 'm':
				if (is_out) {
					outputfile << '\n';
				}
				if (queue.empty()) {
					outputfile << "empty";
				} else {
					outputfile << queue.min();
				}
				is_out = true;
				break;

			case 'r':
				if (queue.empty()) {
					if (is_out) {
						outputfile << '\n';
					}
					is_out = true;
					outputfile << "empty";
				} else {
					queue.removeMin();
				}
				break;

			case 's':
				if (queue.empty()) {
					if (is_out) {
						outputfile << '\n';
					}
					is_out = true;
					outputfile << "empty";
				} else {
					int total_size = queue.size();
					for (int i = 0; i < total_size; i++) {
						outputfile << '\n';
						outputfile << queue.min();
						try {
							queue.removeMin();
						} catch (NotImplementedException& exception) {
							cout << "Deleted finished" << endl;
						}
						is_out = true;
					}
				}
				break;
		}
	}
}



int main(int argc, char *argv[]) {
	
	//Read in the test case
    
	ifstream inputfile;
    ofstream outputfile;

    inputfile.open(argv[1]);
    outputfile.open(argv[2]);

    string str;

    getline(inputfile, str);
    int part;
    stringstream convert(str);
    convert >> part;

    switch(part) {
        case 1: case 2:
            read_part_1_2(inputfile, outputfile);
            break;
        case 3:
            read_part_3(inputfile, outputfile);
            break;
    }

	inputfile.close();
	outputfile.close();

	return 0;
}

