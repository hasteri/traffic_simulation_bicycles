#ifndef BICYCLE_H
#define BICYCLE_H

#include "TrafficObject.h"

// forward declarations to avoid include cycle
class BicycleStreet;
class BicycleIntersection;

class Bicycle : public TrafficObject, public std::enable_shared_from_this<Bicycle>
{
public:
    // constructor / desctructor
    Bicycle();

    // getters / setters
    void setCurrentStreetBicycle(std::shared_ptr<BicycleStreet> bicycleStreet) { _currStreet = bicycleStreet; };
    void setCurrentDestination(std::shared_ptr<BicycleIntersection> destination);
    std::shared_ptr<BicycleStreet> getCurrentBicycleStreet() {return _currStreet;};

    // typical behaviour methods
    void simulate();

    // miscellaneous
    std::shared_ptr<Bicycle> get_shared_this() { return shared_from_this(); }

private:
    // typical behaviour methods
    void ride();

    std::shared_ptr<BicycleStreet> _currStreet;            // street on which the vehicle is currently on
    std::shared_ptr<BicycleIntersection> _currDestination; // destination to which the vehicle is currently driving
    double _posStreet;                              // position on current street
    double _speed;                                  // ego speed in m/s
};

#endif