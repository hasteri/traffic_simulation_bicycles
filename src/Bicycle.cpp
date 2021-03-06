#include <iostream>
#include <random>
#include "Bicycle.h"
#include "BicycleIntersection.h"
#include "BicycleStreet.h"

template<typename T1>
T1 WaitForBicycleQueue<T1>::receive()
{
    std::unique_lock<std::mutex> uLock(_mtx);
    _cond.wait(uLock, [this] {return !_queue.empty();});
    T1 message = std::move(_queue.back());
    _queue.pop_back(); 

    return message;
}

template <typename T1>
void WaitForBicycleQueue<T1>::send(T1 &&message)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
    std::lock_guard<std::mutex> myLock(_mtx);

    _queue.push_back(std::move(message));
    _cond.notify_one();
}

Bicycle::Bicycle()
{
    _currStreet = nullptr;
    _posStreet = 0.0;
    _type = ObjectType::objectBicycle;
    _speed = 150; // m/s
    _ridingStatus = BicycleRidingStatus::passingTheStreet;
}

void Bicycle::waitForBicycle()
{
    while(true)
    {        
        if(_bicycleQueue.receive() == BicycleRidingStatus::goingToIntersection)
        {
            break;
        }
    }
}

bool Bicycle::bicycleBlocking()
{
    if(_ridingStatus == BicycleRidingStatus::passingTheStreet)
    {
        return true;
    }
    else
    {
        return false;
    }
}



void Bicycle::setCurrentDestination(std::shared_ptr<BicycleIntersection> destination)
{
    // update destination
    _currDestination = destination;

    // reset simulation parameters
    _posStreet = 0.0;
}

void Bicycle::simulate()
{
    // launch drive function in a thread
    threads.emplace_back(std::thread(&Bicycle::ride, this));
}

// virtual function which is executed in a thread
void Bicycle::ride()
{
    _ridingStatus = BicycleRidingStatus::passingTheStreet;
    // print id of the current thread
    std::unique_lock<std::mutex> lck(_mtx);
    std::cout << "Bicycle #" << _id << "::ride: thread id = " << std::this_thread::get_id() << std::endl;
    lck.unlock();

    // initalize variables
    bool hasEnteredIntersection = false;
    double cycleDuration = 1; // duration of a single simulation cycle in ms
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;

    // init stop watch
    lastUpdate = std::chrono::system_clock::now();
    while (true)
    {
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // compute time difference to stop watch
        long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
        if (timeSinceLastUpdate >= cycleDuration)
        {
            // update position with a constant velocity motion model
            _posStreet += _speed * timeSinceLastUpdate / 1000;

            // compute completion rate of current street
            double completion = _posStreet / _currStreet->getLength();

            // compute current pixel position on street based on driving direction
            std::shared_ptr<BicycleIntersection> i1, i2;
            i2 = _currDestination;
            i1 = i2->getID() == _currStreet->getInIntersectionBicycle()->getID() ? _currStreet->getOutIntersectionBicycle() : _currStreet->getInIntersectionBicycle();

            double x1, y1, x2, y2, xv, yv, dx, dy, l;
            i1->getPosition(x1, y1);
            i2->getPosition(x2, y2);
            dx = x2 - x1;
            dy = y2 - y1;
            l = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (x1 - x2));
            xv = x1 + completion * dx; // new position based on line equation in parameter form
            yv = y1 + completion * dy;
            this->setPosition(xv, yv);

            if (completion >= 0.9 && !hasEnteredIntersection)
            {                
                // slow down and set intersection flag
                _speed = 15.0;
                hasEnteredIntersection = true;     
                _ridingStatus = BicycleRidingStatus::goingToIntersection;
                std::cout << "Now bicycle has speed of " << getSpeed() << std::endl;           
            }
            
            
            // check wether intersection has been crossed
            if (completion >= 1.0 && hasEnteredIntersection)
            {
                std::cout << "Now bicycle " << _ridingStatus << std::endl;
                _ridingStatus = BicycleRidingStatus::passingTheStreet;
                std::cout << "Now bicycle " << _ridingStatus << std::endl;
                // choose next street and destination
                std::vector<std::shared_ptr<BicycleStreet>> streetOptions = _currDestination->queryStreets(_currStreet);
                std::shared_ptr<BicycleStreet> nextStreet;
                // if (streetOptions.size() > 0)
                // {
                //     // pick one street at random and query intersection to enter this street
                //     std::random_device rd;
                //     std::mt19937 eng(rd());
                //     std::uniform_int_distribution<> distr(0, streetOptions.size() - 1);
                //     nextStreet = streetOptions.at(distr(eng));
                // }
                // else
                // {
                    // this street is a dead-end, so drive back the same way
                    nextStreet = _currStreet;
                //}
                
                // pick the one intersection at which the vehicle is currently not
                std::shared_ptr<BicycleIntersection> nextIntersection = nextStreet->getInIntersectionBicycle()->getID() 
                == _currDestination->getID() ? nextStreet->getOutIntersectionBicycle() : nextStreet->getInIntersectionBicycle(); 

                // send signal to intersection that vehicle has left the intersection
                // _currDestination->bicycleHasLeft(get_shared_this());

                // assign new street and destination
                this->setCurrentDestination(nextIntersection);
                this->setCurrentStreetBicycle(nextStreet);

                // reset speed and intersection flag
                _speed *= 10.0;
                hasEnteredIntersection = false;
            }

            // reset stop watch for next cycle
            lastUpdate = std::chrono::system_clock::now();
        }
    } // eof simulation loop
}


// bool Bicycle::bicycleIsRiding()
// {
//    // please include this part once you have solved the final project tasks
   
//    if (_ridingStatus == BicycleRidingStatus::passingTheStreet)
//        return true;
//    else
//        return false;
   

//   return true; // makes traffic light permanently green
// } 