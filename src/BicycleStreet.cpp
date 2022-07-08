#include <iostream>
#include "Vehicle.h"
#include "BicycleIntersection.h"
#include "BicycleStreet.h"
#include "Bicycle.h"


BicycleStreet::BicycleStreet()
{
    _type = ObjectType::objectBicycleStreet;
    _length = 1000.0; // in m
}

void BicycleStreet::setInIntersectionBicycle(std::shared_ptr<BicycleIntersection> in)
{
    _interInBicycle = in;
    in->addStreet(get_shared_this()); // add this street to list of streets connected to the intersection
}

void BicycleStreet::setOutIntersectionBicycle(std::shared_ptr<BicycleIntersection> out)
{
    _interOutBicycle = out;
    out->addStreet(get_shared_this()); // add this street to list of streets connected to the intersection
}