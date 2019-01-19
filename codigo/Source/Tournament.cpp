#include "../Headers/Tournament.h"
#include "../Headers/utilities.h"
#include <iomanip>

using namespace std;


/*
*Copy constructor
*/
Tournament::Tournament(const Tournament & tournament) :Event(tournament) {
	this->major = tournament.major;
	this->rank = rank;
	this->results = results; };

/*
*copy assignement operator
*/
Tournament & Tournament::operator=(const Tournament & tournament) {
	Event::operator=(tournament);
	this->major = tournament.major;
	this->rank = rank;
	this->results = results;
	return *this;
};

/*
*constructor with pointer
*/
Tournament::Tournament(Event * ev) :Event(*ev) {
	this->major = ev->isMajor();
	this->rank = ev->getRank();
	this->results = ev->getResults();
};

/*
*Prints tournament on the screen
*/

void Tournament::show() const {
	(this->getDay()).show();
	cout << "| ";
	if (major) {
		cout << "      Yes       |";
	}
	else {
		cout << "      No        |";
	}
	cout << setw(7) << rank <<"|"<< setw(14) << results.size()<<"|";
	vector<string> vector_presences = this->getPresences();
	cout << setw(12) << vector_presences.size();
}

/*
parameter: ostream & out - ostream where tournament is going to be written
parameter: const Tournament & tournament - tournament
Writes the tournament passed as a parameter in out
*/
ostream & operator<<(ostream& out, const Tournament & tournament){
	out << tournament.getDay() << " ; " << tournament.major << " ; " << tournament.rank << " ; ";
	out<<(tournament.results).size()<<" ; ";
	for(unsigned int i=0;i<(tournament.results).size();i++){
		out<<tournament.results[i].first.first<<" ";
		out<<tournament.results[i].first.second<<" ";
		out << tournament.results[i].second << ";";
	}
	vector<string> presences = tournament.getPresences();
	out << presences.size() << " ; ";
	for (unsigned int i = 0; i < presences.size(); i++) {
		out << presences[i] << " ; ";
	}
	return out;
}
/*
parameter: istream & in - istream from where tournament is going to be read
parameter: Tournament & tournament - variable where the tournament extracted from stream is going to be stored
Reads tournament from istream
*/
istream & operator>>(istream& in, Tournament & tournament){
	char semicolon;//semicolon that exists in the file
	Date date_day(0,0,0);
	in>>date_day;
	tournament.setDay(date_day);
	in>>semicolon;
	in>>tournament.major;
	in>>semicolon;
	in>>tournament.rank;
	in>>semicolon;
	unsigned int size;
	in>>size;
	in >> semicolon;
	tournament.results.clear();
	for(unsigned int i=0;i<size;i++){
		pair<pair<unsigned int, unsigned int> , string> game;
		in >> game.first.first >> game.first.second;
		getline(in,game.second, ';');
		tournament.results.push_back(game);
	}

	unsigned int n_presences;
	in >> n_presences;
	in >> semicolon;
	for (unsigned int i = 0; i < n_presences; i++) {
		string player_name;
		getline(in, player_name, ';');
		tournament.addPresence(removespaces(player_name));
	}
	return in;
}
