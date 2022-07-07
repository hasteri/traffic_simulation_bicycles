#ifndef BICYCLE_INTERSECTION_H
#define BICYCLE_INTERSECTION_H

#include <vector>
#include <future>
#include <mutex>
#include <memory>
#include "TrafficObject.h"
#include "TrafficLight.h"

// forward declarations to avoid include cycle
class Street;
class Bicycle;

class BicycleIntersection : public TrafficObject
{
public:
    // constructor / desctructor
    BicycleIntersection();

    // getters / setters
    void setIsBlocked(bool isBlocked);

    // typical behaviour methods
    void addStreet(std::shared_ptr<Street> street);
    std::vector<std::shared_ptr<Street>> queryStreets(std::shared_ptr<Street> incoming); // return pointer to current list of all outgoing streets
    void simulate();
    void bicycleHasLeft(std::shared_ptr<Bicycle> bicycle);

private:

    // typical behaviour methods

    // private members
    std::vector<std::shared_ptr<Street>> _streets;   // list of all streets connected to this intersection
    bool _isBlocked;                  // flag indicating wether the intersection is blocked by a vehicle
};

#endif
