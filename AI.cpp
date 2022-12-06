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
    int maxPriority;
    int maxAngerLevel = 0;
    for ( int i = 0; i < NUM_FLOORS; i++) {
        for ( int j = 0; j < buildingState.floors[i].numPeople; i++) {
            if (buildingState.floors[i].people[j].angerLevel > maxAngerLevel) {
                maxPriority = i;
            }
        }
    }
    
    /*if ( buildingState.elevators[0].isServicing != true) {
        return "";
    }
    if (buildingState.elevators[1].isServicing != true) {
        return "";
    }
    if ( buildingState.elevators[2].isServicing != true) {
        return "";
    }
     */
    return "";
}

string getAIPickupList(const Move& move, const BuildingState& buildingState, 
                       const Floor& floorToPickup) {
    return "";
}


