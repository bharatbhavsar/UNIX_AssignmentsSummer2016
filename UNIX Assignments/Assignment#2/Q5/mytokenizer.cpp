#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

using namespace std;

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}


int main () {
  string line;
  int i = 1, j=1;
  ifstream myInputFile ("emp.txt");
  ofstream myOutputFile;
  myOutputFile.open("emp2.txt");
  if (myInputFile.is_open())
  {
    while ( getline (myInputFile,line) )
    {
    	std::string s = line;
		  std::string delimiter = ":";


  		size_t pos = 0;
  		std::string token;
  		myOutputFile << "Record number: " << j++ << "\n";
  		while ((pos = s.find(delimiter)) != std::string::npos) {
      		token = s.substr(0, pos);
      		trim(token);
      		if(i==1){
      			myOutputFile << "\tID: " << token << "\n";
      			
      		}else if(i==2){
      			myOutputFile << "\tName: " << token << "\n";
      			
      		}else if(i==3){
      			myOutputFile << "\tPosition: " << token << "\n";
      			
      		}else if(i==4){
      			myOutputFile << "\tDepartment: " << token << "\n";
      			
      		}else if(i==5){
      			myOutputFile << "\tDoB: " << token << "\n";
      			
      		}
      		//std::cout << token << std::endl;
      		s.erase(0, pos + delimiter.length());
      		i++;
  		}
  		trim(s);
  		myOutputFile << "\tSalary: " << s << "\n\n";
  		i=1;
        
    }
    myInputFile.close();
    myOutputFile.close();
  }
}