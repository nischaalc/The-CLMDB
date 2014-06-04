#include <string>
#include <vector>
#include "List.h"
#include "Node.h"
#include "Actor.h"

using namespace std;


Actor::Actor()
{

}

Actor::Actor(string s)
{
	actorName_ = s;
}

Actor::~Actor()
{

}

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
