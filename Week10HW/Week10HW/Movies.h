// ----------------------------------------------------------------------------
//
//  Movie class
//    Header
//
//  This class represents a movie, featuring a title, director, rating, 
//  year of release, and URL for further information in the Internet
//  Movie Database (IMDB, http://www.imdb.com ) .
//
// ----------------------------------------------------------------------------
//
//  Author:         JL Popyack
//  Date:           4/4/4
//  Modified:       4/2/14  -- JL Popyack, removed destructor
//					4/8/14	-- Nischaal Cooray, added output method
//
// ----------------------------------------------------------------------------
#ifndef _MOVIE__
#define _MOVIE__

#include <string>
#include <vector>
#include "List.h"
#include "Node.h"
#include "Actor.h"

using namespace std;

enum Movie_Rating { G, PG, PG13, R, NC17, NR };

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

class Movie
{
public:

	friend class Actor;

	// ------------------------------------------------------
	// ----- Constructors --------------------	---------------
	// ------------------------------------------------------

	Movie();
	Movie(const string& title);
	Movie(const string& title,
		const string& director,
		const string& rating,
		const string& year,
		const string& path,
		const vector<string>& actors,
		const vector<Actor*>& actorList);

	// ------------------------------------------------------
	// ----- Destructor -------------------------------------
	// ------------------------------------------------------

	~Movie();  

	// ------------------------------------------------------
	// ----- Inspectors -------------------------------------
	// ------------------------------------------------------

	string getTitle() const;
	string getDirector() const;
	string getRating() const;
	string getYear() const;
	string getURL() const;
	int getNumActors() const;

	// ------------------------------------------------------
	// ----- Mutators ---------------------------------------
	// ------------------------------------------------------

	void setDirector(const string& director);
	void setRating(Movie_Rating rating);
	void setYear(const string& year);
	void setURL(const string& path);
	void setTitle(const string& title);
	void addActor(const string& actor);

	// ------------------------------------------------------
	// ----- Facilitators ---------------------------------------
	// ------------------------------------------------------

	void output(ostream & out);
	void insert(ostream & out) const;

	// ----------------------------------------------------------
	// ----------------------------------------------------------

private:
	string title_;
	string director_;
	string rating_;
	string year_;
	string url_;
	vector<string> actors_;
	vector<Actor*> actorPointers_;

};

ostream& operator<<(ostream& out, const Movie*& movieObject);


#endif 