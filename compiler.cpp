#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <bitset>
#include <cstdlib>

using namespace std;

fstream program;
ofstream output;
string branchDest[500];
string bin;
char BD;

void binary(int number) {
	int remain;

	if(number <= 1) {
		bin.append("1");
		return;
	}

	remain = number%2;
	binary(number >> 1); 
	if (remain == 1)
	{
		bin.append("1");
	} else {
		bin.append("0");
	}
}

int lookupBranchDest (string label)
{
	int i = 1;
	while (i < 500)
	{
		if (label.compare(branchDest[i]))
		{
			return i;
		}
		i++;
	}

	return 0;
}

int main (int argc, char *argv[])
{
	string line, command, tmp;
	int lineNumber = 1, length;
	string sop;
	stringstream str(sop);
	const char * cop = new char;
	size_t position;
	bitset<4> bits;

	printf("Opening file\n");
	program.open (argv[1], fstream::in | fstream::out | fstream::app);
	output.open ("output.txt");
	printf("Opened file\n");

	//line = malloc((sizeof(char)*32));
	//command = malloc((sizeof(char)*32));
	//tmp = malloc((sizeof(char)*32));

	if (!program)
	{
		printf("%s is not a recognised program!\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (1)//fscanf(program, "%[^\n]", line) != 0)
	{
		getline(program, line);
		if (!program)
		{
			break;
		}
		cout << line << "\n";

		//take out labels
		position = line.find(":");
		if(position < 100)
		{
			//cout << position << "\n";
			branchDest[lineNumber] = line.substr(0, line.find(" "));
			//cout << branchDest[lineNumber] << "\n";
			line = line.substr(position+2);
			//cout << line << "\n";
		}
		bin = "";
		command = line.substr(0, line.find(" "));
		if (command == "add")
		{
			output << "0000";
			length = (line.find_first_of(",")-line.find_first_of("r"))-1;
			sop = line.substr(line.find_first_of("r")+1, length);
			//cout << sop << endl;
			cop = sop.c_str();
			binary(atoi(cop));
			length = bin.length();
			while (length < 4)
			{
				output << "0";
				length++;
			}
			output << bin;

			// second reg
			bin = "";
			length = (line.find_last_of(",")-line.find_last_of("r"))-1;
			sop = line.substr(line.find_last_of("r")+1, length);
			//cout << sop << endl;
			cop = sop.c_str();
			binary(atoi(cop));
			length = bin.length();
			while (length < 4)
			{
				output << "0";
				length++;
			}
			output << bin << endl;

			// constant

		} else {
				//break;
		}
		//tmp = strchr(command, ':');
		//printf("%s", tmp);
		//fflush(stdout);
		// if (tmp != NULL)
		// {
		// 	branchDest[lineNumber] = command;
		// 	sscanf(line,  "%[^\n]", line);
		// }

		// printf("%s\n",line);

		// fscanf(program, "%[\n]", line);
		lineNumber++;
	}
	program.close();
	output.close();
	return 0;
}