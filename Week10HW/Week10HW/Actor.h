#ifndef _ACTOR__
#define _ACTOR__

#include <string>
#include <vector>
#include "List.h"
#include "Node.h"
#include "Movies.h"

using namespace std;

class Actor
{

	friend class Movie;

public:
	Actor();
	Actor(string s);

	~Actor();

	string getName() const;

private:
	List<Movie*> actorMovies_;
	string actorName_;
};

#endif