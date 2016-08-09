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

