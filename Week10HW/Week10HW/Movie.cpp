#include "Movies.h"
#include "List.h"
#include "Node.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

Movie::Movie()		//Default Constructor
{
}

Movie::Movie(const string& title)		//Alternate Constructor
{
	title_ = title;
}

Movie::Movie(const string& title, const string& director, const string& rating, const string& year, const string& path, const vector<Actor*>& actorList)	//Alternate Constructor
{
	title_ = title;
	director_ = director;
	rating_ = rating; 
	year_ = year;
	url_ = path;

	for (int i = 0; i < actorList.size(); i++)
	{
		actorPointers_.push_back(actorList[i]);
	}

}

Movie::~Movie()
{
}

string Movie::getTitle() const
{
	return title_;
}

string Movie::getDirector() const
{
	return director_;
}

string Movie::getRating() const
{
	return rating_;
}

string Movie::getYear() const
{
	return year_;
}

string Movie::getURL() const
{
	return url_;
}

int Movie::getNumActors() const
{
	return actorPointers_.size();
}

void Movie::setDirector(const string& director)
{
	director_ = director;
}

void Movie::setRating(Movie_Rating rating)
{
	rating_ = rating;
}

void Movie::setYear(const string& year)
{
	year_ = year;
}

void Movie::setURL(const string& path)
{
	url_ = path;
}

void Movie::setTitle(const string& title)
{
	title_ = title;
}

void Movie::addActor(Actor*& actor)
{
	actorPointers_.push_back(actor);
}


void Movie::output(ostream & out)			//Output to either console or file
{
	out << "Movie: " << getTitle() << endl;
	out << "Director: " << getDirector() << endl;
	out << "Year: " << getYear() << endl;

	out << "Rating: " << getRating() << endl;

	out << "IMDB URL: " << getURL() << endl;

	out << "Cast: " << endl;
	
	for (int i = 0; i < getNumActors(); i++)
	{
		out << actorPointers_[i]->getName() << endl;
	}

}

void Movie::insert(ostream & out) const
{
	out << &Movie::output;
}

ostream& operator<<(ostream& out, const Movie& movieObject)
{
	movieObject.insert(out);
	return out;
}