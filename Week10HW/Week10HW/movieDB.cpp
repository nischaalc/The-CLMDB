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

void readFromFile(string userFileName, vector<Movie*>& theMovieList, vector<string>& theActorList);

void merge_sort(vector<Movie*> & a, int fromIndex, int toIndex);
void merge(vector<Movie*> & a, int fromIndex, int mid, int toIndex);

void merge_sort(vector<string> & a, int fromIndex, int toIndex);
void merge(vector<string> & a, int fromIndex, int mid, int toIndex);

void trim(string& s);

bool doesExist(string mTitle, string mDir, string mRate, string mYear, vector<Movie*>& m);

int main(void)
{
	ifstream fin;
	ofstream mout("movieOut.txt");
	ofstream aout("actorOut.txt");
	vector<Movie*> theMovieList;
	vector<string> actorList;

	int i = 0;

	string fileName = "sample.txt";

	readFromFile(fileName, theMovieList, actorList);

	for (int i = 0; i < actorList.size(); i++)
	{
		aout << actorList[i] << endl;
	}

	for (int i = 0; i < theMovieList.size(); i++)
	{
		theMovieList[i]->output(mout);
	}
}

void readFromFile(string userFileName, vector<Movie*> & theMovieList, vector<string>& theActorList)
{
	//-----Variables--------
	ifstream fin;
	fin.open(userFileName);
	string delimiter = "$$$$";
	bool newMovie = false;
	string getInput;
	string tempInput;
	ofstream sOut("sub.txt");

	int i = 0;

	string movieName, movieDirector, movieURL, movieRating, checkInput, movieYear, correctMovieRating;
	vector<string> movieActors;
	vector<Actor> actors;
	//----------------------

	while (!fin.eof())		//Repeat until the end of file is reached
	{
		movieActors.clear();		//Prepare the vector of actors for new entries

		getline(fin, movieName);		//Read in data from the file
		trim(movieName);
		transform(movieName.begin(), ++movieName.begin(), movieName.begin(), toupper);

		getline(fin, movieDirector);
		trim(movieDirector);
		transform(movieDirector.begin(), ++movieDirector.begin(), movieDirector.begin(), toupper);

		fin >> tempInput;
		trim(tempInput);
		istringstream ss(tempInput);

		if ((tempInput.substr(0, 1) == "1") || (tempInput.substr(0, 1) == "2"))
			ss >> movieYear;
		else
		{
			ss >> movieRating;
		}

		fin >> tempInput;
		trim(tempInput);
		istringstream st(tempInput);

		if ((tempInput.substr(0, 1) == "1") || (tempInput.substr(0, 1) == "2"))
			st >> movieYear;
		else
		{
			st >> movieRating;
		}

		doesExist(movieName, movieDirector, movieRating, movieYear, theMovieList);

		fin.ignore();
		getline(fin, movieURL);

		getline(fin, checkInput);

		while (checkInput != delimiter)		//Read in actor data until the delimiter is reached
		{
			trim(checkInput);
			transform(checkInput.begin(), ++checkInput.begin(), checkInput.begin(), toupper);
			movieActors.push_back(checkInput);
			theActorList.push_back(checkInput);
			getline(fin, checkInput);
			
		}

		
		Movie* temp = new Movie(movieName, movieDirector, correctMovieRating, movieYear, movieURL, movieActors);			//Assign collected data to a movie object

		theMovieList.push_back(temp);			//Push the newly created movie object onto a vector
		
		i++;		//Increment the index

	}

	merge_sort(theMovieList, 0, theMovieList.size() - 1);
	merge_sort(theActorList, 0, theActorList.size() - 1);

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

void merge_sort(vector<string> & a, int fromIndex, int toIndex)
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

void merge(vector<string> & a, int fromIndex, int mid, int toIndex)
{
	int n = toIndex - fromIndex + 1; // size of the range to be merged

	// merge both halves into a temporary vector b
	vector<string> b(n);

	int i1 = fromIndex;  // next element to consider in the first half
	int i2 = mid + 1;    // next element to consider in the second half
	int j = 0;           // next open position in b

	// as long as neither i1 nor i2 is past the end, 
	// move the smaller element into b 

	while (i1 <= mid && i2 <= toIndex)
	{
		if (a[i1] < a[i2])
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

bool doesExist(string mTitle, string mDir, string mRate, string mYear, vector<Movie*>& m)
{
	ofstream fout("dupes.txt");
	int counter = 0;
	bool returnVal = false;

	for (int i = 0; i < m.size(); i++)
	{
		if ((m[i]->getTitle() == mTitle) || (m[i]->getDirector() == mDir) || (m[i]->getRating() == mRate) || (m[i]->getYear() == mYear))
		{
			fout << "Duplicate at: " << i << " - " << m[i]->getTitle() << endl;
			counter++;
		}
		else
		{
			fout << "The movie " << m[i]->getTitle() << " does not have exact duplicates." << endl;
		}
	}

	return returnVal;

}