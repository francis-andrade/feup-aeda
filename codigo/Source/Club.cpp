#include "../Headers/Club.h"

using namespace std;

Club * Club::singleton_instance = NULL; //Initially singleton_instance points to null

/*
 * Private Default Constructor
 */
Club::Club() :
		minis(new Minis()), juveniles(new Juveniles()), juniors(new Juniors()), seniors(
				new Seniors()){
	leaveprogram = false;

}

/*
 *Private Destructor
 */
Club::~Club() {
	delete minis;
	delete juveniles;
	delete juniors;
	delete seniors;
	delete singleton_instance;
	singleton_instance = NULL;
}

/*
 Gets instance of Club Class
 */
Club * Club::getinstance() {
	if (!singleton_instance) {
		singleton_instance = new Club;
	}
	return singleton_instance;
}

/*
 *Reads players file
 *parameter: in - file where the players information is written
 */
void Club::readplayers(istream &in) {
	unsigned int size;
	//READ CURRENT PLAYERS
	in >> size;
	for (unsigned int i = 0; i < size; i++) {
		Player *p = new Player; //new player to be added to the list of players
		in >> (*p);
		if (!minis->addPlayer(p) && !juveniles->addPlayer(p) && !juniors->addPlayer(p) && !seniors->addPlayer(p))
			if (!addBirthday(p))
				throw InvalidPlayer(p->getName(), p->getBirth());


	}
	//READ OLD PLAYERS
	in >> size;
	for (unsigned int i = 0 ; i < size ; i++){
		Player *p = new Player;
		in >> (*p);
		if (!addBirthday(p))
			throw InvalidPlayer(p->getName(), p->getBirth());
	}

}
/*
 *Reads trainings file
 *parameter: in - file where the trainings information is written
 */
void Club::readtrainings(istream &in) {
	string club_name;//name of the club;
	in >> club_name;
	name = club_name;
	string level_name; //name of the level that is written in the file
	string coach_name; //coach name for each category
	int n_trainings; //number of trainings for each level
	in >> level_name;
	in.ignore();//extracts the end of line
	getline(in, coach_name);
	minis->setCoach(removespaces(coach_name));
	in >> n_trainings;
	for (int i = 0; i < n_trainings; i++) {
		Training *t = new Training;
		in >> (*t);
		minis->addEvent(t);
	}

	in >> level_name;
	in.ignore();//extracts the end of line
	getline(in, coach_name);
	juveniles->setCoach(removespaces(coach_name));
	in >> n_trainings;
	for (int i = 0; i < n_trainings; i++) {
		Training *t = new Training;
		in >> (*t);
		juveniles->addEvent(t);
	}
	in >> level_name;
	in.ignore();//extracts the end of line
	getline(in, coach_name);
	juniors->setCoach(removespaces(coach_name));
	in >> n_trainings;
	for (int i = 0; i < n_trainings; i++) {
		Training *t = new Training;
		in >> (*t);
		juniors->addEvent(t);
	}
	in >> level_name;
	in.ignore();//extracts the end of line
	getline(in, coach_name);
	seniors->setCoach(removespaces(coach_name));
	in >> n_trainings;
	for (int i = 0; i < n_trainings; i++) {
		Training *t = new Training;
		in >> (*t);
		seniors->addEvent(t);
	}
}

/*
*Reads tournaments file
*parameter: in - file where the tournaments information is written
*/
void Club::readtournaments(istream & in) {
	string level_name; //name of the level that is written
	int n_tournaments; //number of tournaments for each level
	in >> level_name;
	in >> n_tournaments;
	for (int i = 0; i < n_tournaments; i++) {
		Tournament *t = new Tournament;
		in >> (*t);
		minis->addEvent(t);
	}
	in >> level_name;
	in >> n_tournaments;
	for (int i = 0; i < n_tournaments; i++) {
		Tournament *t = new Tournament;
		in >> (*t);
		juveniles->addEvent(t);
	}
	in >> level_name;
	in >> n_tournaments;
	for (int i = 0; i < n_tournaments; i++) {
		Tournament *t = new Tournament;
		in >> (*t);
		juniors->addEvent(t);
	}
	in >> level_name;
	in >> n_tournaments;
	for (int i = 0; i < n_tournaments; i++) {
		Tournament *t = new Tournament;
		in >> (*t);
		seniors->addEvent(t);
	}
}
/*
 * Writes players in a file
 */
void Club::writeplayers() {
	ofstream out; //file
	out.open(filename_players);
	vector<Player *> minis_players = minis->getPlayers();
	vector<Player *> juveniles_players = juveniles->getPlayers();
	vector<Player *> juniors_players = juniors->getPlayers();
	vector<Player *> seniors_players = seniors->getPlayers();
	out
			<< minis_players.size() + juveniles_players.size()
					+ juniors_players.size() + seniors_players.size() << "\n";

	for (unsigned int i = 0; i < minis_players.size(); i++) {
		out << *minis_players[i] << "\n";
	}
	for (unsigned int i = 0; i < juveniles_players.size(); i++) {
		out << *juveniles_players[i] << "\n";
	}
	for (unsigned int i = 0; i < juniors_players.size(); i++) {
		out << *juniors_players[i] << "\n";
	}
	for (unsigned int i = 0; i < seniors_players.size(); i++) {
		out << *seniors_players[i] << "\n";
	}
	out << future_birthdays.size() << endl;
	for (auto it = future_birthdays.begin() ; it != future_birthdays.end() ; it++)
		out << **it << "\n";
}

/*
 * Writes trainings in a file
 */
void Club::writetrainings() {
	ofstream out; //file
	out.open(filename_trainings);
	vector<Event *> minis_events = minis->getEvents();
	vector<Event *> juveniles_events = juveniles->getEvents();
	vector<Event *> juniors_events = juniors->getEvents();
	vector<Event *> seniors_events = seniors->getEvents();
	out << name << "\n";
	out << "Minis\n" << minis->getCoach() << "\n";
	unsigned int count = 0;
	for (unsigned int i = 0; i < minis_events.size(); i++) {
		count = count + minis_events[i]->Istraining();
	}
	out << count << "\n";
	for (unsigned int i = 0; i < minis_events.size(); i++) {
		if (minis_events[i]->Istraining()) {
			minis_events[i]->writetofile(out);
			out << "\n";
		}
	}
	out << "Juveniles\n" << juveniles->getCoach() << "\n";
	count = 0;
	for (unsigned int i = 0; i < juveniles_events.size(); i++) {
		count = count + juveniles_events[i]->Istraining();
	}
	out << count << "\n";
	for (unsigned int i = 0; i < juveniles_events.size(); i++) {
		if (juveniles_events[i]->Istraining()) {
			juveniles_events[i]->writetofile(out);
			out << "\n";
		}
	}
	out << "Juniors\n" << juniors->getCoach() << "\n";
	count = 0;
	for (unsigned int i = 0; i < juniors_events.size(); i++) {
		count = count + juniors_events[i]->Istraining();
	}
	out << count << "\n";
	for (unsigned int i = 0; i < juniors_events.size(); i++) {
		if (juniors_events[i]->Istraining()) {
			juniors_events[i]->writetofile(out);
			out << "\n";
		}
	}
	out << "Seniors\n" << seniors->getCoach() << "\n";
	count = 0;
	for (unsigned int i = 0; i < seniors_events.size(); i++) {
		count = count + seniors_events[i]->Istraining();
	}
	out << count << "\n";
	for (unsigned int i = 0; i < seniors_events.size(); i++) {
		if (seniors_events[i]->Istraining()) {
			seniors_events[i]->writetofile(out);
			out << "\n";
		}
	}
}

/*
 * Writes tournaments in a file
 */
void Club::writetournaments() {
	ofstream out; //file
	out.open(filename_tournaments);
	vector<Event *> minis_events = minis->getEvents();
	vector<Event *> juveniles_events = juveniles->getEvents();
	vector<Event *> juniors_events = juniors->getEvents();
	vector<Event *> seniors_events = seniors->getEvents();
	out << "Minis\n";
	unsigned int count = 0;
	for (unsigned int i = 0; i < minis_events.size(); i++) {
		count = count + !minis_events[i]->Istraining();
	}
	out << count << "\n";
	for (unsigned int i = 0; i < minis_events.size(); i++) {
		if (!minis_events[i]->Istraining()) {
			minis_events[i]->writetofile(out);
			out << "\n";
		}
	}
	out << "Juveniles\n";
	count = 0;
	for (unsigned int i = 0; i < juveniles_events.size(); i++) {
		count = count + !juveniles_events[i]->Istraining();
	}
	out << count << "\n";
	for (unsigned int i = 0; i < juveniles_events.size(); i++) {
		if (!juveniles_events[i]->Istraining()) {
			juveniles_events[i]->writetofile(out);
			out << "\n";
		}
	}
	out << "Juniors\n";
	count = 0;
	for (unsigned int i = 0; i < juniors_events.size(); i++) {
		count = count + !juniors_events[i]->Istraining();
	}
	out << count << "\n";
	for (unsigned int i = 0; i < juniors_events.size(); i++) {
		if (!juniors_events[i]->Istraining()) {
			juniors_events[i]->writetofile(out);
			out << "\n";
		}
	}
	out << "Seniors\n";
	count = 0;
	for (unsigned int i = 0; i < seniors_events.size(); i++) {
		count = count + !seniors_events[i]->Istraining();
	}
	out << count << "\n";
	for (unsigned int i = 0; i < seniors_events.size(); i++) {
		if (!seniors_events[i]->Istraining()) {
			seniors_events[i]->writetofile(out);
			out << "\n";
		}
	}
}

/*
* returns a vector with thes name of all the players in the club. It also includes players that participated in certain events and were later removed
* Return value- vector with the names of all the players in the club
*/
vector<string> Club::getPlayers() const {
	vector<string> rplayers;//vector with the names of the players that is going to be returned
	vector<Level *> vector_levels = this->getLevels();//gets vector of pointers to the existent levels
	for (unsigned int i = 0; i < 4; i++) {
		vector<Player *>vector_players = vector_levels[i]->getPlayers();//gets vector of pointers to the existent players
		for (unsigned int j = 0; j < vector_players.size(); j++) {
			if (find(rplayers.begin(), rplayers.end(), vector_players[j]->getName()) == rplayers.end()) {
				rplayers.push_back(vector_players[j]->getName());
			}
		}
		vector<Event *> vector_events = vector_levels[i]->getEvents();//gets vector of pointers to the existent events
		for (unsigned int j = 0; j < vector_events.size(); j++) {
			vector<string> vector_presences = vector_events[j]->getPresences();//gets vector with the names of the players that participated in a tournament
			for (unsigned int k = 0; k < vector_presences.size(); k++) {
				if (find(rplayers.begin(), rplayers.end(), vector_presences[k]) == rplayers.end()) {
					rplayers.push_back(vector_presences[k]);
				}
			}
		}
	}

	sort(rplayers.begin(), rplayers.end());
	return rplayers;
}

/*
* This functions constructs a tree for all the levels
*/
void Club::makeTree() {
	minis->actualize_curr_parameters();
	juveniles->actualize_curr_parameters();
	juniors->actualize_curr_parameters();
	seniors->actualize_curr_parameters();
	minis->makeTree();
	juveniles->makeTree();
	juniors->makeTree();
	seniors->makeTree();
}


/*
* This function constructs a priority queue
*/

void Club::makeQueue() {
	ECG_queue = priority_queue<Player_queue>();
	Date current_date;//current date
	vector<Player *>minis_players = minis->getPlayers();
	vector<Player *>juveniles_players = juveniles->getPlayers();
	vector<Player *>juniors_players = juniors->getPlayers();
	vector<Player *>seniors_players = seniors->getPlayers();
	for (unsigned int i = 0; i < minis_players.size(); i++) {
		if (!minis_players[i]->checkECG(current_date)) {
			Player_queue pq;//struct that is going to be inserted in the queue
			pq.player = minis_players[i];
			ECG_queue.push(pq);
		}
	}
	for (unsigned int i = 0; i < juveniles_players.size(); i++) {
		if (!juveniles_players[i]->checkECG(current_date)) {
			Player_queue pq;//struct that is going to be inserted in the queue
			pq.player = juveniles_players[i];
			ECG_queue.push(pq);
		}
	}

	for (unsigned int i = 0; i < juniors_players.size(); i++) {
		if (!juniors_players[i]->checkECG(current_date)) {
			Player_queue pq;//struct that is going to be inserted in the queue
			pq.player = juniors_players[i];
			ECG_queue.push(pq);
		}
	}

	for (unsigned int i = 0; i < seniors_players.size(); i++) {
		if (!seniors_players[i]->checkECG(current_date)) {
			Player_queue pq;//struct that is going to be inserted in the queue
			pq.player = seniors_players[i];
			ECG_queue.push(pq);
		}
	}
}

/*
* This function adds a player to ecg queue
* parameter: pl - player that is going to be added to the queue
*/
void Club::addPlayerQueue(Player * pl) {
	Player_queue pq;//player that is going to be added to queue
	pq.player = pl;
	Date current_date;//current date
	if (!pl->checkECG(current_date)) {
		ECG_queue.push(pq);
	}
}


/*
* This function removes a player from the ecg queue
* parameter: pl - player that is going to be removed  from the queue
*/
void Club::removePlayerQueue(Player * pl) {
	vector<Player_queue> players;
	while (!ECG_queue.empty()) {
		players.push_back(ECG_queue.top());
		ECG_queue.pop();
	}
	for (unsigned int i = 0; i < players.size(); i++) {
		if (players[i].player != pl) {
			ECG_queue.push(players[i]);
		}
	}
}

/*
* This function prints the ECG queue on the screen
*/
void Club::showQueue() {
	priority_queue<Player_queue> pq_copy = ECG_queue;//ecg copy
	cout <<setw(21) << "Name |" << setw(16) << "Birthday|" << setw(15) << "Last ECG"<<endl;
	while (!pq_copy.empty()) {
		Player * pl = pq_copy.top().player;//player whose information is going to be printed
		cout << setw(20) << pl->getName() << "|";
		cout << "     ";
		pl->getBirth().show();
		cout << "|     ";
		pl->getLast_Eletro().show();
		cout << "\n";
		pq_copy.pop();
	}
}

bool Club::addBirthday(Player *p1){
	Date current_date;
	current_date = current_date.subtractDays(1);
	if( actualage(p1->getBirth()) > minis->getMinAge() ){
		if ( hashFuncs()(p1)  != -1){
			if( !findOldPlayer(p1)){
				//if his birthday was yesterday then update got_present parameter
				if (p1->getBirth().getDay() == current_date.getDay() && p1->getBirth().getMonth() == current_date.getMonth() )
					p1->setPresent(false);
				this->future_birthdays.insert(p1);
				return true;
			}
			else
				throw DuplicateName( p1->getName() );

		}

	}

	return false;
}

bool Club::removeBirthday(Player *p1){
	auto its = this->future_birthdays.equal_range(p1);

	if (its.first != its.second){ //If players are found
		while(its.first != its.second){
			if (**(its.first) == *(p1) ){
				this->future_birthdays.erase(its.first);
				return true;
			}
			its.first++;
		}
	}

	return false;
}

bool Club::findOldPlayer(Player *p1){
	for(auto it = this->future_birthdays.begin() ; it != this->future_birthdays.end() ; it++)
		if ( (*it)->getName() == p1->getName() )
			return true;

	return false;
}

vector<Player *> Club::nextBirthdays(int days=10) const{
	vector<Player *> temp;
	Date current_date;
	temp.reserve(this->future_birthdays.size());

	for(int i = 0 ; i <= days ; i++){
		Date end_date = current_date.addDays(i);
		Player t(end_date);
		//When it has gone across the calendar
		if (i != 0 && current_date.getDay() == end_date.getDay() && current_date.getMonth() == end_date.getMonth() )
			break;
		auto its = this->future_birthdays.equal_range( &t );
		while(its.first != its.second){
			if ( !( (*(its.first))->getPresent() ) )
				temp.push_back( *(its.first));
			its.first++;
		}
	}

	temp.shrink_to_fit();
	return temp;
}
