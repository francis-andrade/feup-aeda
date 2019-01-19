#include "../Headers/Club.h"
#include "../Headers/menus.h"
#include "../Headers/utilities.h"
#include "../Headers/Date.h"


int main(){
	Club * club=Club::getinstance();//gets new instance of class Vendemaismais
	system(CLEAR);
	if (readplayers() != 0) {
		return 1;//this means that the program caught an exception
	}
	if (club->getleaveprogram()){
		return 1;//leaves the program
	}

	if (readtrainings() != 0) {
		return 1;//this means that the program caught an exception
	}
	if (club->getleaveprogram()){
		return 1;//leaves the program
	}


	if (readtournaments() != 0) {
		return 1;//this means that the program caught an exception
	}
	if (club->getleaveprogram()){
		return 1;//leaves the program
	}

	club->makeTree();//constructs the binary tree that will be used to distribute the monthly prizes
	club->makeQueue();//constructs the queue that will be used to notify the players with the delayed ECG
	initialmenu();//displays the initial menu

	club->writeplayers();//writes players information in the file
	club->writetrainings();//writes trainings information in the file
	club->writetournaments();//writes tournaments information in the file

	system(CLEAR);

	return 0;
}
