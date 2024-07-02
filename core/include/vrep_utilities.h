#ifndef VREP_UTILITIES_H
#define VREP_UTILITIES_H

#include <iostream>
#include <vector>

extern "C" {
    #include "extApi.h"
/*	#include "extApiCustom.h" if you wanna use custom remote API functions! */
}

namespace vrep_utilities
{
    void init();
    void startSimulation();
    void stopSimulation();
    
    std::string GetCurrentObstacle(std::string name);

    void Pick(std::string name);
    bool IsObjectOnHand(std::string name);
    bool IsHandEmpty();
    bool IsFreeToObject(std::string name);

    void Place(std::string name, std::string goal);
    bool IsObjectOnGoal(std::string name, std::string goal);
    bool IsFreeToGoal(std::string name);

    void ClearPathTo(std::string name);
    void DropObject(std::string name);

}

#endif // VREP_UTILITIES_H
