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
    bool elevator0 = buildingState.elevators[0].isServicing;
    bool elevator1 = buildingState.elevators[1].isServicing;
    bool elevator2 = buildingState.elevators[2].isServicing;
    int closestElevatorTicks = 9;
    int closestElevator = 0;
    int maxPriority;
    int maxAngerLevel = 0;
    int maxPriorityAngerDiff;
    int elevatorTicksPossible;
    if ( elevator0 != true|| elevator1 != true || elevator2 != true){
        for ( int i = 0; i < NUM_FLOORS; i++) {
            for ( int j = 0; j < buildingState.floors[i].numPeople; i++) {
                if (buildingState.floors[i].people[j].angerLevel > maxAngerLevel) {
                    for ( int k = 0; k < NUM_ELEVATORS; k++){
                        elevatorTicksPossible = abs(buildingState.elevators[k].currentFloor - i);
                        if (buildingState.elevators[k].isServicing != true && elevatorTicksPossible < closestElevatorTicks) {
                            closestElevator = k;
                            closestElevatorTicks = elevatorTicksPossible;
                        }
                        maxPriorityAngerDiff = MAX_ANGER - buildingState.floors[i].people[j].angerLevel;
                        if (maxPriorityAngerDiff > elevatorTicksPossible){
                            if ( i == 10) {
                                maxPriority = i - 1;
                            }
                            else {
                                maxPriority = i;
                            }
                        }
                    }
                }
            }
        }
        
        return "e" + to_string(closestElevator) + "f" + to_string(maxPriority);
    }
    else {
        return "";
    }
}

string getAIPickupList(const Move& move, const BuildingState& buildingState, 
                       const Floor& floorToPickup) {
    return "";
}


