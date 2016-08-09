#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <map>
#include <stdio.h>

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


class Employee
{
  public:
    void setID(string ID);
    void setName(string name);
    void setPosition(string position);
    void setDepartment(string department);
    void setDoB(string DoB);
    void setSalary(string salary);

    string getID(void);
    string getName(void);
    string getPosition(void);
    string getDepartment(void);
    string getDoB(void);
    string getSalary(void);

    static map<string, string> nameSorted;
    static map<string, string> idSorted;

    Employee();
    ~Employee();

  private:
    string myID;
    string myName;
    string myPosition;
    string myDepartment;
    string myDoB;
    string mySalary;

    
};

map<string, string> Employee::nameSorted;

map<string, string> Employee::idSorted;

Employee::Employee()
{
 cout << "Object is being created" << endl; 
}

Employee::~Employee(void)
{
  cout << "Object is being deleted" << endl;
}

void Employee::setID(string ID)
{
  myID = ID;
}

void Employee::setName(string name)
{
  myName = name;
}

void Employee::setPosition(string position)
{
  myPosition = position;
}

void Employee::setDepartment(string department)
{
  myDepartment = department;
}

void Employee::setDoB(string DoB)
{
  myDoB = DoB;
}

void Employee::setSalary(string salary)
{
  mySalary = salary;
}


string Employee::getID( void )
{
  return myID;
}

string Employee::getName( void )
{
  return myName;
}

string Employee::getPosition( void )
{
  return myPosition;
}

string Employee::getDepartment( void )
{
  return myDepartment;
}

string Employee::getDoB( void )
{
  return myDoB;
}

string Employee::getSalary( void )
{
  return mySalary;
}




int main () {
  string line1, line2;
  int i = 1, j=0;
  int numberOfRecords = 0;
  ifstream myInputFile ("emp.txt");
  ofstream myOutputFileBinary;
  myOutputFileBinary.open("emp2binary.txt",ios::binary);
  string ID, Name, Position, Department, DoB, Salary;
  int k = 0;
  
  if(myInputFile.is_open())
  {
    while(getline (myInputFile,line1))
    {
      numberOfRecords++;
    }
    myInputFile.close();
  }

  Employee myEmployees[numberOfRecords];
  ifstream myInputFileAgain ("emp.txt");

  if (myInputFileAgain.is_open())
  {
    while ( getline (myInputFileAgain,line2) )
    {
    	std::string s = line2;
		  std::string delimiter = ":";


  		size_t pos = 0;
  		std::string token;

  		
  		while ((pos = s.find(delimiter)) != std::string::npos) {
      		token = s.substr(0, pos);
      		trim(token);
      		if(i==1){
            myEmployees[j].setID(token);
      		}else if(i==2){
            myEmployees[j].setName(token);
          }else if(i==3){
            myEmployees[j].setPosition(token);
          }else if(i==4){
            myEmployees[j].setDepartment(token);
          }else if(i==5){
            myEmployees[j].setDoB(token);
      		}
      		//std::cout << token << std::endl;
      		s.erase(0, pos + delimiter.length());
      		i++;
  		}
  		trim(s);
      myEmployees[j].setSalary(s);
      Employee::nameSorted.insert(pair<string,string>(myEmployees[j].getName(), myEmployees[j].getID()));
      Employee::idSorted.insert(pair<string,string>(myEmployees[j].getID(), myEmployees[j].getName()));
  		i=1;
      j++;
        
    }
    myInputFileAgain.close();

    
    

    int l;
    int recordNumber;
    k = 0;
    
    for(map<string, string>::iterator iter=Employee::nameSorted.begin(); 
                    iter != Employee::nameSorted.end(); iter++)  {
        for(l=0; l<numberOfRecords;l++)
        {
          if(myEmployees[l].getName() == iter->first)
          {
            recordNumber = l;
          }
        }
        
        myOutputFileBinary.write((char*)&myEmployees[recordNumber], sizeof(Employee));
    }

    myOutputFileBinary.close();

  }

  Employee myBinaryEmployee[numberOfRecords];

  ifstream createdBinaryFile("emp2binary.txt",ios::binary);

  for(k = 0; k < numberOfRecords; k++){
    createdBinaryFile.read((char*)&myBinaryEmployee[k],sizeof(Employee));
  }
  createdBinaryFile.seekg(0);
  createdBinaryFile.close();

  for(k = 0; k < numberOfRecords; k++){
    ID = myBinaryEmployee[k].getID();
    Name = myBinaryEmployee[k].getName();
    Position = myBinaryEmployee[k].getPosition();
    Department = myBinaryEmployee[k].getDepartment();
    DoB = myBinaryEmployee[k].getDoB();
    Salary = myBinaryEmployee[k].getSalary();
    cout << "Record number: " << k+1 << "\n" << endl;
    cout << "ID: " << ID << "\n" << endl;
    cout << "Name: " << Name << "\n" << endl;
    cout << "Position: " << Position << "\n" << endl;
    cout << "Department: " << Department << "\n" << endl;
    cout << "DoB: " << DoB << "\n" << endl;
    cout << "Salary: " << Salary << "\n\n" << endl;
  }

}