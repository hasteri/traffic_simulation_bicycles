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