#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <random>

#include "Bicycle.h"
#include "BicycleStreet.h"
#include "BicycleIntersection.h"
#include "Vehicle.h"

BicycleIntersection::BicycleIntersection()
{
    _type = ObjectType::objectBicycleIntersection;
    _isBlocked = false;
}

void BicycleIntersection::addStreet(std::shared_ptr<BicycleStreet> bicycleStreet)
{
    _bicycleStreets.push_back(bicycleStreet);
}

std::vector<std::shared_ptr<BicycleStreet>> BicycleIntersection::queryStreets(std::shared_ptr<BicycleStreet> incoming)
{
    // store all outgoing streets in a vector ...
    std::vector<std::shared_ptr<BicycleStreet>> outgoings;
    for (auto it : _bicycleStreets)
    {
        if (incoming->getID() != it->getID()) // ... except the street making the inquiry
        {
            outgoings.push_back(it);
        }
    }

    return outgoings;
}

void BicycleIntersection::vehicleHasLeft(std::shared_ptr<Vehicle> vehicle)
{
    std::cout << "BicycleIntersection #" << _id << ": Vehicle #" << vehicle->getID() << " has left." << std::endl;

    // unblock queue processing
    this->setIsBlocked(false);
}

void BicycleIntersection::setIsBlocked(bool isBlocked)
{
    _isBlocked = isBlocked;
    std::cout << "BicycleIntersection #" << _id << " isBlocked=" << isBlocked << std::endl;
}

// virtual function which is executed in a thread
void BicycleIntersection::simulate() // using threads + promises/futures + exceptions
{
    // FP.6a : In Intersection.h, add a private member _trafficLight of type TrafficLight. At this position, start the simulation of _trafficLight.
    // threads.emplace_back(std::thread(&TrafficLight::simulate, &_trafficLight));
    // launch vehicle queue processing in a thread
    threads.emplace_back(std::thread(&BicycleIntersection::processVehicleWaitingForBicycle, this));
}

// adds a new vehicle to the queue and returns once the vehicle is allowed to enter
void BicycleIntersection::addVehicleToQueue(std::shared_ptr<Vehicle> vehicle)
{
    std::unique_lock<std::mutex> lck(_mtx);
    std::cout << "BicycleIntersection #" << _id << "::addVehicleToQueue: thread id = " << std::this_thread::get_id() << std::endl;
    lck.unlock();

    // add new vehicle to the end of the waiting line
    std::promise<void> prmsVehicleAllowedToEnter;
    std::future<void> ftrVehicleAllowedToEnter = prmsVehicleAllowedToEnter.get_future();
    _vehicleWaitingForBicycles.pushBack(vehicle, std::move(prmsVehicleAllowedToEnter));

    // wait until the vehicle is allowed to enter
    ftrVehicleAllowedToEnter.wait();
    lck.lock();
    std::cout << "BicycleIntersection #" << _id << ": Vehicle #" << vehicle->getID() << " is granted entry." << std::endl;
    
    // FP.6b : use the methods TrafficLight::getCurrentPhase and TrafficLight::waitForGreen to block the execution until the traffic light turns green.

    lck.unlock();

    if(bicycleIsRiding())
    {
        _bicycles.waitForBicycle(); // vehicle should wait for bicycle !!!
    }
}

void BicycleIntersection::processVehicleWaitingForBicycle()
{
    // print id of the current thread
    std::cout << "BicycleIntersection #" << _id << "::processVehicleWaitingForBicycle: thread id = " << std::this_thread::get_id() << std::endl;

    // continuously process the vehicle queue
    while (true)
    {
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // only proceed when at least one vehicle is waiting in the queue
        if (_vehicleWaitingForBicycles.getSize() > 0 && !_isBlocked)
        {
            // set intersection to "blocked" to prevent other vehicles from entering
            this->setIsBlocked(true);

            // permit entry to first vehicle in the queue (FIFO)
            _vehicleWaitingForBicycles.permitEntryToFirstInQueue();
        }
    }
}

bool BicycleIntersection::bicycleIsRiding()
{
   // please include this part once you have solved the final project tasks
   
   if (_bicycles.getCurrentStatus() == BicycleRidingStatus::passingTheStreet)
       return true;
   else
       return false;
   

  return true; // makes traffic light permanently green
} 

/* Implementation of class "VehicleWaitingForBicycle" */

int VehicleWaitingForBicycle::getSize()
{
    std::lock_guard<std::mutex> lock(_mutex);

    return _vehicles.size();
}

void VehicleWaitingForBicycle::pushBack(std::shared_ptr<Vehicle> vehicle, std::promise<void> &&promise)
{
    std::lock_guard<std::mutex> lock(_mutex);

    _vehicles.push_back(vehicle);
    _promises.push_back(std::move(promise));
}

void VehicleWaitingForBicycle::permitEntryToFirstInQueue()
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
