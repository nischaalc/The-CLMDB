//-----------------------------------------------------------
//Program Name: movieDB
//Author: Nischaal Cooray
//Desciption: Allows the user to create a database of movies and their associated actors
//-----------------------------------------------------------

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "Movies.h"
#include "List.h"
#include "Node.h"

using namespace std;

//-----------------Prototypes--------------------------------------
void readFromFile(string userFileName, vector<Movie*>& theMovieList, vector<Actor*>& theActorList);

void merge_sort(vector<Movie*> & movieVector, int fromIndex, int toIndex);
void merge(vector<Movie*> & movieVector, int fromIndex, int mid, int toIndex);

void merge_sort(vector<Actor*> & actorVector, int fromIndex, int toIndex);
void merge(vector<Actor*> & actorVector, int fromIndex, int mid, int toIndex);

bool actorDuplicates(Actor* firstActor, Actor* secondActor);
bool movieDuplicates(Movie* firstMovie, Movie* secondMovie);

void trim(string& s);

void searchMovies(const vector<Movie*>& movieList);
void searchDirectors(const vector<Movie*>& movieList);
void searchRating(const vector<Movie*>& movieList);
void searchYear(const vector<Movie*>& movieList);
//-----------------------------------------------------------------

int main(void)
{
	//-------------Variables-------------
	ifstream fin;
	ofstream mout("ovieOut.txt");
	ofstream aout("ctorOut.txt");
	vector<Movie*> theMovieList;
	vector<Actor*> actorList;
	string fileName, temp, queryChoice;
	int i = 0;
	//-----------------------------------

fromFile:
	//-------Introduction----------------
	cout << "Would you like to read data in from a file? (y/n): ";
	cin >> temp;

	if (temp == "y")
	{
		cout << "Enter the name of the file: ";
		cin >> fileName;
		readFromFile(fileName, theMovieList, actorList);
	}
	else if (temp == "n")
	{
		cout << "Come back soon!" << endl;
		return 0;
	}
	else
	{
		cout << "Unrecognized input. Please try again." << endl;
		goto fromFile;
	}

	cout << "All done." << endl;
	cout << "There are a total of " << theMovieList.size() << " different movies and " << actorList.size() << " actors in your database right now!" << endl;
	//-----------------------------------

search:
	//-----------Queries-----------------
	cout << "Enter one of the following letters to query the respective data." << endl;
	cout << "'Movie' - to query for movies by title." << endl;
	cout << "'Director' - to query for a list of movies directed by the specified director." << endl;
	cout << "'Rating' - to query for all movies matching the specified rating." << endl;
	cout << "'Year' - to query for all movies made in the specified year." << endl;
	cin >> queryChoice;

	if (queryChoice == "Movie" || queryChoice == "movie")
		searchMovies(theMovieList);
	else if (queryChoice == "Director" || queryChoice == "director")
		searchDirectors(theMovieList);
	else if (queryChoice == "Rating" || queryChoice == "rating")
		searchRating(theMovieList);
	else if (queryChoice == "Year" || queryChoice == "year")
		searchYear(theMovieList);
	
	cout << "Do you want to search for more information? (y/n): ";
	cin >> temp;
	
	if (temp == "y")
		goto search;
	else
	{
		cout << "Come back soon!" << endl;
		return 0;
	}
	//-----------------------------------

}

/*
Read in data from the file and insert it into the respective objects
@param userFileName: the name from which the data is to be collected
@param theMovieList: the vector that stores Movie objects
@param theActorList: the vector that stores Actor objects
*/
void readFromFile(string userFileName, vector<Movie*> & theMovieList, vector<Actor*>& theActorList)
{
	//-----Variables--------
	ifstream fin;
	fin.open(userFileName);
	string delimiter = "$$$";
	bool newMovie = false;
	string getInput;
	string tempInput;

	int i = 0;

	string movieName, movieDirector, movieURL, movieRating, checkInput, movieYear, correctMovieRating;
	vector<Actor*> movieActors;
	//----------------------

	while (!fin.eof())					//Repeat until the end of file is reached
	{
		movieActors.clear();			//Prepare the vector of actors for new entries

		getline(fin, movieName);		//Read in data from the file
		trim(movieName);				//Eliminate white space from the start and end of the string
		transform(movieName.begin(), ++movieName.begin(), movieName.begin(), toupper);	//Convert the first letter of the string to an uppercase letter

		getline(fin, movieDirector);
		trim(movieDirector);			//Eliminate white space from the start and end of the string
		transform(movieDirector.begin(), ++movieDirector.begin(), movieDirector.begin(), toupper);	//Convert the first letter of the string to an uppercase letter

		getline(fin, tempInput);
		trim(tempInput);				//Eliminate white space from the start and end of the string

		//----------Differentiate between reading in the Year and reading in the Rating----------
		if ((tempInput.substr(0, 1) == "1") || (tempInput.substr(0, 1) == "2"))
			movieYear = tempInput;
		else
		{
			movieRating = tempInput;
		}

		getline(fin, tempInput);
		trim(tempInput);				//Eliminate white space from the start and end of the string
		
		if ((tempInput.substr(0, 1) == "1") || (tempInput.substr(0, 1) == "2"))
			movieYear = tempInput;
		else
		{
			movieRating = tempInput;
		}
		//---------------------------------------------------------------------------------------

		getline(fin, movieURL);

		getline(fin, checkInput);

		while (checkInput.substr(0, 3) != delimiter)		//Read in actor data until the delimiter is reached
		{
			trim(checkInput);								//Eliminate white space from the start and end of the string
			transform(checkInput.begin(), ++checkInput.begin(), checkInput.begin(), toupper);	//Convert the first letter of the string to an uppercase letter
			Actor* temp = new Actor(checkInput);			//Create a new memory location to store the Actor object
			movieActors.push_back(temp);					//Add the Actor object to the vector in the Movie object
			theActorList.push_back(temp);					//Add the Actor object to a list of all the actors
			getline(fin, checkInput);
		}

		merge_sort(movieActors, 0, movieActors.size() - 1);	//Alphabetically sort the list of actors associated with a movie

		Movie* temp = new Movie(movieName, movieDirector, movieRating, movieYear, movieURL, movieActors);		//Assign collected data to a movie object

		theMovieList.push_back(temp);	//Push the newly created movie object onto a vector

		i++;		//Increment the index

	}
		
	merge_sort(theMovieList, 0, theMovieList.size() - 1);			//Alphabetically sort the list of Movies
	merge_sort(theActorList, 0, theActorList.size() - 1);			//Alphabetically sort the list of actors

	//----------Eliminate duplicates from each vector----------------------
	theMovieList.erase(unique(theMovieList.begin(), theMovieList.end(), movieDuplicates), theMovieList.end());		
	theActorList.erase(unique(theActorList.begin(), theActorList.end(), actorDuplicates), theActorList.end());
	//---------------------------------------------------------------------
}

/*
Part of the recursive algorithm used to sort data
@param movieVector: the vector that stores Movie objects
@param fromIndex: the index from which to start the sort
@param toIndex: the index at which to stop the sort
*/
void merge_sort(vector<Movie*> & movieVector, int fromIndex, int toIndex)
{
	if (fromIndex < toIndex) // don't sort single elements
	{
		int mid = (fromIndex + toIndex) / 2;

		// break vector into two halves and sort each half
		merge_sort(movieVector, fromIndex, mid);
		merge_sort(movieVector, mid + 1, toIndex);

		// merge sorted halves together
		merge(movieVector, fromIndex, mid, toIndex);
	}
}

/*
Part of the recursive algorithm used to sort data
@param movieVector: the vector that stores Movie objects
@param fromIndex: the index from which to start the sort
@param toIndex: the index at which to stop the sort
*/
void merge(vector<Movie*> & movieVector, int fromIndex, int mid, int toIndex)
{
	int n = toIndex - fromIndex + 1; // size of the range to be merged

	// merge both halves into a temporary vector b
	vector<Movie*> b(n);

	int i1 = fromIndex;  // next element to consider in the first half
	int i2 = mid + 1;    // next element to consider in the second half
	int j = 0;           // next open position in b

	// as long as neither i1 nor i2 is past the end, 
	// move the smaller element into b 

	while (i1 <= mid && i2 <= toIndex)
	{
		if (movieVector[i1]->getTitle() < movieVector[i2]->getTitle())
		{
			b[j] = movieVector[i1];
			i1++;
		}
		else
		{
			b[j] = movieVector[i2];
			i2++;
		}
		j++;
	}

	// note that only one of the two while loops below is executed

	// copy any remaining entries of the first half
	while (i1 <= mid)
	{
		b[j] = movieVector[i1];
		i1++;
		j++;
	}
	// copy any remaining entries of the second half
	while (i2 <= toIndex)
	{
		b[j] = movieVector[i2];
		i2++;
		j++;
	}

	// copy back from the temporary vector
	for (j = 0; j < n; j++)
		movieVector[fromIndex + j] = b[j];
}

/*
Part of the recursive algorithm used to sort data
@param actorVector: the vector that stores Actor objects
@param fromIndex: the index from which to start the sort
@param toIndex: the index at which to stop the sort
*/
void merge_sort(vector<Actor*> & actorVector, int fromIndex, int toIndex)
{
	if (fromIndex < toIndex) // don't sort single elements
	{
		int mid = (fromIndex + toIndex) / 2;

		// break vector into two halves and sort each half
		merge_sort(actorVector, fromIndex, mid);
		merge_sort(actorVector, mid + 1, toIndex);

		// merge sorted halves together
		merge(actorVector, fromIndex, mid, toIndex);
	}
}

/*
Part of the recursive algorithm used to sort data
@param actorVector: the vector that stores Actor objects
@param fromIndex: the index from which to start the sort
@param toIndex: the index at which to stop the sort
*/
void merge(vector<Actor*> & actorVector, int fromIndex, int mid, int toIndex)
{
	int n = toIndex - fromIndex + 1; // size of the range to be merged

	// merge both halves into a temporary vector b
	vector<Actor*> b(n);

	int i1 = fromIndex;  // next element to consider in the first half
	int i2 = mid + 1;    // next element to consider in the second half
	int j = 0;           // next open position in b

	// as long as neither i1 nor i2 is past the end, 
	// move the smaller element into b 

	while (i1 <= mid && i2 <= toIndex)
	{
		if (actorVector[i1]->getName() < actorVector[i2]->getName())
		{
			b[j] = actorVector[i1];
			i1++;
		}
		else
		{
			b[j] = actorVector[i2];
			i2++;
		}
		j++;
	}

	// note that only one of the two while loops below is executed

	// copy any remaining entries of the first half
	while (i1 <= mid)
	{
		b[j] = actorVector[i1];
		i1++;
		j++;
	}
	// copy any remaining entries of the second half
	while (i2 <= toIndex)
	{
		b[j] = actorVector[i2];
		i2++;
		j++;
	}

	// copy back from the temporary vector
	for (j = 0; j < n; j++)
		actorVector[fromIndex + j] = b[j];
}

/*
Function used to "trim" leading and trailing white space from a string
@param s: the string to be "trimmed"
*/
void trim(string& s)
{
	int start = s.find_first_not_of(" ");
	int end = s.find_last_not_of(" ");
	
	s = s.substr(start, end - start + 1);
}

/*
Function used to determine whether a duplicate of an object exists
@param firstActor: the Actor object that is being compared
@param secondActor: the Actor object being used as reference
*/
bool actorDuplicates(Actor* firstActor, Actor* secondActor)
{
	if (firstActor->getName() != secondActor->getName())
		return false;

	return true;
}

/*
Function used to determine whether a duplicate of an object exists
@param firstMovie: the Movie object that is being compared
@param secondMovie: the Movie object being used as reference
*/
bool movieDuplicates(Movie* firstMovie, Movie* secondMovie)
{
	if ((firstMovie->getTitle() == secondMovie->getTitle()) && (firstMovie->getDirector() == secondMovie->getDirector()) && (firstMovie->getRating() == secondMovie->getRating()) && (firstMovie->getYear() == secondMovie->getYear()))
		return true;

	return false;

}

/*
Function that searches the vector of Movie objects 
@param movieVector: the vector that stores Movie objects
*/
void searchMovies(const vector<Movie*>& movieList)
{
	string movieName;

	cout << "Enter the name of a movie to find: ";
	cin.ignore();
	getline(cin, movieName);
	cout << endl;

	vector<Movie*> foundMovies;

	for (int i = 0; i < movieList.size(); i++)
	{
		if (movieList[i]->getTitle() == movieName)
			foundMovies.push_back(movieList[i]);
	}

	if (foundMovies.size() != 0)
	{
		cout << foundMovies.size() << " instances of " << movieName << " were found!" << endl << endl;
		for (int j = 0; j < foundMovies.size(); j++)
		{
			foundMovies[j]->output(cout);
			cout << endl;
		}
	}
	else
	{
		cout << "No movies with this name were found! Please try again." << endl;
		searchMovies(movieList);
	}
}

/*
Function that searches the vector of Movie objects
@param movieVector: the vector that stores Movie objects
*/
void searchDirectors(const vector<Movie*>& movieList)
{
	string directorName;

	cout << "Enter the name of a director to find movies they have directed: ";
	cin.ignore();
	getline(cin, directorName);
	cout << endl;

	vector<Movie*> foundMovies;

	for (int i = 0; i < movieList.size(); i++)
	{
		if (movieList[i]->getDirector() == directorName)
			foundMovies.push_back(movieList[i]);
	}

	if (foundMovies.size() != 0)
	{
		cout << foundMovies.size() << " instances of " << directorName << " were found!" << endl << endl;
		for (int j = 0; j < foundMovies.size(); j++)
		{
			foundMovies[j]->output(cout);
			cout << endl;
		}
	}
	else
	{
		cout << "No movies with this name were found! Please try again." << endl;
		searchMovies(movieList);
	}
}

/*
Function that searches the vector of Movie objects
@param movieVector: the vector that stores Movie objects
*/
void searchRating(const vector<Movie*>& movieList)
{
	string rating;

	cout << "Enter the Rating that you would like to filter movies by: ";
	cin.ignore();
	getline(cin, rating);
	cout << endl;

	vector<Movie*> foundMovies;

	for (int i = 0; i < movieList.size(); i++)
	{
		if (movieList[i]->getRating() == rating)
			foundMovies.push_back(movieList[i]);
	}

	if (foundMovies.size() != 0)
	{
		cout << foundMovies.size() << " instances of " << rating << " were found!" << endl << endl;
		for (int j = 0; j < foundMovies.size(); j++)
		{
			foundMovies[j]->output(cout);
			cout << endl;
		}
	}
	else
	{
		cout << "No movies with this name were found! Please try again." << endl;
		searchMovies(movieList);
	}
}

/*
Function that searches the vector of Movie objects
@param movieVector: the vector that stores Movie objects
*/
void searchYear(const vector<Movie*>& movieList)
{
	string year;

	cout << "Enter the Year that you would like to filter movies by: ";
	cin.ignore();
	getline(cin, year);
	cout << endl;

	vector<Movie*> foundMovies;

	for (int i = 0; i < movieList.size(); i++)
	{
		if (movieList[i]->getYear() == year)
			foundMovies.push_back(movieList[i]);
	}

	if (foundMovies.size() != 0)
	{
		cout << foundMovies.size() << " instances of " << year << " were found!" << endl << endl;
		for (int j = 0; j < foundMovies.size(); j++)
		{
			foundMovies[j]->output(cout);
			cout << endl;
		}
	}
	else
	{
		cout << "No movies with this name were found! Please try again." << endl;
		searchMovies(movieList);
	}
}