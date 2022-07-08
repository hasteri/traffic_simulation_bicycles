#include <iostream>
#include <thread>
#include <vector>

#include "Vehicle.h"
#include "Bicycle.h"
#include "Street.h"
#include "BicycleStreet.h"
#include "Intersection.h"
#include "BicycleIntersection.h"
#include "Graphics.h"


// Paris
void createTrafficObjects_Paris(std::vector<std::shared_ptr<Street>> &streets, std::vector<std::shared_ptr<BicycleStreet>> &bicycleStreets, 
std::vector<std::shared_ptr<Intersection>> &intersections, std::vector<std::shared_ptr<BicycleIntersection>> &bicycleIntersections, 
std::vector<std::shared_ptr<Vehicle>> &vehicles, std::vector<std::shared_ptr<Bicycle>> &bicycles, std::string &filename, int nVehicles, int nBicycles)
{
    // assign filename of corresponding city map
    filename = "../data/paris.jpg";

    // init traffic objects
    int nIntersections = 9;
    for (size_t ni = 0; ni < nIntersections; ni++)
    {
        intersections.push_back(std::make_shared<Intersection>());
    }

    int nbicycleIntersections = 16;
    for(size_t nbi = 0; nbi < nbicycleIntersections; nbi++)
    {
        bicycleIntersections.push_back(std::make_shared<BicycleIntersection>());
    }

    // position intersections in pixel coordinates (counter-clockwise)
    intersections.at(0)->setPosition(385, 270);
    intersections.at(1)->setPosition(1240, 80);
    intersections.at(2)->setPosition(1625, 75);
    intersections.at(3)->setPosition(2110, 75);
    intersections.at(4)->setPosition(2840, 175); 
    intersections.at(5)->setPosition(3070, 680);
    intersections.at(6)->setPosition(2800, 1400);
    intersections.at(7)->setPosition(400, 1100);
    intersections.at(8)->setPosition(1700, 900); // central plaza

    // From this point the bicycle intersections are defined
    bicycleIntersections.at(0)->setPosition(1330, 800);
    bicycleIntersections.at(1)->setPosition(1400, 660);

    bicycleIntersections.at(2)->setPosition(1470, 590);
    bicycleIntersections.at(3)->setPosition(1550, 540);

    bicycleIntersections.at(4)->setPosition(1630, 510);
    bicycleIntersections.at(5)->setPosition(1720, 500);

    bicycleIntersections.at(6)->setPosition(1850, 530);
    bicycleIntersections.at(7)->setPosition(1920, 560);

    bicycleIntersections.at(8)->setPosition(2020, 660);
    bicycleIntersections.at(9)->setPosition(2070, 730);

    bicycleIntersections.at(10)->setPosition(2100, 800);
    bicycleIntersections.at(11)->setPosition(2110, 890);

    bicycleIntersections.at(12)->setPosition(2090, 1000);
    bicycleIntersections.at(13)->setPosition(2020, 1140);
    
    bicycleIntersections.at(14)->setPosition(1340, 990);
    bicycleIntersections.at(15)->setPosition(1330, 910);

    // create streets and connect traffic objects
    int nStreets = 8;
    for (size_t ns = 0; ns < nStreets; ns++)
    {
        streets.push_back(std::make_shared<Street>());
        streets.at(ns)->setInIntersection(intersections.at(ns));
        streets.at(ns)->setOutIntersection(intersections.at(8));
    }

    // add vehicles to streets
    for (size_t nv = 0; nv < nVehicles; nv++)
    {
        vehicles.push_back(std::make_shared<Vehicle>());
        vehicles.at(nv)->setCurrentStreet(streets.at(nv));
        vehicles.at(nv)->setCurrentDestination(intersections.at(8));
    }

    // create bicycle streets
    int nBicycleStreets = 8;
    for (size_t ns = 0; ns < nBicycleStreets; ns++)
    {
        bicycleStreets.push_back(std::make_shared<BicycleStreet>());
    } 
    
    bicycleStreets.at(0)->setInIntersectionBicycle(bicycleIntersections.at(0));
    bicycleStreets.at(0)->setOutIntersectionBicycle(bicycleIntersections.at(1));

    bicycleStreets.at(1)->setInIntersectionBicycle(bicycleIntersections.at(2));
    bicycleStreets.at(1)->setOutIntersectionBicycle(bicycleIntersections.at(3));

    bicycleStreets.at(2)->setInIntersectionBicycle(bicycleIntersections.at(4));
    bicycleStreets.at(2)->setOutIntersectionBicycle(bicycleIntersections.at(5));

    bicycleStreets.at(3)->setInIntersectionBicycle(bicycleIntersections.at(6));
    bicycleStreets.at(3)->setOutIntersectionBicycle(bicycleIntersections.at(7));

    bicycleStreets.at(4)->setInIntersectionBicycle(bicycleIntersections.at(8));
    bicycleStreets.at(4)->setOutIntersectionBicycle(bicycleIntersections.at(9));

    bicycleStreets.at(5)->setInIntersectionBicycle(bicycleIntersections.at(10));
    bicycleStreets.at(5)->setOutIntersectionBicycle(bicycleIntersections.at(11));

    bicycleStreets.at(6)->setInIntersectionBicycle(bicycleIntersections.at(12));
    bicycleStreets.at(6)->setOutIntersectionBicycle(bicycleIntersections.at(13));

    bicycleStreets.at(7)->setInIntersectionBicycle(bicycleIntersections.at(14));
    bicycleStreets.at(7)->setOutIntersectionBicycle(bicycleIntersections.at(15));

    // add bicycles to streets
    for (size_t nb = 0; nb < nBicycles; nb++)
    {
        bicycles.push_back(std::make_shared<Bicycle>());
    }
    bicycles.at(0)->setCurrentStreetBicycle(bicycleStreets.at((0)));
    bicycles.at(0)->setCurrentDestination(bicycleIntersections.at(1));

    bicycles.at(1)->setCurrentStreetBicycle(bicycleStreets.at((2)));
    bicycles.at(1)->setCurrentDestination(bicycleIntersections.at(5));

    bicycles.at(2)->setCurrentStreetBicycle(bicycleStreets.at((3)));
    bicycles.at(2)->setCurrentDestination(bicycleIntersections.at(7));

    bicycles.at(3)->setCurrentStreetBicycle(bicycleStreets.at((5)));
    bicycles.at(3)->setCurrentDestination(bicycleIntersections.at(11));
}

// NYC
/*
void createTrafficObjects_NYC(std::vector<std::shared_ptr<Street>> &streets, std::vector<std::shared_ptr<Intersection>> &intersections, std::vector<std::shared_ptr<Vehicle>> &vehicles, std::string &filename, int nVehicles)
{
    // assign filename of corresponding city map
    filename = "../data/nyc.jpg";

    // init traffic objects
    int nIntersections = 6;
    for (size_t ni = 0; ni < nIntersections; ni++)
    {
        intersections.push_back(std::make_shared<Intersection>());
    }

    // position intersections in pixel coordinates
    intersections.at(0)->setPosition(1430, 625);
    intersections.at(1)->setPosition(2575, 1260);
    intersections.at(2)->setPosition(2200, 1950);
    intersections.at(3)->setPosition(1000, 1350);
    intersections.at(4)->setPosition(400, 1000);
    intersections.at(5)->setPosition(750, 250);

    // create streets and connect traffic objects
    int nStreets = 7;
    for (size_t ns = 0; ns < nStreets; ns++)
    {
        streets.push_back(std::make_shared<Street>());
    }

    streets.at(0)->setInIntersection(intersections.at(0));
    streets.at(0)->setOutIntersection(intersections.at(1));

    streets.at(1)->setInIntersection(intersections.at(1));
    streets.at(1)->setOutIntersection(intersections.at(2));

    streets.at(2)->setInIntersection(intersections.at(2));
    streets.at(2)->setOutIntersection(intersections.at(3));

    streets.at(3)->setInIntersection(intersections.at(3));
    streets.at(3)->setOutIntersection(intersections.at(4));

    streets.at(4)->setInIntersection(intersections.at(4));
    streets.at(4)->setOutIntersection(intersections.at(5));

    streets.at(5)->setInIntersection(intersections.at(5));
    streets.at(5)->setOutIntersection(intersections.at(0));

    streets.at(6)->setInIntersection(intersections.at(0));
    streets.at(6)->setOutIntersection(intersections.at(3));

    // add vehicles to streets
    for (size_t nv = 0; nv < nVehicles; nv++)
    {
        vehicles.push_back(std::make_shared<Vehicle>());
        vehicles.at(nv)->setCurrentStreet(streets.at(nv));
        vehicles.at(nv)->setCurrentDestination(intersections.at(nv));
    }
}
*/
/* Main function */
int main()
{
    /* PART 1 : Set up traffic objects */

    // create and connect intersections and streets
    std::vector<std::shared_ptr<Street>> streets;
    std::vector<std::shared_ptr<BicycleStreet>> bicycleStreets;
    std::vector<std::shared_ptr<Intersection>> intersections;
    std::vector<std::shared_ptr<BicycleIntersection>> bicycleIntersections;
    std::vector<std::shared_ptr<Vehicle>> vehicles;
    std::vector<std::shared_ptr<Bicycle>> bicycles;
    std::string backgroundImg;
    int nVehicles = 6;
    int nBicycles = 4;
    createTrafficObjects_Paris(streets, bicycleStreets, intersections, bicycleIntersections, vehicles, bicycles, backgroundImg, nVehicles, nBicycles);

    /* PART 2 : simulate traffic objects */

    // simulate intersection
    std::for_each(intersections.begin(), intersections.end(), [](std::shared_ptr<Intersection> &i) {
        i->simulate();
    });

    // simulate bicycle intersections
    std::for_each(bicycleIntersections.begin(), bicycleIntersections.end(), [](std::shared_ptr<BicycleIntersection> &bi) {
        bi->simulate();
    });

    // simulate vehicles
    std::for_each(vehicles.begin(), vehicles.end(), [](std::shared_ptr<Vehicle> &v) {
        v->simulate();
    });

    // simulate bicycles
    std::for_each(bicycles.begin(), bicycles.end(), [](std::shared_ptr<Bicycle> &b) {
        b->simulate();
    });

    /* PART 3 : Launch visualization */

    // add all objects into common vector
    std::vector<std::shared_ptr<TrafficObject>> trafficObjects;
    std::for_each(intersections.begin(), intersections.end(), [&trafficObjects](std::shared_ptr<Intersection> &intersection) {
        std::shared_ptr<TrafficObject> trafficObject = std::dynamic_pointer_cast<TrafficObject>(intersection);
        trafficObjects.push_back(trafficObject);
    });

    std::for_each(bicycleIntersections.begin(), bicycleIntersections.end(), [&trafficObjects](std::shared_ptr<BicycleIntersection> &bicycleIntersection) {
        std::shared_ptr<TrafficObject> trafficObject = std::dynamic_pointer_cast<TrafficObject>(bicycleIntersection);
        trafficObjects.push_back(trafficObject);
    });

    std::for_each(vehicles.begin(), vehicles.end(), [&trafficObjects](std::shared_ptr<Vehicle> &vehicles) {
        std::shared_ptr<TrafficObject> trafficObject = std::dynamic_pointer_cast<TrafficObject>(vehicles);
        trafficObjects.push_back(trafficObject);
    });

    std::for_each(bicycles.begin(), bicycles.end(), [&trafficObjects](std::shared_ptr<Bicycle> &bicycles) {
        std::shared_ptr<TrafficObject> trafficObject = std::dynamic_pointer_cast<TrafficObject>(bicycles);
        trafficObjects.push_back(trafficObject);
    });

    // draw all objects in vector
    Graphics *graphics = new Graphics();
    graphics->setBgFilename(backgroundImg);
    graphics->setTrafficObjects(trafficObjects);
    graphics->simulate();
}
