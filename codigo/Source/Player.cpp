#include "../Headers/Player.h"
#include <iostream>
#include"../Headers/utilities.h"
#include<iomanip>
#include <algorithm>
using namespace std;


/*
* This function adds an ECG to the list
* parameter: ecg_date - date of the ecg that is going to be added to the list
*/
void Player::addECG(Date ecg_date) {
	ecg.push_back(ecg_date);
	sort(ecg.begin(), ecg.end());
}

/*
*This function prints the player on the screen
*/
void Player::show() const {
	cout << setw(20) << name << "|";
	cout << "     ";
	birth.show();
	cout << "|     ";
	this->getLast_Eletro().show();
	cout << "|";
	cout << setw(10) << height<<"|";
	cout << setw(8) << assiduity << " |" << setw(7) << presences_games << " |" << setw(10) << presences_stournaments;
}


/*
* This returns the date of the last electrocardiogram
* Return value: Date when the player had his last ecg
*/
Date Player::getLast_Eletro() const {
	if (ecg.size() == 0) {
		return Date(0, 0, 0);
	}
	else {
		return ecg[ecg.size() - 1];
	}
}

/*
* This function checks if a certain player had their ECG in order in a certain date
* The ECG is in order if the player had at least one exam between the date of his last birthday and the date of his penultimante birthday
* parameter: date - date when  this function is going to check if the ECG is in order
* Return value: true if the ECG is in order, false otherwise
*/
bool Player::checkECG(const Date & date) const {
	Date last_birthday(0, 0, 0);//date when the player had his last birthday
	if (date >= birth.year_date(date.getYear())) {
		last_birthday = birth.year_date(date.getYear());
	}
	else {
		last_birthday = birth.year_date(date.getYear()-1);
	}
	Date penultimate_birthday(0, 0, 0);//date when the player had his penultimate birthday
	penultimate_birthday = birth.year_date(last_birthday.getYear() - 1);

	for (unsigned int i = 0; i < ecg.size(); i++) {
		if ((penultimate_birthday <= ecg[i]) && (ecg[i] <= date)) {
			return true;
		}
	}
	return false;
}

/*
parameter: ostream & out - ostream where player is going to be written
parameter: const Player & player - player
Writes the player passed as a parameter in out
*/
ostream & operator<<(ostream& out, const Player & player){
	out << player.name << " ; " << player.birth << " ; ";
	out << player.ecg.size() << " ; ";
	for (unsigned int i = 0; i < player.ecg.size(); i++) {
		out << player.ecg[i] << " ; ";
	}
	out<<player.got_present<<" ; ";
	out<<player.height<<" ; ";
	out<<player.assiduity<<" ; "<<player.presences_games<<" ; "<<player.presences_stournaments;
	return out;
}
/*
parameter: istream & in - istream from where date is going to be read
parameter: Date & date - variable where the date extracted from stream is going to be stored
Reads date from istream
*/
istream& operator>>(istream& in, Player & player){
	char semicolon;//semicolon that exists in the file
	string name;//name of the player
	getline(in, name ,';');
	player.name=removespaces(name);
	in>>player.birth;
	in>>semicolon;
	unsigned int ecg_size;//size of ecg size
	in >> ecg_size;
	in >> semicolon;
	for (unsigned int i = 0; i < ecg_size; i++) {
		Date ecg_date(0, 0, 0);
		in >> ecg_date;
		player.ecg.push_back(ecg_date);
		in >> semicolon;
	}
	in>>player.got_present;
	in>>semicolon;
	in>>player.height;
	in>>semicolon;
	in>>player.assiduity;
	in>>semicolon;
	in>>player.presences_games;
	in>>semicolon;
	in>>player.presences_stournaments;
	return in;
}


/*
* This function compares two differente player nodes
* Returns true if pl_left has a better record than pl_right
*/
bool operator<(const Player_node & pl_left, const Player_node & pl_right) {
	if ((pl_left.player->getAssiduity_Curr_Month() + pl_left.player->getGames_Won()) == (pl_right.player->getAssiduity_Curr_Month() + pl_right.player->getGames_Won())) {
		return pl_left.player->getName() < pl_right.player->getName();
	}
	else {
		return pl_left.player->getAssiduity_Curr_Month() + pl_left.player->getGames_Won() > pl_right.player->getAssiduity_Curr_Month() + pl_right.player->getGames_Won();
	}
}

/*
* This function compares two different player queues
* Returns true if pl_left is younger than p_right
*/
bool operator<(const Player_queue & pl_left, const Player_queue & pl_right) {
	if (pl_left.player->getBirth() == pl_right.player->getBirth()) {
		return pl_left.player->getName() < pl_right.player->getName();
	}
	else {
		return pl_left.player->getBirth() < pl_right.player->getBirth();
	}
}
