#include "Movies.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

Movie::Movie()		//Default Constructor
{
}

Movie::Movie(const string& title)		//Alternate Constructor
{
	title_ = title;
}

Movie::Movie(const string& title, const string& director, Movie_Rating rating, const string& year, const string& path, const vector<string>& actors)	//Alternate Constructor
{
	title_ = title;
	director_ = director;
	rating_ = rating; 
	year_ = year;
	url_ = path;

	for (int i = 0; i < actors.size(); i++)
	{
		actors_.push_back(actors[i]);
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

Movie_Rating Movie::getRating() const
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
	return actors_.size();
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

void Movie::addActor(const string& actor)
{
	actors_.push_back(actor);
}

void Movie::output(ostream & out)			//Output to either console or file
{
	out << "Movie: " << title_ << endl;
	out << "Director: " << director_ << endl;
	out << "Year: " << year_ << endl;

	/*if (rating_ == G)
		out << "Rating: G" << endl;
	else if (rating_ == PG)
		out << "Rating: PG" << endl;
	else if (rating_ == PG13)
		out << "Rating: PG13" << endl;
	else if (rating_ == R)
		out << "Rating: R" << endl;
	else if (rating_ == NC17)
		out << "Rating: NC17" << endl;
	else if (rating_ == NR)
		out << "Rating: NR" << endl;*/

	out << "IMDB URL: " << url_ << endl;
	
	int endLoop = actors_.size();

	out << "Cast: " << endl;
	for (int i = 0; i < endLoop; i++)
	{
		out << actors_[i] << endl;
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