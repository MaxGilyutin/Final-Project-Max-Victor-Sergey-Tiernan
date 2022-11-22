/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Max Gilyutin, Victor Diaso, Tiernan Jesrani, Sergey Kislenkov
 * mgily, vjdiaso, tiernanj, skis
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


//Modifies: people[], numPeople, hasUpRequest, hasDownRequest
void Floor::removePeople(int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {

    //sort indicesToRemove array
    sort(indicesToRemove, indicesToRemove + numPeopleToRemove);
    
    int countRemoved = 0;
    
    for(int i = 0; i < numPeople; i++){
        if(i != indicesToRemove[countRemoved]){
            people[i-countRemoved] = people[i];
        }else{
            countRemoved++;
        }
    }
    
    numPeople = numPeople - numPeopleToRemove;
    resetRequests();
}




void Floor::resetRequests() {
    hasUpRequest = false;
    hasDownRequest = false;
    
    for (int i = 0; i < numPeople; i++){
        if(people[i].getTargetFloor() > people[i].getCurrentFloor()){
            hasUpRequest = true;
        }
        else if(people[i].getTargetFloor() < people[i].getCurrentFloor()){
            hasDownRequest = true;
        }
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
