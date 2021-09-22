#include <iostream>
#include <string>
#include "header.h"
#include <Windows.h>

using namespace std;

void firstPage(MyClass& util) {
	
	cout << "________________________________________________________________________________________________________________________\n";
	cout << "                                                      FIXTURE CREATOR 2020                                                                             \n\n";
	cout << "                                                       HACKATHON PROJECT                                                                           \n";
	cout << "________________________________________________________________________________________________________________________\n";

	cout << "                       THIS IS A PROGRAM TO GENERATE FIXTURES FOR THE CURRENT ABC PREMIER LEAGUE SEASON\n\n\n";

	cout << "Follow the instructions provided below in order to generate the required fixtures.\n\n";
	cout << "                                                               **DISCLAIMER**                                                                                             \n";
	cout << "                                            OUTPUT WILL ONLY BE RECEIVED IF INSTRUCTIONS ARE STRICTLY FOLLOWED                                                          \n\n";
	cout << "Enter step 1 in order to read the file containing the TEAMS, their LOCAL TOWNS and STADIUMS.\n";
	cout << "- 1. READ FILE (" << util.countTeams() << " Teams loaded)                                \n\n";
	cout << "-                                                                        -\n";
	cout << "After entering choice 1, enter 2 in order to create the fixtures.\n";
	cout << "- 2. CREATE FIXTURES (" << util.countFixtures() << " Fixtures generated)                             -\n\n";
	cout << "-                                                                        -\n";
	cout << "Next enter step 3 in order to generate the cvs file containing the fixtures\n";
	cout << "- 3. GENERATE CVS FIXTURE FILE                                                     -\n\n";
	cout << "-                                                                        -\n";	
	cout << "-                                                                        -\n";
	cout << "- Enter step : ";
}

int main() {
	SetConsoleTitle(L"Fixtures Generator");


	MyClass header;
	int step = 0;
	string cvsFilePath;



	while (step != 5) {
		firstPage(header);
		cin >> step;
		switch (step)
		{
		case 1:
			if (header.countTeams() <= 0) {
				cout << "- \n- Enter the path of the file containing the teams removing the apostrophe marks. (include extension e.g file.csv)\n- \n- ";
				cin >> cvsFilePath;
				header.readgivenfile(cvsFilePath);
				cout << "\n- " << header.countTeams() << " teams have been read from " << cvsFilePath << "\n\n";
			}
			break;
		case 2:
			if (header.countFixtures() <= 0) {
				header.makeMatches();
				header.shuffleMatches();
				header.sortMatches();
				header.createWeekendGames();
				cout << "\n- " << header.countFixtures() << " fixtures have been generated \n\n";
			}
			break;
		case 3:
			header.OutputintoFile("output.csv");
			cout << "Opening generated Fixtures \n";
			system("start output.csv");
			header.showFixtures();
			break;
		
		default:
			break;
		}
		system("pause");
		system("cls");
	}



	cout << "bye\n";
	return 0;
}