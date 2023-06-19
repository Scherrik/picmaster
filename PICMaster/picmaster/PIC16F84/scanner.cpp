#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;
int inst[1000];

int interpreter()
{
  string filename = "C:\Users\Erik\source\repos\picmaster\TestProg_PicSim_20230413\TPicSim3.LST";
  ifstream input(filename);
 
  if (!input)
  {
    cerr << "Datei beim Oeffnen der Datei " << filename << "\n";
    return 1;
  }
  
  string line;
  int prog_counter = 0;
  cout << "Interpreter:" << endl;
  while (getline(input, line))
  {
    if(line[0] != ' '){
        string instruction_str = line.substr(5,4);
        cout << prog_counter << ": " << instruction_str << endl;
        unsigned int instruction = stoul(instruction_str, nullptr, 16);
        inst[prog_counter]=instruction;
        prog_counter ++;
    }
  } 
  inst[prog_counter]=0x3FFF;
  return 0;
}