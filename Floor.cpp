/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Max Victor Sergey Tiernan
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */


#include "Floor.h"

using namespace std;

int Floor::tick(int currentTime) {
    
    int numExploded = 0;
    int a[numPeople];
    int x = 0;
    
    for (int i = 0; i < numPeople; i++){
        if (people[i].tick(currentTime)){
            numExploded++;
            a[x] = i;
            x++;
        }
    }
    removePeople(a, numExploded);
    return numExploded;
}


void Floor::addPerson(Person newPerson, int request) {
    //TODO: Implement addPerson
    
    if (numPeople < MAX_PEOPLE_PER_FLOOR){
        people[numPeople] = newPerson;
        numPeople++;
    }
    
    if (request > 0){
        hasUpRequest = true;
    }
    else if (request < 0){
        hasDownRequest = true;
        }
    }


void Floor::removePeople(int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {

    
    Person array[MAX_PEOPLE_PER_FLOOR];
    int skips = 0;
        
        for (int i = 0; i < numPeopleToRemove; i++)
        {
            for (int j = 0; j < numPeople; j++)
            {
                if (i == indicesToRemove[j])
                {
                    numPeople--;
                }
                for (int k = 0; k < i; k++){
                    if(indicesToRemove[k] < indicesToRemove[i]){
                        skips++;
                    }
                }
                for (int l = indicesToRemove[i]-skips; l <= numPeople; l++){
                    people[l] = people[l+1];
                }
            }
            skips = 0;
        }
    resetRequests();
}




void Floor::resetRequests() {
    int down = 0;
    hasUpRequest = false;
    int up = 0;
    hasDownRequest = false;
    
    for (int i = 0; i < numPeople; i++){
        if (people[i].getTargetFloor() > people[i].getCurrentFloor()){
            down++;
        }
        else if (people[i].getTargetFloor() < people[i].getCurrentFloor()){
            up++;
        }
    
    }
    if (up > 0){
        hasUpRequest = true;
    }
    if (down > 0){
        hasDownRequest = true;
    }
}









//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i){
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
