#ifndef BICYCLE_STREET_H
#define BICYCLE_STREET_H

#include "TrafficObject.h"

// forward declaration to avoid include cycle
class BicycleIntersection;

class BicycleStreet : public TrafficObject, public std::enable_shared_from_this<BicycleStreet>
{
public:
    // constructor / desctructor
    BicycleStreet();

    // getters / setters
    double getLength() { return _length; }
    void setInIntersectionBicycle(std::shared_ptr<BicycleIntersection> in);
    void setOutIntersectionBicycle(std::shared_ptr<BicycleIntersection> out);
    std::shared_ptr<BicycleIntersection> getOutIntersectionBicycle() { return _interInBicycle; }
    std::shared_ptr<BicycleIntersection> getInIntersectionBicycle() { return _interOutBicycle; }

    // typical behaviour methods

    // miscellaneous
    std::shared_ptr<BicycleStreet> get_shared_this() { return shared_from_this(); }

private:
    double _length;                                                             // length of this street in m
    std::shared_ptr<BicycleIntersection> _interInBicycle, _interOutBicycle;     // bicycle intersections
};

#endif