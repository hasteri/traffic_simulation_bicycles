#ifndef VEHICLE_H
#define VEHICLE_H

#include "TrafficObject.h"
#include "Bicycle.h"

// forward declarations to avoid include cycle
class Street;
class Intersection;
class Bicycle;
class BicycleStreet;
class BicycleIntersection;
class RidingBicycles;

class Vehicle : public TrafficObject, public std::enable_shared_from_this<Vehicle>
{
public:
    // constructor / desctructor
    Vehicle();

    // getters / setters
    void setCurrentStreet(std::shared_ptr<Street> street) { _currStreet = street; };
    void setCurrentDestination(std::shared_ptr<Intersection> destination);
    auto getCurrentVehicleStreet() {return _currStreet.get();};
    void setSpeed(int speed){_speed = speed;};

    // typical behaviour methods
    void simulate();

    // miscellaneous
    std::shared_ptr<Vehicle> get_shared_this() { return shared_from_this(); }
    void waitForBicycle(std::shared_ptr<Bicycle> bicycle);
    bool bicycleBlocking();
    bool getCurrentStatus();
    void setBicycleBlocking(bool block){_block=block;};

    void drive();

    // operator == overload to compare two shared pointers
    template < class T, class U >
    friend bool operator==( const std::shared_ptr<T>& lhs,
                    const std::shared_ptr<U>& rhs ) noexcept;

private:
    // typical behaviour methods
    

    std::shared_ptr<Street> _currStreet;            // street on which the vehicle is currently on
    std::shared_ptr<Intersection> _currDestination; // destination to which the vehicle is currently driving
    double _posStreet;                              // position on current street
    double _speed;                                  // ego speed in m/s
    bool _block = false;
    Bicycle _bicycle;
};

#endif