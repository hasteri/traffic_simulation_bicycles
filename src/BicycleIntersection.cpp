#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <random>

#include "Street.h"
#include "BicycleIntersection.h"
#include "Vehicle.h"

BicycleIntersection::BicycleIntersection()
{
    _type = ObjectType::objectBicycleIntersection;
    _isBlocked = false;
}

void BicycleIntersection::addStreet(std::shared_ptr<Street> street)
{
    _streets.push_back(street);
}

std::vector<std::shared_ptr<Street>> BicycleIntersection::queryStreets(std::shared_ptr<Street> incoming)
{
    // store all outgoing streets in a vector ...
    std::vector<std::shared_ptr<Street>> outgoings;
    for (auto it : _streets)
    {
        if (incoming->getID() != it->getID()) // ... except the street making the inquiry
        {
            outgoings.push_back(it);
        }
    }

    return outgoings;
}

void BicycleIntersection::bicycleHasLeft(std::shared_ptr<Bicycle> bicycle)
{
    //std::cout << "Intersection #" << _id << ": Vehicle #" << vehicle->getID() << " has left." << std::endl;

    // unblock queue processing
    this->setIsBlocked(false);
}

void BicycleIntersection::setIsBlocked(bool isBlocked)
{
    _isBlocked = isBlocked;
    //std::cout << "Intersection #" << _id << " isBlocked=" << isBlocked << std::endl;
}

// virtual function which is executed in a thread
void BicycleIntersection::simulate() // using threads + promises/futures + exceptions
{
    // FP.6a : In Intersection.h, add a private member _trafficLight of type TrafficLight. At this position, start the simulation of _trafficLight.
    // threads.emplace_back(std::thread(&TrafficLight::simulate, &_trafficLight));
    // launch vehicle queue processing in a thread
    // threads.emplace_back(std::thread(&BicycleIntersection::processVehicleQueue, this));
}




/* Implementation of class "WaitingVehicles" */

int RidingBicycles::getSize()
{
    std::lock_guard<std::mutex> lock(_mutex);

    return _bicycles.size();
}

void RidingBicycles::pushBack(std::shared_ptr<Bicycle> bicycle, std::promise<void> &&promise)
{
    std::lock_guard<std::mutex> lock(_mutex);

    _bicycles.push_back(bicycle);
    _promises.push_back(std::move(promise));
}
/*
void RidingBicycles::permitEntryToFirstInQueue()
{
    std::lock_guard<std::mutex> lock(_mutex);

    // get entries from the front of both queues
    auto firstPromise = _promises.begin();
    auto firstVehicle = _vehicles.begin();

    // fulfill promise and send signal back that permission to enter has been granted
    firstPromise->set_value();

    // remove front elements from both queues
    _vehicles.erase(firstVehicle);
    _promises.erase(firstPromise);
}
*/