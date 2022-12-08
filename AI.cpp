/*
 * Copyright 2022 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core

string getAIMoveString(const BuildingState& buildingState) {
    int angerDiff = MAX_ANGER - 1;
    int distance = NUM_FLOORS - 1;
    int currentDistance;
    int currentAngerDiff;
    string elevator;
    int elevatorNum;
    string floor;
    
    for (int i = 0; i < NUM_ELEVATORS; i++)
    {
        if (!(buildingState.elevators[i].isServicing))
        {
            for (int z = 0; z < NUM_FLOORS; z++)
            {
                for (int x = 0; x < buildingState.floors[z].numPeople; x++)
                {
                    currentAngerDiff = MAX_ANGER - buildingState.floors[z].people[x].angerLevel;
                    currentDistance = abs(buildingState.elevators[i].currentFloor - z);

                    if (currentAngerDiff <= angerDiff)
                    {
                        
                        if (currentDistance < distance)
                        {
                            elevator = buildingState.elevators[i].elevatorId;
                            elevatorNum = buildingState.elevators[i].elevatorId;
                            floor = buildingState.floors[z].floorNum;
                            angerDiff = currentAngerDiff;
                            distance = currentDistance;
                        }
                        else if (currentDistance == 0)
                        {
                            elevator = buildingState.elevators[i].elevatorId;
                            elevatorNum = buildingState.elevators[i].elevatorId;
                            angerDiff = currentAngerDiff;
                            distance = currentDistance;
                        }
                    }




                }
            }
        }
     }

    if (currentDistance == 0)
    {
        return "e" + elevator + "p";
    }
    else if (!(buildingState.elevators[elevatorNum].isServicing))
    {
        return "e" + elevator + "f" + floor;
    }
    else
    {
        return "";
    }

    
   
}

string getAIPickupList(const Move& move, const BuildingState& buildingState, 
                       const Floor& floorToPickup) {
    return "";
}



