

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h> // srand, rand
#include <time.h> // time
using namespace std;


struct LeagueTeam
{
    string name;
    string town;
    string stadium;
};

struct Match
{
    LeagueTeam home;
    LeagueTeam away;
    bool derby;
    int leg;
};

struct Weekend
{
    Match matches[2];
};


//FUNCTIONS TO BE USED IN PROGRAM
class MyClass {
public:
    void readgivenfile(string);
    void OutputintoFile(string);

    void makeMatches();
    void createWeekendGames();
    void shuffleMatches();
    void sortMatches();

    void showFixtures();
    void showMatches();
    void printTeams();
    int countFixtures();
    int countTeams();

private:
    ifstream inputStream;
    ofstream outputStream;
    vector<LeagueTeam> teams; // List of all teams
    vector<Match> matches; // List of all mathces (90)
    vector<Weekend> weekendGames; // List of all fixtures (45)
    bool havePlayedBefore(LeagueTeam a, LeagueTeam b);

};

//READ DOWNLOADED TEAMS FILE 
void MyClass::readgivenfile(string _dir) {

    inputStream.open(_dir, ios::in);//OPENS THE TEAMS FILE
    string str;
    getline(inputStream, str, '\n');

    while (!inputStream.eof()) {
        string name, town, stadium;        //GETS DATA FROM FILE
        getline(inputStream, name, ',');
        getline(inputStream, town, ',');
        getline(inputStream, stadium, '\n');

        LeagueTeam t;
        t.name = name;
        t.town = town;
        t.stadium = stadium;
        teams.push_back(t);
    }

    inputStream.close();  //CLOSES THE FILE
}






// WRITE RESULTS TO OUTPUT CSV FILE
void MyClass::OutputintoFile(string _dir) {


    if (_dir.length() < 2) {
        _dir = "output.csv";
    }


    outputStream.open(_dir, ios::trunc);          // OPENS THE OUTPUT FILE

    outputStream << "Derby,Game Week,Leg,Home,-,Away,Town,Stadium\n";


    for (int i = 0; i < weekendGames.size(); i++) {
        for (int j = 0; j < 2; j++) {
            string hometeam, awayteam, stadium, town;
            string derby = weekendGames.at(i).matches[j].derby ? "Derby" : "-";
            int leg;

            // Extract fields from list
            hometeam = weekendGames.at(i).matches[j].home.name;
            awayteam = weekendGames.at(i).matches[j].away.name;
            stadium = weekendGames.at(i).matches[j].home.stadium;
            town = weekendGames.at(i).matches[j].home.town;
            leg = weekendGames.at(i).matches[j].leg;

            // Write values to file
            outputStream << derby << "," << i + 1 << "," << leg << "," << hometeam << ",vs," << awayteam << "," << town << "," << stadium << "\n";
        }
    }

    outputStream.close();
}




//PRINTS OUTPUT TO CONSOLE
void MyClass::printTeams() {
    for (int i = 0; i < teams.size(); i++) {
        cout << teams.at(i).name << ",";
        cout << teams.at(i).town << ",";
        cout << teams.at(i).stadium << std::endl;
    }
}





// PAIRS 2 TEAMS TO FORM A MATCH
void MyClass::makeMatches() {
    Match derby;
    for (int i = 0; i < teams.size(); i++) {
        LeagueTeam currentTeam = teams.at(i); // Hold team in a variable
        // Iterate through all teams
        for (int j = 0; j < teams.size(); j++) {
            // If the teams are the same continue iterating
            if (currentTeam.name == teams.at(j).name) {
                continue;
            }
            else
                // If teams are from same town, hold the teams in a temporary derby variable
                if (currentTeam.town == teams.at(j).town) {
                    derby.home = currentTeam;
                    derby.away = teams.at(j);
                    if (havePlayedBefore(currentTeam, teams.at(j))) {
                        derby.leg = 1;
                    }
                    else {
                        derby.leg = 2;
                    }
                    derby.derby = true;
                }
                else {
                    Match match;
                    match.home = currentTeam;
                    match.away = teams.at(j);
                    // Go through all matches checking if both teams have played before
                    if (havePlayedBefore(currentTeam, teams.at(j))) {
                        match.leg = 1;
                    }
                    else {
                        match.leg = 2;
                    }
                    match.derby = false;
                    matches.push_back(match);
                }
        }
        // Add derby match after the current team has already played with all other teams
        matches.push_back(derby);
    }
}





// Print matches to cout
void MyClass::showMatches() {
    for (int i = 0; i < matches.size(); i++) {
        cout << "\n--------------match #" << i + 1 << "--------------\n";
        cout << matches.at(i).home.name << " vs " << matches.at(i).away.name;
        cout << "\n---------------------------------------\n";
    }
}




// Pairs matches ( 2 matches per weekend)
void MyClass::createWeekendGames() {
    for (int i = 0; i < matches.size() - 1; i += 2) {
        Weekend weekend;
        weekend.matches[0] = matches.at(i);
        weekend.matches[1] = matches.at(i + 1);
        weekendGames.push_back(weekend);
    }
}




// Shuffle the generated matches 
void MyClass::shuffleMatches() {


    srand(time(NULL)); // Initialize random seed

    for (int i = matches.size() - 1; i > 0; i--) {
        // Generate random number between 0 and i
        int randomIndex = rand() % i + 0;
        if (randomIndex == i || matches.at(i).derby) {
            continue;
        }
        else {
            std::swap(matches.at(i), matches.at(randomIndex));
        }
    }
}





// Print Weekend games to std::cout
void MyClass::showFixtures() {
    for (int i = 0; i < weekendGames.size(); i++) {
        cout << "|------------ Week #" << i + 1 << " ------------\n\n";
        for (int j = 0; j < 2; j++) {
            cout << "| ";
            cout << weekendGames.at(i).matches[j].home.name;
            cout << " vs ";
            cout << weekendGames.at(i).matches[j].away.name;
            cout << "\n| Stadium: ";
            cout << weekendGames.at(i).matches[j].home.stadium << std::endl;
            cout << "\n";
        }

        cout << "|--------------------------------\n\n";
    }
}





// Check if teams have played each other before 
bool MyClass::havePlayedBefore(LeagueTeam a, LeagueTeam b) {
    // Go through all matches
    for (int i = 0; i < matches.size(); i++) {
        Match currentMatch = matches.at(i);
        // check if a b or b a exists 
        if (
            (currentMatch.home.name == a.name && currentMatch.away.name == b.name)
            ||
            (currentMatch.home.name == b.name && currentMatch.away.name == a.name)
            ) {
            return true;
        }
    }
    return false;
}






// Ensures second legs matches come after all the first legs have been played (Bubble Sort)
void MyClass::sortMatches() {
    for (int i = 0; i < matches.size(); i++) {
        for (int j = 0; j < matches.size() - i - 1; j++) {
            if (matches.at(j).leg > matches.at(j + 1).leg) {
                swap(matches.at(j), matches.at(j + 1));
            }
        }
    }
}


int MyClass::countFixtures() {
    return weekendGames.size();
}


int MyClass::countTeams() {
    return teams.size();
}