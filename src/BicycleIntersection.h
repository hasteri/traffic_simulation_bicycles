#ifndef BICYCLE_INTERSECTION_H
#define BICYCLE_INTERSECTION_H

#include <vector>
#include <future>
#include <mutex>
#include <memory>
#include "TrafficObject.h"
#include "TrafficLight.h"
#include "Bicycle.h"

// forward declarations to avoid include cycle
class Street;
class Vehicle;
class BicycleStreet;

// auxiliary class to gather all bicycles
class VehicleWaitingForBicycle
{
public:
    // getters / setters
    int getSize();
    std::vector<std::shared_ptr<Bicycle>> getAllBicycles() {return _bicycles;}
    // typical behaviour methods
    void pushBack(std::shared_ptr<Vehicle> vehicle, std::promise<void> &&promise);
    void permitEntryToFirstInQueue();
    //bool bicycleIsRiding();
    

private:
    std::vector<std::shared_ptr<Bicycle>> _bicycles;          // list of all vehicles waiting to enter this intersection

    std::vector<std::shared_ptr<Vehicle>> _vehicles;
    std::vector<std::promise<void>> _promises; // list of associated promises
    std::mutex _mutex;
};


class BicycleIntersection : public TrafficObject
{
public:
    // constructor / desctructor
    BicycleIntersection();

    // getters / setters
    void setIsBlocked(bool isBlocked);

    // typical behaviour methods
    void addVehicleToQueue(std::shared_ptr<Vehicle> vehicle);
    void addStreet(std::shared_ptr<BicycleStreet> street);
    std::vector<std::shared_ptr<BicycleStreet>> queryStreets(std::shared_ptr<BicycleStreet> incoming); // return pointer to current list of all outgoing streets
    void simulate();
    void vehicleHasLeft(std::shared_ptr<Vehicle> vehicle);
    bool bicycleIsRiding();

private:

    // typical behaviour methods
   // void processVehicleWaitingForBicycle();

    // private members
    std::vector<std::shared_ptr<BicycleStreet>> _bicycleStreets;   // list of all streets connected to this intersection
    VehicleWaitingForBicycle _vehicleWaitingForBicycles;
    bool _isBlocked;                  // flag indicating wether the intersection is blocked by a vehicle
    Bicycle _bicycles;
};

#endif
