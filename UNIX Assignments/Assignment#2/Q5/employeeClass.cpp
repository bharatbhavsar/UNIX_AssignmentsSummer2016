#include <iostream>
#include <string>

class Employee
{
	public:
		void setID(string ID);
		void setName(string name);
		void setPosition(string position);
		void setDepartment(string department);
		void setDoB(string DoB);
		void setSalary(double salary);

		string getID( void );
		string getName( void );
		string getPosition( void );
		string getDepartment( void );
		string getDoB( void );
		int getSalary( void );

		Employee(string name);
		~Employee();

	private:
		string myID;
		string myName;
		string myPosition;
		string myDepartment;
		string myDoB;
		int mySalary;
};

Employee::Employee(string name)
{
	myName = name;
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

void Employee::setsalary(int salary)
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

int Employee::getSalary( void )
{
	return mysalary;
}
