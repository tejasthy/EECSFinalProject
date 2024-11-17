/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * Tejas Thiyagarajan, Sindid Ahmed, Ala Abdullah, Mutaz Ismael
 * tejasthy, sindid, alaabdul, mutaz
 *
 * Final Project - Elevators
 */


#include "Floor.h"

using namespace std;

int Floor::tick(int currentTime) {
    bool status[numPeople];
    int exploded[numPeople];
    int k = 0;
    
    for (int i = 0; i < numPeople; i++) {
        bool stati = people[i].tick(currentTime);
        status[i] = stati;
        if (stati) {
            exploded[k++] = i;
        }
    }
    removePeople(exploded, k);
    return k;
}

void Floor::addPerson(Person newPerson, int request) {
    if (MAX_PEOPLE_PER_FLOOR > numPeople) {
        people[numPeople] = newPerson;
        numPeople++;
        if (request > 0) {
            hasUpRequest = true;
        }
        if (request < 0) {
            hasDownRequest = true;
        }
    }
}

void Floor::removePeople(const int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {
    //remove
    Person temp[MAX_PEOPLE_PER_FLOOR];
    int k = 0;
    int tempnumpeople = 0;
    
    for (int i = 0; i < numPeople; i++) {
        bool remove = false;
//        temp[k] = people[i];
//        k++;
        
        for (int j = 0; j < numPeopleToRemove; j++) {
            if (i == indicesToRemove[j]) {
                remove = true;;
                break;
            }
        }
        
        if (!remove) {
            temp[k++] = people[i];
            tempnumpeople++;
        }
    }
    
    for (int i = 0; i < tempnumpeople; i++) {
        if (i < k) {
            people[i] = temp[i];
        }
    }
    
    numPeople = tempnumpeople;
    resetRequests();
}

void Floor::resetRequests() {
    for (int i = 0; i < numPeople; i++) {
        int req = people[i].getTargetFloor() - people[i].getCurrentFloor();
        if (req < 0) {
            hasDownRequest = true;
        }
        else if (req < 0) {
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
