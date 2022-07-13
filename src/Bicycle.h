#ifndef BICYCLE_H
#define BICYCLE_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class BicycleStreet;
class BicycleIntersection;

class Vehicle;

template <class T1>
class WaitForBicycleQueue
{
public:
    T1 receive();
    void send(T1 &&message);
private:
    std::deque<T1> _queue;
    std::condition_variable _cond;
    std::mutex _mtx;
};

enum BicycleRidingStatus
{
    passingTheStreet,
    goingToIntersection,
};

class Bicycle : public TrafficObject //, public std::enable_shared_from_this<Bicycle>
{
public:
    // constructor / desctructor
    Bicycle();

    // getters / setters
    void setCurrentStreetBicycle(std::shared_ptr<BicycleStreet> bicycleStreet) { _currStreet = bicycleStreet; };
    void setCurrentDestination(std::shared_ptr<BicycleIntersection> destination);
    std::shared_ptr<BicycleStreet> getCurrentBicycleStreet() {return _currStreet;};
    void waitForBicycle();
    BicycleRidingStatus getCurrentStatus() {return _ridingStatus;};

    // typical behaviour methods
    void simulate();

    // miscellaneous
    // std::shared_ptr<Bicycle> get_shared_this() { return shared_from_this(); }

private:
    // typical behaviour methods
    void ride();

    std::shared_ptr<BicycleStreet> _currStreet;            // street on which the vehicle is currently on
    std::shared_ptr<BicycleIntersection> _currDestination; // destination to which the vehicle is currently driving
    double _posStreet;                              // position on current street
    double _speed;                                  // ego speed in m/s

    BicycleRidingStatus _ridingStatus;
    WaitForBicycleQueue<BicycleRidingStatus> _bicycleQueue;
    std::condition_variable _condition;
    std::mutex _mutex;
};

#endif