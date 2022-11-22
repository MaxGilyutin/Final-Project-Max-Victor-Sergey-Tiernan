/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Max Gilyutin, Victor Diaso, Tiernan Jesrani, Sergey Kislenkov
 * mgily, vjdiaso, tiernanj, skis
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {
    //TODO: Implement non-default constructor
    string str = commandString;
    stringstream ss(str);

    char x;

    if (str.size() == 0)
    {
        isPass == true;
    }
    else if (str.size() == 1)
    {
        if (str == "Q" || str == "q")
        {
            isQuit = true;
        }
        else if (str == "S" || str == "s")
        {
            isSave = true;
        }
    }
    else if (str.size() == 3)
    {
        ss >> x;
        ss >> elevatorId;
        ss >> x;
        isPickup = true;
    }
    else if (str.size() == 4)
    {
        ss >> x;
        ss >> elevatorId;
        ss >> x;
        ss >> targetFloor;
    }



   


}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    //TODO: Implement isValidMove
    if (isPass || isSave || isQuit)
    {
        return true;
    }
    else if (isPickup)
    {
        if (elevatorId >= 0 && elevatorId < NUM_ELEVATORS &&
            elevators[elevatorId].isServicing() == false)
        {
            return true;
        }
        
    }
    else if (elevatorId >= 0 && elevatorId < NUM_ELEVATORS &&
        elevators[elevatorId].isServicing() == false)
    {
        if (targetFloor >= 0 && targetFloor < NUM_FLOORS &&
            targetFloor != elevators[elevatorId].getCurrentFloor())
        {
            return true;
        }
        
    }
        

    //Returning false to prevent compilation error
    return false;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    //TODO: Implement setPeopleToPickup
   
    for (int i = 0; i < pickupList.size(); i++)
    {
        peopleToPickup[i] = pickupList.at(i) - '0';
        numPeopleToPickup++;
        totalSatisfaction += (MAX_ANGER - pickupFloor.getPersonByIndex(peopleToPickup[i]).getAngerLevel());

        
    }

    targetFloor = pickupFloor.getPersonByIndex(peopleToPickup[0]).getTargetFloor();
    int floorDiff = abs(currentFloor - targetFloor);

    for (int i = 1; i < pickupList.size(); i++)
    {
        if (abs(currentFloor - pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor()) > floorDiff)
        {
            targetFloor = pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor();
            floorDiff = abs(currentFloor - targetFloor);

        }
    }

}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
