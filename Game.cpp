/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Game.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Max Gilyutin, Victor Diaso, Tiernan Jesrani, Sergey Kislenkov
 * mgily, vjdiaso, tiernanj, skis
 *
 * Final Project - Elevators
 */
 
#include <random>
#include <sstream>
#include "Game.h"
#include "AI.h"
#include "Utility.h"
using namespace std;

// Stub for playGame for Core, which plays random games
// You *must* revise this function according to the RME and spec

void Game::playGame(bool isAIModeIn, ifstream& gameFile) {
    
    if(!gameFile.is_open()){
        exit(1);
    }

    //load and prepare all the data for the game loop
    isAIMode = isAIModeIn;
    printGameStartPrompt();
    initGame(gameFile);
    
    string line;
    Person p;
    Person firstPerson;
    Move nextMove;
    
    //makes it so any earlier entries in game.in don't screw up the actual entries
    getline(gameFile, line);
    while(line.length() < 7){
        getline(gameFile, line);
        if(line.length() >= 7){
            firstPerson = Person(line);
            break;
        }
    }
    
    //makes sure the first person works
    if(firstPerson.getTurn() <= building.getTime()){
        building.spawnPerson(firstPerson);
    }else{
        building.prettyPrintBuilding(cout);
        satisfactionIndex.printSatisfaction(cout, false);
        checkForGameEnd();
        nextMove = getMove();
        update(nextMove);
        building.spawnPerson(firstPerson);
    }
    
    while (true) {
           
        while(getline(gameFile, line)){
            p = Person(line);
            
            if(p.getTurn() <= building.getTime()){
                building.spawnPerson(p);
                
            }else{
                building.prettyPrintBuilding(cout);
                satisfactionIndex.printSatisfaction(cout, false);
                checkForGameEnd();
                nextMove = getMove();
                update(nextMove);
                building.spawnPerson(p);
            }
            
        }
        
        building.prettyPrintBuilding(cout);
        satisfactionIndex.printSatisfaction(cout, false);
        checkForGameEnd();
        nextMove = getMove();
        update(nextMove);
        
    }
}

// Stub for isValidPickupList for Core
// You *must* revise this function according to the RME and spec
bool Game::isValidPickupList(const string& pickupList, const int pickupFloorNum) const {
    
    //  Makes sure the list doesn't exceed elevator capacity
    if(pickupList.length() > ELEVATOR_CAPACITY){
        return false;
    }
    // Makes sure no repeats are present
    for(int i = 0; i < pickupList.length()-1; i ++){
        for(int j = i+1; j < pickupList.length(); j++){
            if(pickupList.at(i) == pickupList.at(j)){
                return false;
            }
        }
    }
    
    // Runs through string, makes sure all are positive
    // integer 'n' is used in the following sequences
    // of code to convert elements of pickupList into
    // integers
    int n = 0;
    
    for(int i = 0; i < pickupList.length(); i++){
        n = pickupList.at(i) - '0';
        if(n < 0){
            return false;
        }
    }
    
    //Makes sure all the pickups are heading in the same direction
    //TO DO: IMPLEMENT
    //
    int currentPerson = pickupList.at(0) - '0';
    
    if(building.getFloorByFloorNum(pickupFloorNum).getPersonByIndex(currentPerson).getTargetFloor() > pickupFloorNum){
        for(int i = 1; i < pickupList.length(); i++){
            currentPerson = pickupList.at(i) - '0';
            if(building.getFloorByFloorNum(pickupFloorNum).getPersonByIndex(currentPerson).getTargetFloor() < pickupFloorNum){
                return false;
            }
            
        }
    }
    
    currentPerson = pickupList.at(0) - '0';
    
    if(building.getFloorByFloorNum(pickupFloorNum).getPersonByIndex(currentPerson).getTargetFloor() < pickupFloorNum){
        for(int i = 1; i < pickupList.length(); i++){
            currentPerson = pickupList.at(i) - '0';
            if(building.getFloorByFloorNum(pickupFloorNum).getPersonByIndex(currentPerson).getTargetFloor() > pickupFloorNum){
                return false;
            }
            
        }
    }
    
    
    //The maximum value pointed to by an index of pickupList must be strictly less than the number of people on the floor pointed to by pickupFloorNum
    int max = 0;
    for(int i = 0; i < pickupList.length(); i++){
        n = pickupList.at(i) - '0';
        if(n > max){
            max = n;
        }
    }
    // returns false if an index of pickupList exceeds the number
    // of people on that floor
    if(max >= building.getFloorByFloorNum(pickupFloorNum).getNumPeople()){
        return false;
    }
    if(building.getFloorByFloorNum(pickupFloorNum).getNumPeople() == 0 && pickupList.length() != 0){
        return false;
    }
    
    
    return true;
}


//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

bool Game::performMove(Move& move) const
{
    Elevator elevators[NUM_ELEVATORS];

    for (int i = 0; i < NUM_ELEVATORS; ++i)
    {
        elevators[i] = building.getElevatorById(i);
    }

    if (move.isValidMove(elevators) && move.isPickupMove())
    {

        Elevator taggedElevator = building.getElevatorById(move.getElevatorId());
        Floor taggedFloor = building.getFloorByFloorNum(taggedElevator.getCurrentFloor());

        if (taggedFloor.getNumPeople() > 0)
        {
            getPeopleToPickup(move);
            return true;
        }

        return false;
    }
    else if (move.isSaveMove())
    {
        performSave();
    }
    else if (move.isQuitMove())
    {
        performQuit();
    }
    else if (!move.isValidMove(elevators))
    {
        return false;
    }

    return true;
}

void Game::printWelcomeMenu() const
{
    cout << "########################################" << endl;
    cout << "# Welcome to EECS 183 Elevator Escape! #" << endl;
    cout << "########################################" << endl
        << endl;
}

void Game::printIntroMenu() const
{
    cout << "[0] Run Tests" << endl;
    cout << "[1] Load saved game" << endl;
    cout << "[2] Start new game" << endl;
    cout << "Choice: ";
}

void Game::printAIMenu() const {
    cout << "[1] Play as human" << endl;
    cout << "[2] Watch AI play" << endl;
    cout << "Choice: ";
}

void Game::printOptions() const
{
    cout << "########################################" << endl;
    cout << "#         Enter service move:          #" << endl;
    cout << "#     'e' elevatorId 'f' floorNum      #" << endl;
    cout << "#            Or pickup move:           #" << endl;
    cout << "#          'e' elevatorId 'p'          #" << endl;
    cout << "########################################" << endl;
}

void Game::printGameStartPrompt() const
{
    cout << endl;
    cout << "########################################" << endl;
    cout << "#                 Enter:               #" << endl;
    cout << "#               Q to Quit              #" << endl;
    cout << "#               S to Save              #" << endl;
    cout << "#      At any time after this prompt   #" << endl;
    cout << "########################################" << endl;
    cout << endl;
    cout << "Press enter to continue....";

    string trash;
    getline(cin, trash);
    cout << endl;
}

IntroChoice Game::getIntroChoice() const {

    if (IS_AI_OVERRIDE) {
        return IntroChoice::New;
    }

    int choice = -1;

    while ((choice < 0) || (choice > 2))
    {
        printIntroMenu();
        string s_choice;
        getline(cin, s_choice);
        choice = stoi(s_choice);

        if ((choice < 0) || (choice > 2))
        {
            cout << endl
                << "Invalid menu choice!" << endl
                << endl;
        }
    }

    cout << endl;

    return static_cast<IntroChoice>(choice);
}

AIChoice Game::getAIChoice() const {
    if (IS_AI_OVERRIDE) {
        return AIChoice::AI;
    }

    int choice = 0;
    printAIMenu();
    string s_choice;
    getline(cin, s_choice);
    choice = stoi(s_choice);
    while (choice != 1 && choice != 2) {
        cout << endl << "Invalid menu choice!" << endl << endl;
        getline(cin, s_choice);
        choice = stoi(s_choice);
    }

    cout << endl;

    return static_cast<AIChoice>(choice);
}

void Game::printSatisfactionIndex() const
{
    cout << endl
        << endl;
    cout << "Your hotel's current satisfaction index is: " << satisfactionIndex;
    cout << endl
        << endl;
}

void Game::getPeopleToPickup(Move& move) const
{
    int currentFloorNum = building.getElevatorById(move.getElevatorId()).getCurrentFloor();
    Floor currentFloor = building.getFloorByFloorNum(currentFloorNum);

    if (currentFloor.getNumPeople() == 1)
    {
        move.setPeopleToPickup("0", currentFloorNum, currentFloor);
        return;
    }

    string peopleIndices = "";
    bool isValidPickup = false;

    while (!isValidPickup)
    {

        currentFloor.printFloorPickupMenu(cout);
        cout << endl;
        cout << "Choices: ";
        getline(cin, peopleIndices);
        cout << "\n";

        if (isAIMode) {
            Elevator e = building.getElevatorById(move.getElevatorId());
            Floor f = building.getFloorByFloorNum(e.getCurrentFloor());
            peopleIndices = getAIPickupList(move, building.getBuildingState(), f);
            cout << "AI OVERRIDE: " << peopleIndices << endl;
        }

        isValidPickup = isValidPickupList(peopleIndices, currentFloorNum);

        if (!isValidPickup)
        {
            cout << "Invalid list of people chosen!" << endl;
            checkForGameEnd();
        }
    }

    move.setPeopleToPickup(peopleIndices, currentFloorNum, currentFloor);
}

Move Game::getMove() const
{
    Move moveObj;
    string moveString = "";
    bool isValid = false;
    GameChoice choiceCapture = GameChoice::Invalid;

    do
    {
        cout << "Enter move: ";

        getline(cin, moveString);
        cout << "\n";

        if (isAIMode) {
            moveString = getAIMoveString(building.getBuildingState());
            cout << "AI OVERRIDE: " << moveString << endl;
        }
        moveObj = Move(moveString);
        choiceCapture = static_cast<GameChoice>(moveString[0]);

        switch (choiceCapture)
        {
        case GameChoice::Quit:
            performQuit();
            break;
        case GameChoice::Save:
            isValid = performSave();
            break;
        case GameChoice::Pass:
        case GameChoice::Move:
            isValid = performMove(moveObj);
            break;
        default:
            isValid = false;
            break;
        }

        if (!isValid)
        {
            cout << endl
                << "Invalid move!" << endl
                << endl;
            checkForGameEnd();
        }

    } while (!isValid);

    return moveObj;
}

void Game::performQuit() const
{
    QuitChoice quitChoice = static_cast<QuitChoice>(getExitChoice());
    switch (quitChoice)
    {
    case QuitChoice::Quit:
        endGame();
        break;
    case QuitChoice::Stay:
        return;
        break;
    }
}

bool Game::performSave() const
{
    ofstream saveFile(LOAD_FILENAME);
    if (!saveFile.is_open())
    {
        cout << "Could not open " << LOAD_FILENAME << endl;
        return false;
    }
    return saveGame(saveFile);
}

void Game::initGame(ifstream& loadFile)
{
    cout << endl
        << "Loading game..." << endl;

    loadFile >> satisfactionIndex;

    int tempTime;
    loadFile >> tempTime;

    building.setTime(tempTime);

    string elvState;
    for (int i = 0; i < NUM_ELEVATORS; i++)
    {
        loadFile >> elvState;
        building.setElevator(elvState, i);
    }

    cout << "Loaded!" << endl
        << endl;
}

void Game::printExitMenu() const
{
    cout << endl;
    cout << "Are you sure you want to quit?" << endl;
    cout << "[1] Yes, I'm sure!" << endl;
    cout << "[2] No, keep playing!" << endl;
    cout << "Choice: ";
}

int Game::getExitChoice() const
{
    int exitChoice = 0;

    while ((exitChoice < 1) || (exitChoice > 2))
    {
        printExitMenu();

        string choice = "";
        getline(cin, choice);
        exitChoice = stoi(choice);

        if ((exitChoice < 1) || (exitChoice > 2))
        {
            cout << endl
                << "Invalid menu choice!" << endl
                << endl;
        }
    }
    cout << endl;

    return exitChoice;
}

void Game::endGame() const
{
    cout << endl
        << "Goodbye!" << endl;
    satisfactionIndex.save();
    exit(0);
}

void Game::printSuccessEnding() const
{
    cout << endl
        << endl;
    cout << "Time is up! Your final score is: " << endl;
    satisfactionIndex.printSatisfaction(cout);
}

void Game::printFailureEnding() const
{
    cout << endl
        << endl;
    cout << "Uh oh! Your hotel has gone out of business!" << endl;
    cout << "Better luck next time!" << endl
        << endl;
    cout << "Your final achievement:" << endl
        << endl;
    satisfactionIndex.printSatisfaction(cout);
}

void Game::checkForGameEnd() const
{
    if (building.getTime() >= MAX_TURNS)
    {
        printSuccessEnding();
        endGame();
    }
    else if (satisfactionIndex.getSatisfaction() < 0)
    {
        printFailureEnding();
        endGame();
    }
}

void Game::update(const Move& m)
{
    if (m.isPickupMove())
    {
        satisfactionIndex.updateSumDirectionRequest(m, building);
    }
    satisfactionIndex.updateSumExploded(building.tick(m));
    satisfactionIndex.updateTimeReached(building);
    if (building.getTime() % 2)
    {
        satisfactionIndex.updateSumIdle(building);
    }
}

// Stub for saveGame for project
// You will *not* implement this function for the project
bool Game::saveGame(ofstream& saveFile) const {
    return true;
}
