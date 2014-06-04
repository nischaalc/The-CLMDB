#include <string>
#include <vector>
#include "List.h"
#include "Node.h"
#include "Actor.h"

using namespace std;


Actor::Actor()			//Default Constructor
{}

Actor::Actor(string s)	//Alternate Constructor
{
	actorName_ = s;
}

Actor::~Actor()			//Destructor
{}

string Actor::getName() const		
{
	return actorName_;
}

void Actor::setName(string s)
{
	actorName_ = s;
}

void Actor::addMovie(Movie* moviePtr)
{
	actorMovies_.push_back(moviePtr);
}
