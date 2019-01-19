#include "../Headers/Juveniles.h"
#include "../Headers/utilities.h"
#include <fstream>
#include <algorithm>
using namespace std;




/*
*This function adds a new player to the vector of players
*parameter : player - player to be added to the list
*Returns true if insert operation was successfuland false if not
*/
bool Juveniles::addPlayer(Player * player){
	unsigned int age=actualage(player->getBirth());
	if(age>=age_min && age<=age_max){
		Level::addPlayer(player);
		return true;
	}
	else{
		return false;
	}
}

/*
* This function shows the list of players on the screen
*/
void Juveniles::showplayers() const {
	cout << "Juveniles - Players" << endl;
	Level::showplayers();
}

/*
* This function shows the list of trainings on the screen
*/
void Juveniles::showtrainings() const {
	cout << "Juveniles - Trainings" << endl;
	Level::showtrainings();
}

/*
* This function shows the list of tournaments on the screen
*/
void Juveniles::showtournaments() const {
	cout << "Juveniles - Tournaments" << endl;
	Level::showtournaments();
}

/*
*This function returns the score that is going to be used to make the call of the players for a tournament
* parametes: player - player whose score is going to be computed
* return value score of the player
*/
unsigned int Juvenilescallscore(const Player & player) {
	return player.getAssiduity() + 2 * player.getPresences_games() + 4 * player.getPresences_stournaments();
}

/*
*This function compares the scores of two players
*parameters: Player_left, Player_right - players whose score is going to be compared
*return value: true if Player_left score is smaller than Player_right score
*/
bool Juvenilescomp(const Player & Player_left, const Player & Player_right) {
	if (Juvenilescallscore(Player_left) == Juvenilescallscore(Player_right)) {
		return Player_left.getBirth() < Player_right.getBirth();
	}
	else {
		return Juvenilescallscore(Player_left) > Juvenilescallscore(Player_right);
	}
}

/*
* This function makes the call for a major tournament
*parameter: size - number of players that are going to be called
* Return value: vector with the names of the players that are going to be called
*/
vector<string> Juveniles::getCall(unsigned int size) {
	vector<Player *> vector_players_pointers = this->getPlayers();//vector of pointers to players
	vector<Player> vector_players;//vector of players
	for (unsigned int i = 0; i < vector_players_pointers.size(); i++) {
		vector_players.push_back(*vector_players_pointers[i]);
	}
	sort(vector_players.begin(), vector_players.end(), Juvenilescomp);
	vector<string> names;//vector with the names of the players
	unsigned int counter = 0;//counts the number of players in the vector
	Date current_date;//current date
	for (unsigned int i = 0; i<vector_players.size() && counter<size; i++) {
		if (vector_players[i].checkECG(current_date)) {
			names.push_back(vector_players[i].getName());
			counter++;
		}
	}
	return names;
}