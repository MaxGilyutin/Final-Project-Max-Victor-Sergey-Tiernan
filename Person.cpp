/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Person.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Max Gilyutin, Victor Diaso, Tiernan Jesrani, Sergey Kislenkov
 * mgily, vjdiaso, tiernanj, skis
 *
 * Final Project - Elevators
 */

#include "Person.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

Person::Person(string inputString) : Person() {
    string str = inputString;
    stringstream ss(str);
    
    char x;

    ss >> turn;
    ss >> x;
    ss >> currentFloor;
    ss >> x;
    ss >> targetFloor;
    ss >> x;
    ss >> angerLevel;
    
}

bool Person::tick(int currentTime) {

    if (currentTime % TICKS_PER_ANGER_INCREASE >= 0){
        angerLevel += 1;
        if (angerLevel >= MAX_ANGER){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
void Person::print(ostream &outs) {    
    
    outs << "f" << currentFloor << "t" << targetFloor << "a" << angerLevel << endl;
    
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Person::Person() {
    turn = 0;
    currentFloor = 0;
    targetFloor = 0;
    angerLevel = 0;
}

int Person::getTurn() const {
    return turn;
}

int Person::getCurrentFloor() const {    
    return currentFloor;
}

int Person::getTargetFloor() const {    
    return targetFloor;
}

int Person::getAngerLevel() const {    
    return angerLevel;
}

ostream& operator<< (ostream& outs, Person p)
{
    p.print(outs);
    return outs;
}
