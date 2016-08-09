#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <map>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h> 
#include <sstream>

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


class Person
{
  public:
    void setFirstName(string ID);
    void setLastName(string name);
    void setID(int position);
    
    string getFirstName(void);
    string getLastName(void);
    int getID(void);

    Person();
    
  private:
    int myID;
    string myFirstName;
    string myLastName;
    
};


Person::Person()
{
 
}

void Person::setID(int ID)
{
  myID = ID;
}

void Person::setFirstName(string fname)
{
  myFirstName = fname;
}

void Person::setLastName(string lname)
{
  myLastName = lname;
}

int Person::getID( void )
{
  return myID;
}

string Person::getFirstName( void )
{
  return myFirstName;
}

string Person::getLastName( void )
{
  return myLastName;
}

class Movie
{
  public:
    void setMovieTitle(string movieName);
    void setMovieID(int movieID);
    void setMovieYear(int movieYear);
    void setMovieDirector(int movieDirector);
    
    string getMovieTitle(void);
    int getMovieYear(void);
    int getMovieDirector(void);
    int getMovieID(void);

    Movie();
    
  private:
    int movieID;
    string movieTitle;
    int movieDirector;
    int movieYear;
};

Movie::Movie()
{

}

void Movie::setMovieTitle(string title)
{
  movieTitle = title;
}
void Movie::setMovieDirector(int director)
{
  movieDirector = director;
}
void Movie::setMovieYear(int year)
{
  movieYear = year;
}
void Movie::setMovieID(int id)
{
  movieID = id;
}

int Movie::getMovieID( void )
{
  return movieID;
}

int Movie::getMovieYear( void )
{
  return movieYear;
}

int Movie::getMovieDirector( void )
{
  return movieDirector;
}

string Movie::getMovieTitle( void )
{
  return movieTitle;
}

class Act_In
{
  public:
    void setActor(int act);
    void setMovie(int mov);
    
    int getActor(void);
    int getMovie(void);

    Act_In();
    
  private:
    int myActor;
    int myMovie;
    
};

Act_In::Act_In()
{

}

void Act_In::setActor(int act)
{
  myActor = act;
}

void Act_In::setMovie(int mov)
{
  myMovie = mov;
}

int Act_In::getMovie( void )
{
  return myActor;
}

int Act_In::getActor( void )
{
  return myMovie;
}

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   std::ofstream myOutputFile;
   myOutputFile.open("tableOutput.txt", std::ios_base::app);
   for(i=0; i<argc; i++){
   		string colName = azColName[i];
   		string value =  argv[i];
      	myOutputFile << colName << " : "<< value << "\n";
   }
   myOutputFile << "\n";
   myOutputFile.close();
   return 0;
}

int main (int argc, char* argv[]) {
	
	//First Part

	string line1, line2;
	int i = 1, j=0;
	int myInt;
	int numberOfPersonRecords = 0, numberOfMovieRecords = 0, numberOfActInRecords = 0;
	ifstream myInputFilePerson ("person.txt");
	ifstream myInputFileMovies ("movies.txt");
	ifstream myInputFileActIn ("acts_in.txt");
  
  	if(myInputFilePerson.is_open())
  	{
    	while(getline (myInputFilePerson,line1))
    	{
      		numberOfPersonRecords++;
    	}
    	myInputFilePerson.close();
  	}

  	if(myInputFileMovies.is_open())
  	{
    	while(getline (myInputFileMovies,line1))
    	{
      	numberOfMovieRecords++;
    	}
    	myInputFileMovies.close();
  	}

  	if(myInputFileActIn.is_open())
  	{
    	while(getline (myInputFileActIn,line1))
    	{
      		numberOfActInRecords++;
    	}
    	myInputFileActIn.close();
  	}

	Person myPerson[numberOfPersonRecords];
	Movie myMovies[numberOfMovieRecords];
	Act_In myActIn[numberOfActInRecords];

	ifstream myInputFilePersonAgain ("person.txt");
	ifstream myInputFileMoviesAgain ("movies.txt");
	ifstream myInputFileActInAgain ("acts_in.txt");

	cout << "Staring Part 1 ----->\n" << endl;

  	if (myInputFilePersonAgain.is_open())
  	{
    	while ( getline (myInputFilePersonAgain,line2) )
    	{
	    	std::string s = line2;
			std::string delimiter = "|";


	  		size_t pos = 0;
	  		std::string token;

	  		
	  		while ((pos = s.find(delimiter)) != std::string::npos) {
	      		token = s.substr(0, pos);
	      		trim(token);
	      		if(i==1){
	            	myPerson[j].setLastName(token);
	      		}else if(i==2){
	            	myPerson[j].setFirstName(token);
	          	}
	      		s.erase(0, pos + delimiter.length());
	      		i++;
	  		}
	  		trim(s);
	  		myInt = atoi(s.c_str());
	      	myPerson[j].setID(myInt);
	      	i=1;
	      	j++;
	        
	    }
    	myInputFilePersonAgain.close();
	}

	j=0;

	if (myInputFileMoviesAgain.is_open())
  	{
    	while ( getline (myInputFileMoviesAgain,line2) )
    	{
	    	std::string s = line2;
			std::string delimiter = "|";


	  		size_t pos = 0;
	  		std::string token;

	  		
	  		while ((pos = s.find(delimiter)) != std::string::npos) {
	      		token = s.substr(0, pos);
	      		trim(token);
	      		if(i==1){
	            	myMovies[j].setMovieTitle(token);
	      		}else if(i==2){
	      			myInt = atoi(token.c_str());
	            	myMovies[j].setMovieDirector(myInt);
	          	}else if(i==3){
	          		myInt = atoi(token.c_str());
	            	myMovies[j].setMovieYear(myInt);
	          	}
	     		s.erase(0, pos + delimiter.length());
	      		i++;
	  		}
	  		trim(s);
	  		myInt = atoi(s.c_str());
	      	myMovies[j].setMovieID(myInt);
	      	i=1;
	      	j++;
	        
	    }
	    myInputFileMoviesAgain.close();
	}

	j=0;

	if (myInputFileActInAgain.is_open())
  	{
    	while ( getline (myInputFileActInAgain,line2) )
    	{
	    	std::string s = line2;
			std::string delimiter = "|";


	  		size_t pos = 0;
	  		std::string token;

	  		
	  		while ((pos = s.find(delimiter)) != std::string::npos) {
	      		token = s.substr(0, pos);
	      		trim(token);
	      		if(i==1){
	      			myInt = atoi(token.c_str());
	            	myActIn[j].setActor(myInt);
	      		}
	     		s.erase(0, pos + delimiter.length());
	      		i++;
	  		}
	  		trim(s);
	  		myInt = atoi(s.c_str());
	      	myActIn[j].setMovie(myInt);
	      	i=1;
	      	j++;
	        
	    }
	    myInputFileActInAgain.close();
	}

	cout << "Person Records recovered:: " << "\n";
	for(int k = 0; k < numberOfPersonRecords; k++)
	{
		cout << "Record Number " << k+1 << "\n";
	    cout << "\tLast Name: " << myPerson[k].getLastName() << "\n";
	    cout << "\tFirst Name: " << myPerson[k].getFirstName() << "\n";
	    cout << "\tID: " << myPerson[k].getID() << "\n\n";
	}

	cout << "Movie Records recovered:: " << "\n";
	for(int k = 0; k < numberOfMovieRecords; k++)
	{
		cout << "Record Number " << k+1 << "\n";
	    cout << "\tMovie Title: " << myMovies[k].getMovieTitle() << "\n";
	    cout << "\tDirector ID: " << myMovies[k].getMovieDirector() << "\n";
	    cout << "\tYear: " << myMovies[k].getMovieYear() << "\n";
	    cout << "\tMovieID: " << myMovies[k].getMovieID() << "\n\n";
	}

	cout << "ActIn Records recovered:: " << "\n";
	for(int k = 0; k < numberOfActInRecords; k++)
	{
		cout << "Record Number " << k+1 << "\n";
	    cout << "\tActor ID: " << myActIn[k].getActor() << "\n";
	    cout << "\tMovie ID: " << myActIn[k].getMovie() << "\n\n";
	    
	}

	cout << "<------ Part 1 Ends\n\n" << endl;
	cout << "Starting Part 2 ----->\n" << endl;

	sqlite3 *db;
   	char *zErrMsg = 0;
   	int rc;

	rc = sqlite3_open("movie.db", &db);

	if( rc ){
	  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	}else{
	  fprintf(stderr, "Opened database successfully\n");
	}

	const char *sql;

	sql = "CREATE TABLE persons (" \
			"lname varchar(40) not null," \
            "fname varchar(40)," \
            "id int," \
            "primary key (id));";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   	if( rc != SQLITE_OK ){
   		fprintf(stderr, "SQL error: %s\n", zErrMsg);
      	sqlite3_free(zErrMsg);
   	}else{
      	fprintf(stdout, "Table created successfully\n");
   	}

   	sql = "create table movies (title varchar(40) not null, " \
                     "director int not null, " \
                     "year_made int not null, " \
                     "id int, " \
                     "primary key (id), " \
                     "foreign key (director) references persons(id));";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   	if( rc != SQLITE_OK ){
   		fprintf(stderr, "SQL error: %s\n", zErrMsg);
      	sqlite3_free(zErrMsg);
   	}else{
      	fprintf(stdout, "Table created successfully\n");
   	}

   	sql = "create table acts_in (actor int, " \
                      "movie int, " \
                      "primary key (actor, movie), " \
                      "foreign key (actor) references persons(id), " \
                      "foreign key (movie) references movies(id));";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   	if( rc != SQLITE_OK ){
   		fprintf(stderr, "SQL error: %s\n", zErrMsg);
      	sqlite3_free(zErrMsg);
   	}else{
      	fprintf(stdout, "Table created successfully\n");
   	}




   	for(int k = 0; k < numberOfPersonRecords; k++){
		
   		string Lname, Fname;
   		int id;
   		Lname = myPerson[k].getLastName();
   		Fname = myPerson[k].getFirstName();
   		id = myPerson[k].getID();


   		
		std::string thisID;
		std::stringstream out;
		out << id;
		thisID = out.str();

   		sql = ("INSERT INTO PERSONS (LNAME,FNAME,ID) " \
   			"VALUES ('" + Lname +"','" + Fname + "'," + thisID +");").c_str();




	   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	   if( rc != SQLITE_OK ){
	      fprintf(stderr, "SQL error: %s\n", zErrMsg);
	      sqlite3_free(zErrMsg);
	   }else{
	      fprintf(stdout, "Records created successfully\n");
	   }
	}

	for(int k = 0; k < numberOfMovieRecords; k++){
		
   		string Title;
   		int movieId, movieDirector, movieYear;
   		Title = myMovies[k].getMovieTitle();
   		movieId = myMovies[k].getMovieID();
   		movieDirector = myMovies[k].getMovieDirector();
   		movieYear = myMovies[k].getMovieYear();


   		
		std::string thisMovieID, thisMovieDirector, thisMovieYear;
		std::stringstream outId, outDirector, outYear;
		outId << movieId;
		outDirector << movieDirector;
		outYear << movieYear;
		thisMovieID = outId.str();
		thisMovieDirector = outDirector.str();
		thisMovieYear = outYear.str();
		
   		sql = ("INSERT INTO MOVIES (TITLE,DIRECTOR,YEAR_MADE,ID) " \
   			"VALUES ('" + Title +"'," + thisMovieDirector + "," + thisMovieYear +","+ thisMovieID +");").c_str();




	   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	   if( rc != SQLITE_OK ){
	      fprintf(stderr, "SQL error: %s\n", zErrMsg);
	      sqlite3_free(zErrMsg);
	   }else{
	      fprintf(stdout, "Records created successfully\n");
	   }
	}

	for(int k = 0; k < numberOfActInRecords; k++){
		
   		
   		int actor, movie;
   		actor = myActIn[k].getActor();
   		movie = myActIn[k].getMovie();


   		
		std::string thisActor, thisMovie;
		std::stringstream outActor, outMovie;
		outActor << actor;
		outMovie << movie;
		thisActor = outActor.str();
		thisMovie = outMovie.str();
		
   		sql = ("INSERT INTO Acts_In (actor,movie) " \
   			"VALUES (" + thisActor +"," + thisMovie + ");").c_str();




	   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	   if( rc != SQLITE_OK ){
	      fprintf(stderr, "SQL error: %s\n", zErrMsg);
	      sqlite3_free(zErrMsg);
	   }else{
	      fprintf(stdout, "Records created successfully\n");
	   }
	}

	const char* data = "Callback function called";

	sql = "SELECT * from PERSONS";

	std::ofstream myOutputFile;
   	
   	myOutputFile.open("tableOutput.txt", std::ios_base::app);
   	myOutputFile << "Content in Person table: \n";
   	myOutputFile.close();

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }

   sql = "SELECT * from MOVIES";

	myOutputFile.open("tableOutput.txt", std::ios_base::app);
   	myOutputFile << "Content in Movies table: \n";
   	myOutputFile.close();
   

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }

   sql = "SELECT * from Acts_In";

   myOutputFile.open("tableOutput.txt", std::ios_base::app);
   	myOutputFile << "Content in Acts_In table: \n";
   	myOutputFile.close();

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }

   	sqlite3_close(db);

}