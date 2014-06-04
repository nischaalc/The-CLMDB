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

void merge_sort(vector<Movie*> & a, int fromIndex, int toIndex);
void merge(vector<Movie*> & a, int fromIndex, int mid, int toIndex);

void merge_sort(vector<Actor*> & a, int fromIndex, int toIndex);
void merge(vector<Actor*> & a, int fromIndex, int mid, int toIndex);

bool actorDuplicates(Actor* first, Actor* second);
bool movieDuplicates(Movie* first, Movie* second);

void trim(string& s);

void searchMovies(const vector<Movie*>& movieList);
void searchDirectors(const vector<Movie*>& movieList);
void searchRating(const vector<Movie*>& movieList);
void searchYear(const vector<Movie*>& movieList);
void searchActor(const vector<Movie*>& movieList);
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
	cout << "'Actor' - to query for a list of movies that an actor has appeared in." << endl;
	cin >> queryChoice;

	if (queryChoice == "Movie" || queryChoice == "movie")
		searchMovies(theMovieList);
	else if (queryChoice == "Director" || queryChoice == "director")
		searchDirectors(theMovieList);
	else if (queryChoice == "Rating" || queryChoice == "rating")
		searchRating(theMovieList);
	else if (queryChoice == "Year" || queryChoice == "year")
		searchYear(theMovieList);
	else if (queryChoice == "Actor" || queryChoice == "actor")
		searchActor(theMovieList);
	
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
			movieActors.push_back(temp);					//Add the 
			theActorList.push_back(temp);
			getline(fin, checkInput);
		}

		merge_sort(movieActors, 0, movieActors.size() - 1);

		Movie* temp = new Movie(movieName, movieDirector, movieRating, movieYear, movieURL, movieActors);			//Assign collected data to a movie object

		theMovieList.push_back(temp);	//Push the newly created movie object onto a vector

		i++;		//Increment the index

	}

	merge_sort(theMovieList, 0, theMovieList.size() - 1);
	merge_sort(theActorList, 0, theActorList.size() - 1);

	theMovieList.erase(unique(theMovieList.begin(), theMovieList.end(), movieDuplicates), theMovieList.end());
	theActorList.erase(unique(theActorList.begin(), theActorList.end(), actorDuplicates), theActorList.end());
}

void merge_sort(vector<Movie*> & a, int fromIndex, int toIndex)
{
	if (fromIndex < toIndex) // don't sort single elements
	{
		int mid = (fromIndex + toIndex) / 2;

		// break vector into two halves and sort each half
		merge_sort(a, fromIndex, mid);
		merge_sort(a, mid + 1, toIndex);

		// merge sorted halves together
		merge(a, fromIndex, mid, toIndex);
	}
}

void merge(vector<Movie*> & a, int fromIndex, int mid, int toIndex)
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
		if (a[i1]->getTitle() < a[i2]->getTitle())
		{
			b[j] = a[i1];
			i1++;
		}
		else
		{
			b[j] = a[i2];
			i2++;
		}
		j++;
	}

	// note that only one of the two while loops below is executed

	// copy any remaining entries of the first half
	while (i1 <= mid)
	{
		b[j] = a[i1];
		i1++;
		j++;
	}
	// copy any remaining entries of the second half
	while (i2 <= toIndex)
	{
		b[j] = a[i2];
		i2++;
		j++;
	}

	// copy back from the temporary vector
	for (j = 0; j < n; j++)
		a[fromIndex + j] = b[j];
}

void merge_sort(vector<Actor*> & a, int fromIndex, int toIndex)
{
	if (fromIndex < toIndex) // don't sort single elements
	{
		int mid = (fromIndex + toIndex) / 2;

		// break vector into two halves and sort each half
		merge_sort(a, fromIndex, mid);
		merge_sort(a, mid + 1, toIndex);

		// merge sorted halves together
		merge(a, fromIndex, mid, toIndex);
	}
}

void merge(vector<Actor*> & a, int fromIndex, int mid, int toIndex)
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
		if (a[i1]->getName() < a[i2]->getName())
		{
			b[j] = a[i1];
			i1++;
		}
		else
		{
			b[j] = a[i2];
			i2++;
		}
		j++;
	}

	// note that only one of the two while loops below is executed

	// copy any remaining entries of the first half
	while (i1 <= mid)
	{
		b[j] = a[i1];
		i1++;
		j++;
	}
	// copy any remaining entries of the second half
	while (i2 <= toIndex)
	{
		b[j] = a[i2];
		i2++;
		j++;
	}

	// copy back from the temporary vector
	for (j = 0; j < n; j++)
		a[fromIndex + j] = b[j];
}

void trim(string& s)
{
	int start = s.find_first_not_of(" ");
	int end = s.find_last_not_of(" ");
	
	s = s.substr(start, end - start + 1);
}

bool actorDuplicates(Actor* first, Actor* second)
{
	if (first->getName() != second->getName())
		return false;

	return true;
}

bool movieDuplicates(Movie* first, Movie* second)
{
	if ((first->getTitle() == second->getTitle()) && (first->getDirector() == second->getDirector()) && (first->getRating() == second->getRating()) && (first->getYear() == second->getYear()))
		return true;

	return false;

}

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

void searchActor(const vector<Movie*>& movieList)
{
	string actorName;

	cout << "Enter the actor whos' movies you want to find: ";
	cin.ignore();
	getline(cin, actorName);
	cout << endl;

	vector<Movie*> foundMovies;

	for (int i = 0; i < movieList.size(); i++)
	{
		for (int j = 0; j < movieList[i]->getNumActors(); j++)
		{
			if (movieList[i]->getYear() == actorName)
				foundMovies.push_back(movieList[i]);
		}
	}

	if (foundMovies.size() != 0)
	{
		cout << foundMovies.size() << " instances of " << actorName << " were found!" << endl << endl;
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