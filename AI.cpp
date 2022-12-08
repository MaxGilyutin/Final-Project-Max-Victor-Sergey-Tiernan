/*
 * Copyright 2022 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Max Gilyutin, Victor Diaso, Tiernan Jesrani, Sergey Kislenkov
 * mgily, vjdiaso, tiernanj, skis
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include "Person.h"
#include <cassert>

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core


string getAIMoveString(const BuildingState& buildingState) {
    
    //checks if the elevators are servicing
    bool e0 = buildingState.elevators[0].isServicing;
    bool e1 = buildingState.elevators[1].isServicing;
    bool e2 = buildingState.elevators[2].isServicing;
    
    // returns Enter if all elevators are servicing
    if(e0 && e1 && e2){
        return "";
    }
    
    int sumPeople = 0;
    for(int i = 0; i < NUM_FLOORS; i++){
        sumPeople += buildingState.floors[i].numPeople;
    }
    if(sumPeople == 0){
        return "";
    }
    
    int floorVal = 0;
    //goes through elevators, tells it to pickup if the floor matches the elevator
    for(int i = 0; i < NUM_ELEVATORS; i++){
        floorVal = buildingState.elevators[i].currentFloor;
        
        if(buildingState.elevators[i].targetFloor == buildingState.elevators[i].currentFloor && buildingState.floors[floorVal].numPeople > 0){
            return "e" + to_string(i) + "p";
        }
    }
    
    // First, find the closest elevator for each floor
    //  There are 10 array slots, with 3 possibilities for elevators
    int floorClosestElevators[10] = {0};
    int difference1 = 999;
    int difference2 = 999;
    int difference3 = 999;
    
    // Fills out array with closest elevators
    //Go through the FLOORS
    for(int i = 0; i < 10; i++){
        //Go through the ELEVATORS
        if(!buildingState.elevators[0].isServicing){
            //takes distance from elevator to floor
            difference1 = abs(buildingState.elevators[0].currentFloor - i);
            floorClosestElevators[i] = 0;
        }
        if(!buildingState.elevators[1].isServicing){
            //takes distance from elevator to floor
            difference2 = abs(buildingState.elevators[1].currentFloor - i);
            if(difference2 < difference1){
                floorClosestElevators[i] = 1;
            }
        }
        if(!buildingState.elevators[2].isServicing){
            difference3 = abs(buildingState.elevators[2].currentFloor - i);
            if(difference3 < difference2 && difference3 < difference1){
                floorClosestElevators[i] = 2;
            }
        }
    }
    
    int distance = 0;
    
    //Creates an array that will keep track of all the score potentials of a floor
    int floorScores[10] = {0};
    //Variable for keeping track of the score for the floor
    int sum = 0;
    // Runs through floor
    for(int i = 0; i < 10; i++){
        // Runs through people on the floor
        for(int j = 0; j < buildingState.floors[i].numPeople; j++){
            sum += (10 - buildingState.floors[i].people[j].angerLevel);
        }
        
        //calculates how far the closest elevator has to travel to reach the floor
        distance = abs(buildingState.elevators[floorClosestElevators[i]].currentFloor - i);
        //from the sum, subtracts the anger that will accumulate while the elevator is traveling
        sum -= buildingState.floors[i].numPeople * distance;
        
        floorScores[i] = sum;
        
        sum = 0;
    }
    
    //sets the bestFloor to target to the one with the greatest floorScore
    int bestFloor = 0;
    for(int i = 0; i < 10; i++){
        if(floorScores[i] > floorScores[bestFloor]){
            bestFloor = i;
        }
    }
    
    int bestElevator = floorClosestElevators[bestFloor];
    //only return if the target floor has people
    if(buildingState.floors[bestFloor].numPeople > 0){
        return "e" + to_string(bestElevator) + "f" + to_string(bestFloor);
    }else{
        return "";
    }
    
    
    
}

string getAIPickupList(const Move& move, const BuildingState& buildingState,
                       const Floor& floorToPickup) {
    
    int countUp = 0;
    int countDown = 0;
    int angerUp = 0;
    int angerDown = 0;
    bool up = false;
    bool down = false;
    string dropOff = "";
    
    for (int i = 0; i < floorToPickup.getNumPeople(); i++){
        if (floorToPickup.getPersonByIndex(i).getTargetFloor() > floorToPickup.getPersonByIndex(i).getCurrentFloor()){
            countUp++;
            angerUp += (10 - floorToPickup.getPersonByIndex(i).getAngerLevel());
            
        }
        else if (floorToPickup.getPersonByIndex(i).getTargetFloor() < floorToPickup.getPersonByIndex(i).getCurrentFloor()){
            countDown++;
            angerDown += (10 - floorToPickup.getPersonByIndex(i).getAngerLevel());
        }
    }
    
    angerUp *= countUp;
    angerDown *= countDown;
    
    if (angerUp >= angerDown){
        up = true;
    }
    else if (angerDown > angerUp){
        down = true;
    }
    
    for (int j = 0; j < floorToPickup.getNumPeople(); j++){
        if (floorToPickup.getPersonByIndex(j).getTargetFloor() > floorToPickup.getPersonByIndex(j).getCurrentFloor() && up){
            dropOff += to_string(j);
            
        }
        else if (floorToPickup.getPersonByIndex(j).getTargetFloor() < floorToPickup.getPersonByIndex(j).getCurrentFloor() && down){
            dropOff += to_string(j);

        }
    }
        
        
    return dropOff;
}
