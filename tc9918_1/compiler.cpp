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
string branchDest[500], tempReg = "10111"; //temp reg = 23
string bin;
char BD;

void binary(int number) {
	int remain;

	if (number == 0)
	{
		bin.append("0");
		return;
	}

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
	int i = 0;

	//cout << "\nA:" << label; 
	while (i < 500)
	{
		//cout << i << endl;
		if (label.compare(branchDest[i]) == 0)
		{
			//cout << " b:" << i << "c:" << branchDest[i] << endl;
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
	output.open ("simpleLoopBMC.txt");
	printf("Opened file\n");

	if (!program)
	{
		printf("%s is not a recognised program!\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		getline(program, line);
		if (!program)
		{
			break;
		}
		

		//take out labels
		position = line.find(":");
		if(position < 100)
		{
			//cout << position << "\n";
			branchDest[lineNumber] = line.substr(0, line.find(" ")-1);
			//cout << branchDest[lineNumber];
			line = line.substr(position+2);
			//cout << " " << lineNumber << endl;

		}
		bin = "";
		command = line.substr(0, line.find(" "));
		if (command == "add")
		{
			if ( line.find("#") < 1000)
			{
				//Mov constant to r13
				output << "00101" << tempReg;
				// constant
				bin = "";
				length = (line.find_last_of("\n")-line.find_last_of("#"))-1;
				sop = line.substr(line.find_last_of("#")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 22)
				{
					output << "0";
					length++;
				}
				output << bin << endl;

				output << "00000";
				bin = "";
				length = (line.find_first_of(",")-line.find_first_of("r"))-1;
				sop = line.substr(line.find_first_of("r")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
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
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin;

				// constant, ie r13
				output << tempReg << "000000000000" << endl;
			} else { // register + register
				output << "00000";
				bin = "";
				length = (line.find_first_of(",")-line.find_first_of("r"))-1;
				sop = line.substr(line.find_first_of("r")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin;

				// second reg
				bin = "";
				length = (line.find_last_of(",")-(line.find_first_of(",")+2))-1;
				sop = line.substr((line.find_first_of(",")+2)+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin;

				//third reg
				bin = "";
				length = (line.find_last_of("\n")-line.find_last_of("r"))-1;
				sop = line.substr(line.find_last_of("r")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin << "000000000000" << endl;
			}

		} else if (command == "sub")
		{
			if ( line.find("#") < 1000)
			{
				//Mov constant to r13
				output << "00101" << tempReg;
				// constant
				bin = "";
				length = (line.find_last_of("\n")-line.find_last_of("#"))-1;
				sop = line.substr(line.find_last_of("#")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 22)
				{
					output << "0";
					length++;
				}
				output << bin << endl;

				output << "00001";
				bin = "";
				length = (line.find_first_of(",")-line.find_first_of("r"))-1;
				sop = line.substr(line.find_first_of("r")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
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
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin;

				// constant, ie r13
				output << tempReg << "000000000000" << endl;
			} else { // register + register
				output << "00001";
				bin = "";
				length = (line.find_first_of(",")-line.find_first_of("r"))-1;
				sop = line.substr(line.find_first_of("r")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin;

				// second reg
				bin = "";
				length = (line.find_last_of(",")-(line.find_first_of(",")+2))-1;
				sop = line.substr((line.find_first_of(",")+2)+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin;

				//third reg
				bin = "";
				length = (line.find_last_of("\n")-line.find_last_of("r"))-1;
				sop = line.substr(line.find_last_of("r")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin << "000000000000" << endl;
			}
				//break;
		} else if (command == "mul")
		{
			if ( line.find("#") < 1000)
			{
				//Mov constant to r13
				output << "00101" << tempReg;
				// constant
				bin = "";
				length = (line.find_last_of("\n")-line.find_last_of("#"))-1;
				sop = line.substr(line.find_last_of("#")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 22)
				{
					output << "0";
					length++;
				}
				output << bin << endl;

				output << "00010";
				bin = "";
				length = (line.find_first_of(",")-line.find_first_of("r"))-1;
				sop = line.substr(line.find_first_of("r")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
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
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin;

				// constant, ie r13
				output << tempReg << "000000000000" << endl;
			} else { // register + register
				output << "00010";
				bin = "";
				length = (line.find_first_of(",")-line.find_first_of("r"))-1;
				sop = line.substr(line.find_first_of("r")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin;

				// second reg
				bin = "";
				length = (line.find_last_of(",")-(line.find_first_of(",")+2))-1;
				sop = line.substr((line.find_first_of(",")+2)+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin;

				//third reg
				bin = "";
				length = (line.find_last_of("\n")-line.find_last_of("r"))-1;
				sop = line.substr(line.find_last_of("r")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin << "000000000000" << endl;
			}


		} else if (command == "div")
		{
			if ( line.find("#") < 1000)
			{
				//Mov constant to r13
				output << "00101" << tempReg;
				// constant
				bin = "";
				length = (line.find_last_of("\n")-line.find_last_of("#"))-1;
				sop = line.substr(line.find_last_of("#")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 22)
				{
					output << "0";
					length++;
				}
				output << bin << endl;

				output << "00011";
				bin = "";
				length = (line.find_first_of(",")-line.find_first_of("r"))-1;
				sop = line.substr(line.find_first_of("r")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
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
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin;

				// constant, ie r13
				output << tempReg << "000000000000" << endl;
			} else { // register + register
				output << "00011";
				bin = "";
				length = (line.find_first_of(",")-line.find_first_of("r"))-1;
				sop = line.substr(line.find_first_of("r")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin;

				// second reg
				bin = "";
				length = (line.find_last_of(",")-(line.find_first_of(",")+2))-1;
				sop = line.substr((line.find_first_of(",")+2)+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin;

				//third reg
				bin = "";
				length = (line.find_last_of("\n")-line.find_last_of("r"))-1;
				sop = line.substr(line.find_last_of("r")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin << "000000000000" << endl;
			}
		} else if (command == "mov" || command == "movle" || command == "movgt") 
		{
			output << "00101";
			bin = "";
			//cout << line << endl;
			length = (line.find_first_of(",")-line.find_first_of("r"))-1;
			sop = line.substr(line.find_first_of("r")+1, length);
			//cout << sop;
			cop = sop.c_str();
			binary(atoi(cop));
			length = bin.length();
			while (length < 5)
			{
				output << "0";
				length++;
			}
			//cout << " " << bin << endl;
			output << bin;

			// constant
			bin = "";
			length = (line.find_last_of("\n")-line.find_last_of("#"))-1;
			sop = line.substr(line.find_last_of("#")+1, length);
			//cout << sop;
			cop = sop.c_str();
			binary(atoi(cop));
			length = bin.length();
			while (length < 22)
			{
				output << "0";
				length++;
			}
			//cout << " " << bin << endl;
			output << bin << endl;


		} else if (command == "cmp")
		{
			//cout << line << "\n";

			if ( line.find("#") < 1000)
			{
				//Mov constant to r13
				output << "00101" << tempReg;
				// constant
				bin = "";
				length = (line.find_last_of("\n")-line.find_last_of("#"))-1;
				sop = line.substr(line.find_last_of("#")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 22)
				{
					output << "0";
					length++;
				}
				output << bin << endl;

				//CMP
				//reg 1
				output << "00100";
				bin = "";
				length = (line.find_first_of(",")-line.find_first_of("r"))-1;
				sop = line.substr(line.find_first_of("r")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin;

				// constant
				// constant, ie r13
				output << "00000000000000000"<< tempReg << endl;

			} else { //register

				// reg 1
				output << "00100";
				bin = "";
				length = (line.find_first_of(",")-line.find_first_of("r"))-1;
				sop = line.substr(line.find_first_of("r")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin;

				// reg2
				bin = "";
				length = (line.find_last_of("\n")-line.find_last_of("r"))-1;
				sop = line.substr(line.find_last_of("r")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin << "00000000000000000" << endl;
			}

		} else if (command == "ldr") //opcode 4 Rd 4 Maddress 20
		{
			// append a \n
			if (line.find("\n") > 1000)
			{
				line.append("\n");
			}

			// with offset
			if (line.find("[") < 1000) 
			{ // register and offset
				//cout << line << "\n";
				if(line.find("#") < 1000)
				{ // ldr r3, [r15, #4]
					// mov
					output << "0010101111";
					bin = "";
					length = (line.find_last_of("]")-line.find_last_of("#"))-1;
					sop = line.substr(line.find_last_of("#")+1, length);
					cop = sop.c_str();
					binary(atoi(cop));
					length = bin.length();
					while (length < 22)
					{
						output << "0";
						length++;
					}
					output << bin << endl;

					// add
					output << "0000001111";
					bin = "";
					length = (line.find_last_of(",")-line.find_last_of("r"))-1;
					sop = line.substr(line.find_last_of("r")+1, length);
					cop = sop.c_str();
					binary(atoi(cop));
					length = bin.length();
					while (length < 5)
					{
						output << "0";
						length++;
					}
					output << bin << "01111000000000000" << endl;

					// ldr
					output << "00110";
					bin = "";
					length = (line.find_first_of(",")-line.find_first_of("r"))-1;
					sop = line.substr(line.find_first_of("r")+1, length);
					cop = sop.c_str();
					binary(atoi(cop));
					length = bin.length();
					while (length < 5)
					{
						output << "0";
						length++;
					}
					output << bin << "0111100000000000000000" << endl;


				} else { // ldr r3, [r15, r12]
					// add
					output << "0000001111";
					bin = "";
					length = (line.find_last_of(",")-(line.find_first_of("[")+1)-1);
					sop = line.substr(line.find_first_of("[")+2, length);
					cop = sop.c_str();
					binary(atoi(cop));
					length = bin.length();
					while (length < 5)
					{
						output << "0";
						length++;
					}
					output << bin;

					bin = "";
					length = (line.find_last_of("]")-line.find_last_of("r")-1);
					sop = line.substr(line.find_last_of("r")+1, length);
					cop = sop.c_str();
					binary(atoi(cop));
					length = bin.length();
					while (length < 5)
					{
						output << "0";
						length++;
					}
					output << bin << "000000000000" << endl;

					//ldr
					output << "00110";
					bin = "";
					length = (line.find_first_of(",")-line.find_first_of("r"))-1;
					sop = line.substr(line.find_first_of("r")+1, length);
					//cout << sop << endl;
					cop = sop.c_str();
					binary(atoi(cop));
					length = bin.length();
					while (length < 5)
					{
						output << "0";
						length++;
					}
					output << bin << "0111100000000000000000" << endl;
				}

			} else { // address
				// mov address to register
				output << "0010101111";
				bin = "";
				binary(lookupBranchDest(line.substr(line.find_last_of("\n")-line.find_last_of(","))));
				length = bin.length();
				while (length < 22)
				{
					output << "0";
					length++;
				}
				output << bin << endl;

				// ldr register
				output << "00110";
				bin = "";
				length = (line.find_last_of(",")-line.find_last_of("r"))-1;
				sop = line.substr(line.find_last_of("r")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin;
				
				output << "0111100000000000000000" << endl;
			}
		}else if (command == "str" || command == "strgt") //opcode 4 Rd 4 Maddress 20
		{
			// append a \n
			if (line.find("\n") > 1000)
			{
				line.append("\n");
			}

			// with offset
			if (line.find("[") < 1000) 
			{ // register and offset
				//cout << line << "\n";
				if(line.find("#") < 1000)
				{ // ldr r3, [r15, #4]
					// mov
					output << "0010101111";
					bin = "";
					length = (line.find_last_of("]")-line.find_last_of("#"))-1;
					sop = line.substr(line.find_last_of("#")+1, length);
					cop = sop.c_str();
					binary(atoi(cop));
					length = bin.length();
					while (length < 22)
					{
						output << "0";
						length++;
					}
					output << bin << endl;

					// add
					output << "0000001111";
					bin = "";
					length = (line.find_last_of(",")-line.find_last_of("r"))-1;
					sop = line.substr(line.find_last_of("r")+1, length);
					cop = sop.c_str();
					binary(atoi(cop));
					length = bin.length();
					while (length < 5)
					{
						output << "0";
						length++;
					}
					output << bin << "01111000000000000" << endl;

					// ldr
					output << "00111";
					bin = "";
					length = (line.find_first_of(",")-line.find_first_of("r"))-1;
					sop = line.substr(line.find_first_of("r")+1, length);
					cop = sop.c_str();
					binary(atoi(cop));
					length = bin.length();
					while (length < 5)
					{
						output << "0";
						length++;
					}
					output << bin << "0111100000000000000000" << endl;


				} else { // ldr r3, [r15, r12]
					// add
					output << "0000001111";
					bin = "";
					length = (line.find_last_of(",")-(line.find_first_of("[")+1)-1);
					sop = line.substr(line.find_first_of("[")+2, length);
					cop = sop.c_str();
					binary(atoi(cop));
					length = bin.length();
					while (length < 5)
					{
						output << "0";
						length++;
					}
					output << bin;

					bin = "";
					length = (line.find_last_of("]")-line.find_last_of("r")-1);
					sop = line.substr(line.find_last_of("r")+1, length);
					cop = sop.c_str();
					binary(atoi(cop));
					length = bin.length();
					while (length < 0)
					{
						output << "0";
						length++;
					}
					output << bin << "000000000000" << endl;

					//ldr
					output << "00111";
					bin = "";
					length = (line.find_first_of(",")-line.find_first_of("r"))-1;
					sop = line.substr(line.find_first_of("r")+1, length);
					//cout << sop << endl;
					cop = sop.c_str();
					binary(atoi(cop));
					length = bin.length();
					while (length < 5)
					{
						output << "0";
						length++;
					}
					output << bin << "0111100000000000000000" << endl;
				}

			} else { // address
				// mov address to register
				output << "0010101111";
				bin = "";
				binary(lookupBranchDest(line.substr(line.find_last_of("\n")-line.find_last_of(","))));
				length = bin.length();
				while (length < 22)
				{
					output << "0";
					length++;
				}
				output << bin << endl;

				// str register
				output << "00111";
				bin = "";
				length = (line.find_last_of(",")-line.find_last_of("r"))-1;
				sop = line.substr(line.find_last_of("r")+1, length);
				//cout << sop << endl;
				cop = sop.c_str();
				binary(atoi(cop));
				length = bin.length();
				while (length < 5)
				{
					output << "0";
					length++;
				}
				output << bin;
				
				output << "0111100000000000000000" << endl;
			}
		}else if (command == "b"){
			// append a \n
			if (line.find("\n") > 1000)
			{
				line.append("\n");
			}

			output << "01000";
			bin = "";
			length = (line.find_first_of("\n")-line.find_first_of("r"))-1;
			sop = line.substr(line.find_first_of("r")+1, length);
			//cout << sop << endl;
			cop = sop.c_str();
			binary(atoi(cop));
			length = bin.length();
			while (length < 5)
			{
				output << "0";
				length++;
			}
			output << bin;
			output << "0000000000000000000000" << endl;
		} else if (command == "blt" || command == "ble" || command == "bl"){
			// append a \n
			if (line.find("\n") > 1000)
			{
				line.append("\n");
			}
			//mov adress in to tmp reg
			output << "00101" << tempReg;
			bin = "";
			length = (line.find_first_of("\n")-line.find_first_of("."))-1;
			sop = line.substr(line.find_first_of(".")+1, length);
			//cout << sop << endl;
			//cop = lookupBranchDest(sop);
			//cout << cop << endl;
			binary(lookupBranchDest(sop));
			//cout << bin << endl;
			length = bin.length();
			while (length < 22)
			{
				output << "0";
				length++;
			}
			output << bin << endl;
			// branch to temp reg
			output << "01001" << tempReg << "0000000000000000000000" << endl;
		}else if (command == "blti"){
			// append a \n
			if (line.find("\n") > 1000)
			{
				line.append("\n");
			}
			//mov adress in to tmp reg
			output << "11001";
			bin = "";
			length = (line.find_first_of("\n")-line.find_first_of("."))-1;
			sop = line.substr(line.find_first_of(".")+1, length);
			//cout << sop << endl;
			//cop = lookupBranchDest(sop);
			//cout << cop << endl;
			binary(lookupBranchDest(sop));
			//cout << bin << endl;
			length = bin.length();
			while (length < 5)
			{
				output << "0";
				length++;
			}
			output << bin << "0000000000000000000000" << endl;
		}else if (command == "bgt" || command == "bge" || command == "bg"){
			// append a \n
			if (line.find("\n") > 1000)
			{
				line.append("\n");
			}
			//mov adress in to tmp reg
			output << "00101" << tempReg;
			bin = "";
			length = (line.find_first_of("\n")-line.find_first_of("."))-1;
			sop = line.substr(line.find_first_of(".")+1, length);
			//cout << sop << endl;
			//cop = lookupBranchDest(sop);
			//cout << cop << endl;
			binary(lookupBranchDest(sop));
			//cout << bin << endl;
			length = bin.length();
			while (length < 22)
			{
				output << "0";
				length++;
			}
			output << bin << endl;
			// branch to temp reg
			output << "01011" << tempReg << "0000000000000000000000" << endl;
		}else if (command == "bne"){
			// append a \n
			if (line.find("\n") > 1000)
			{
				line.append("\n");
			}
			//mov adress in to tmp reg
			output << "00101" << tempReg;
			bin = "";
			length = (line.find_first_of("\n")-line.find_first_of("."))-1;
			sop = line.substr(line.find_first_of(".")+1, length);
			//cout << sop << endl;
			//cop = lookupBranchDest(sop);
			//cout << cop << endl;
			binary(lookupBranchDest(sop));
			//cout << bin << endl;
			length = bin.length();
			while (length < 22)
			{
				output << "0";
				length++;
			}
			output << bin << endl;
			// branch to temp reg
			output << "01011" << tempReg << "0000000000000000000000" << endl;
			output << "01001" << tempReg << "0000000000000000000000" << endl;
		}else if (command == "end"){
			output << "01110000000000000000000000000000" << endl;
		} else {
			//cout << line << "\n";
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