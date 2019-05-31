#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
//#include <algorithm>

using namespace std;


constexpr int PUBLISHER_FOLLOWED_NOTIF = 270;
constexpr int PUBLISHER_BUOUGTYOURFILM_NOTIF = 250;
constexpr int PUBLISHER_RATEDYOURFILM_NOTIF = 260;
constexpr int PUBLISHER_COMMENTEDYOURFILM_NOTIF = 285;
constexpr int USER_PUBLISERNEWFILM_NOTIF = 385;
constexpr int USER_COMMENTREPLY_NOTIF = 485;

const string DONE_MAEESAGE = "OK";
const string ERROR_PERMISION = "Permission Denied";
const string ERROR_BADREQUEST = "Bad Request";
const string ERROR_NOTFOUND = "Not Found";









class Notification{
public:
	Notification(string nameOfNotifMaker, int _notifMakerId, 
		int _notificationType, int _filmId, string _filmName);
	Notification(string nameOfNotifMaker, int _notifMakerId, int _notificationType);

	void printNotification();
private:
	string notifMakerName;
	int notifMakerId;
	int notificationType;
	int filmId;
	string filmName;
};

Notification::Notification(string nameOfNotifMaker, int _notifMakerId, int _notificationType){
	notifMakerName = nameOfNotifMaker;
	notifMakerId = _notifMakerId;
	notificationType = _notificationType;
	filmId = 0;
	filmName = "";
}

Notification::Notification(string nameOfNotifMaker, int _notifMakerId,
					 int _notificationType, int _filmId, string _filmName){

	notifMakerName = nameOfNotifMaker;
	notifMakerId = _notifMakerId;
	notificationType = _notificationType;
	filmId = _filmId;
	filmName = _filmName;
}

void Notification::printNotification(){
	if(notificationType == PUBLISHER_FOLLOWED_NOTIF)
		cout << "User " << notifMakerName << " with id " << notifMakerId << " follow you." << endl;
	if(notificationType == PUBLISHER_BUOUGTYOURFILM_NOTIF)
		cout << "User " << notifMakerName << " with id " << notifMakerId 
				<< " buy your film " << filmName << " with id " << filmId << endl;
	if(notificationType == PUBLISHER_RATEDYOURFILM_NOTIF)
		cout << "User " << notifMakerName << " with id " << notifMakerId 
				<< " rate your film " << filmName << " with id " << filmId << endl;
	if(notificationType == PUBLISHER_COMMENTEDYOURFILM_NOTIF)
		cout << "User " << notifMakerName << " with id " << notifMakerId 
				<< " rate your film " << filmName << " with id " << filmId << endl;
	if(notificationType == USER_PUBLISERNEWFILM_NOTIF)
		cout << "Publisher " << notifMakerName << " with id " 
				<< notifMakerId << " register new film."<<endl;
	if(notificationType == USER_COMMENTREPLY_NOTIF)
		cout << "Publisher " << notifMakerName << " with id " 
				<< notifMakerId << " reply to your comment."<<endl;
}







class INotification{
public:
	void addNormalNotification(string nameOfNotifMaker, int NotifMakerId, int notificationType);
	void addNotificationPublisherSpecific(string nameOfNotifMaker, int NotifMakerId,
			 int notificationType, int filmId, string filmName);
	int showNewNotifications();
	int showAllNotifications(int limit = 0);
private:
	void printNotifications(vector<Notification*> printVector, int limit = 0);
	void addNotificationsToOthers();
	vector <Notification*> unReadNotifications;
	vector <Notification*> readNotifications;
};


void INotification::addNormalNotification(string nameOfNotifMaker, int NotifMakerId, int notificationType){
	Notification* newNotification = new Notification(nameOfNotifMaker,NotifMakerId,notificationType);
	unReadNotifications.push_back(newNotification);
}

void INotification::addNotificationPublisherSpecific(string nameOfNotifMaker, int NotifMakerId,
			 int notificationType, int filmId, string filmName){
	Notification* newNotification = new Notification(nameOfNotifMaker,NotifMakerId,notificationType,filmId,filmName);
	unReadNotifications.push_back(newNotification);
}

const string OUT_NOTIFICATION_STARTER = "#. Notification Message";

void INotification::printNotifications(vector<Notification*> printVector, int limit){
	if (limit == 0)
		limit = printVector.size();
	cout << OUT_NOTIFICATION_STARTER << endl;
	for(int i = 0;i < printVector.size();i++){
		if (printVector.size() - i - 1 < 0)
			cout << "error is in Inotif -> printnotif" << endl;
		cout << i+1 << ". ";
		printVector[printVector.size() - i - 1]->printNotification();
		if (i+1 == limit)
			return;
	}
} 

void INotification::addNotificationsToOthers(){
	vector<Notification*> emptyVector;
	for (int i = 0;i< unReadNotifications.size();i++)
		readNotifications.push_back(unReadNotifications[i]);
	unReadNotifications = emptyVector;
}

int INotification::showNewNotifications(){
	this->printNotifications(unReadNotifications);
	this->addNotificationsToOthers();
	return 1;
}

int INotification::showAllNotifications(int limit){
	this->printNotifications(readNotifications,limit);
	return 1;
}













constexpr int PUBLISHERCODE = 1;
constexpr int REGULARUSERCODE = 0;

class User{
public:
	User(map <string,string> _characteristics, int _id, bool publisher);
	bool isThisPublisher() {return functionalType;}
	bool isThisMyName(string userName);
	bool isThisMe(string userName, string passWord);
	void addMoney(int amount);
	void showNewNotifications() {notifs->showNewNotifications();}
	void showAllNotifications() {notifs->showAllNotifications();}
	bool isHeSomeOneIFollow(int userId);
	int addFollowr(int follwerId);
	bool isMoneyEnogh(int price);
	void subtractBuyingCost(int cost) {moneyStock -= cost;}
	int addNotification(string nameOfUserWhoYourNotifiedFor,
	 		int whoYourNotifiedForId, int notificationType, 
	 			int filmId = 0, string filmName = 0);
private:
	INotification* notifs;
	int moneyStock;
	bool functionalType;
	int id;
	map <string,string> characteristics;
	vector<int> follwersId;
};

User::User(map <string,string> _characteristics, int _id, bool publisher){
	notifs = new INotification();
	moneyStock = 0;
	characteristics = _characteristics;
	id = _id;
	functionalType = publisher;
}

bool User::isThisMe(string userName, string passWord){
	if(characteristics.find("username") == characteristics.end())
		return false;	
	else{
		map<string,string> :: iterator it1 = characteristics.find("username");
		if(it1->second == userName){
				if(characteristics.find("password") == characteristics.end())
					return false;	
				else{
					map<string,string> :: iterator it2 = characteristics.find("password");
						if(it2->second == passWord)
							return true;
					}
		}
	}
	return false;
}

bool User::isThisMyName(string userName){
	if(characteristics.find("username") == characteristics.end())
		return false;	
	else{
		map<string,string> :: iterator it = characteristics.find("username");
		if(it->second == userName)
			return true;
		return false;
	}
}

void User::addMoney(int amount){
	moneyStock += amount;
	cout << DONE_MAEESAGE << endl;
}

bool User::isHeSomeOneIFollow(int userId){
	for(int i = 0;i<follwersId.size();i++)
		if(follwersId[i] == userId)
			return true;
	return false;
}

int User::addFollowr(int follwerId){
	follwersId.push_back(follwerId);
	cout << DONE_MAEESAGE << endl;
	return 1;
}

bool User::isMoneyEnogh(int price){
	if(moneyStock >= price)
		return true;
	return false;
}



int User::addNotification(string nameOfUserWhoYourNotifiedFor, int whoYourNotifiedForId, int notificationType, int filmId, string filmName){
	if(notificationType == PUBLISHER_BUOUGTYOURFILM_NOTIF || notificationType == PUBLISHER_COMMENTEDYOURFILM_NOTIF || notificationType == PUBLISHER_RATEDYOURFILM_NOTIF)
		notifs->addNotificationPublisherSpecific(nameOfUserWhoYourNotifiedFor,whoYourNotifiedForId,notificationType,filmId,filmName);
	else
		notifs->addNormalNotification(nameOfUserWhoYourNotifiedFor,whoYourNotifiedForId,notificationType);
}













constexpr int ACTIVE = 1;
constexpr int NONACTIVE = 0;

struct Comment{
	Comment(int _id, string _comment):id(_id),comment(_comment){commentActiveness = ACTIVE;}
	void addReply(string reply);
	void deleteThis();
	void printCommentsAndReplyes();
	string comment;
	vector <string> replyes;
	bool commentActiveness;
	int id;
};

void Comment::printCommentsAndReplyes(){
	if(commentActiveness == NONACTIVE)
		return;
	cout << id << ". " << comment << endl;
	for (int i = 0;i < replyes.size();i++){
		cout << id << '.' << i+1 << replyes[i] << endl;
	}
}


void Comment::addReply(string reply){
	if(reply != ""){
		replyes.push_back(reply);
		cout << DONE_MAEESAGE <<endl;
	}
	else
		cerr<<"there is an empty reply";
}

void Comment::deleteThis(){
	if(!commentActiveness){
		cout <<	"Bad Request" <<endl;
		return;
	}
	commentActiveness = NONACTIVE;
	cout << DONE_MAEESAGE <<endl;
}






const string MAPS_NAME = "name";
const string MAPS_YEAR = "year";
const string MAPS_LENGTH = "length";
const string MAPS_PRICE = "price";
const string MAPS_DIRECTOR = "director";
const string SPACEINOUTOFFILMDETAILS = " | ";
const string FILMDETAILINTRO = "Details of Film ";
const string MAPS_SUMMERY = "summary";
const string OUT_DETAIL_ID = "Id = ";
const string OUT_DETAIL_DIRECTOR = "Director = ";
const string OUT_DETAIL_LENGTH = "Length = ";
const string OUT_DETAIL_YEAR = "Year = ";
const string OUT_DETAIL_SUMMARY = "Summary = ";
const string OUT_DETAIL_RATE = "Rate = ";
const string OUT_DETAIL_PRICE = "Price = ";
const string OUT_COMMENT = "Comments";
const string RECOM_OUT_START = "#.";
const string RECOM_OUT_FID = " Film Id |";
const string RECOM_OUT_FNAME = " Film Name |";
const string RECOM_OUT_FLENGTH = " Film Length |";
const string RECOM_OUT_FPRICE = " Film price |";
const string RECOM_OUT_FRATE = " Rate |";
const string RECOM_OUT_FYEAR = " Production Year |";
const string RECOM_OUT_FDIRECTOR = " Film Director";
const string OUT_RECOM = "Recommendation Film \n";


class Film{
public:
	Film(int _creatorId, map <string,string> _details, int id);
	int deleteFilm(int userId);
	bool isFilmDeleted() {return saleStatus;}
	int deleteThisComment(int commentId);
	int tellDetail();
	int changeDetails(int userId, vector< pair<string,string>> newDetails);
	int addComment(string _comment);
	int replyToComment(int commentId , string reply);
	void addRate(float newRate);
	float getRate() {return rate;}
	void addBuyer(int buyerId) {buyersId.push_back(buyerId);}
	bool isUserTheCreator(int userId);
	bool isHeHasTheFilm(int userId);
	void tellBrifDetail();
	void tellVeryBrifDetail();
	pair<int,float>tellPriceAndRate();

private:
	int changeThisBlockOfMap(string key , string data);
	string giveDataInMap(string key);
	vector <Comment*> comments;
	map <string,string> details;
	int filmId;
	int price;
	vector<int> buyersId;
	bool saleStatus;
	float rate;
	int numberOfRates;
	int creatorId;
};



void Film::tellVeryBrifDetail(){
	cout << this->filmId << SPACEINOUTOFFILMDETAILS;
	cout << giveDataInMap(MAPS_NAME) << SPACEINOUTOFFILMDETAILS;
	cout << giveDataInMap(MAPS_LENGTH) << SPACEINOUTOFFILMDETAILS;
	cout << giveDataInMap(MAPS_DIRECTOR);
}

void Film::tellBrifDetail(){
	cout << this->filmId << SPACEINOUTOFFILMDETAILS;
	cout << giveDataInMap(MAPS_NAME) << SPACEINOUTOFFILMDETAILS;
	cout << giveDataInMap(MAPS_LENGTH) << SPACEINOUTOFFILMDETAILS;
	cout << giveDataInMap(MAPS_PRICE) << SPACEINOUTOFFILMDETAILS;
	cout << this->rate << SPACEINOUTOFFILMDETAILS;
	cout << giveDataInMap(MAPS_YEAR) << SPACEINOUTOFFILMDETAILS;
	cout << giveDataInMap(MAPS_DIRECTOR);
}

bool Film::isHeHasTheFilm(int userId){
	for(int i = 0;i < buyersId.size();i++)
		if (buyersId[i] == userId)
			return true;
	return false;	
}

int Film::deleteFilm(int userId){
	if(!isUserTheCreator(userId)){
		cout << ERROR_PERMISION << endl;
		return 0;
	}
	saleStatus = NONACTIVE;
	return 1;
}

Film::Film(int _creatorId, map <string,string> _details , int id){
	creatorId = _creatorId;
	details = _details;
	price = stoi(giveDataInMap(MAPS_PRICE));
	filmId = id;
	saleStatus = ACTIVE;
	rate = 0;
}

pair<int,float> Film::tellPriceAndRate(){
	pair<int,float> result;
	result.first = price;
	result.second = rate;
	return result;
}

bool Film::isUserTheCreator(int userId){
	if(userId == creatorId)
		return true;
	return false;
}

int Film::addComment(string _comment){
	Comment *comment = new Comment(comments.size() + 1,_comment);
	comments.push_back(comment);
	return 1;
}

int Film::replyToComment(int commentId , string reply){
	if (commentId > comments.size()){
		cout << ERROR_BADREQUEST << endl;
		return 0;
	}
	comments[commentId - 1]->addReply(reply);
	return 1;
}

void Film::addRate(float newRate){
	if (numberOfRates == 0){
		rate = newRate;
		numberOfRates++;
		return;
	}
	float totalSumOfRates = rate * numberOfRates;
	totalSumOfRates += newRate;
	numberOfRates++;
	rate = totalSumOfRates / numberOfRates;
}

int Film::deleteThisComment(int commentId){
	for(int i = 0 ;i< comments.size();i++)
		if(commentId == comments[i]->id){
			comments[i]->deleteThis();
			return 1;
		}
	cout <<	ERROR_NOTFOUND <<endl;
	return 0;
}

string Film::giveDataInMap(string key){
	if( details.find(key) == details.end())
		return "";	
	else{
		map<string,string> :: iterator it = details.find(key);
		return it->second;
	}
} 


int Film::tellDetail(){
	cout << FILMDETAILINTRO << giveDataInMap(MAPS_NAME) << endl;
	cout << OUT_DETAIL_ID << this->filmId << endl;
	cout << OUT_DETAIL_DIRECTOR << giveDataInMap(MAPS_DIRECTOR) << endl;
	cout << OUT_DETAIL_LENGTH << giveDataInMap(MAPS_LENGTH) << endl;
	cout << OUT_DETAIL_YEAR << giveDataInMap(MAPS_YEAR) << endl;
	cout << OUT_DETAIL_SUMMARY << giveDataInMap(MAPS_SUMMERY) << endl;
	cout << OUT_DETAIL_RATE << this->rate << endl;
	cout << OUT_DETAIL_PRICE << this->price << endl << endl;
	cout << OUT_COMMENT << endl;
	for(int i = 0;i < comments.size();i++)
		comments[i]->printCommentsAndReplyes();
	cout << endl;
	return 1;
}

int Film::changeThisBlockOfMap(string key , string data){
	if( details.find(key) == details.end())
		return 0;	
	else{
		map<string,string> :: iterator it = details.find(key);
		it->second = data;
		return 1;
	}
}

int Film::changeDetails(int userId, vector< pair<string,string>> newDetails){
	if (creatorId != userId){
		cout << ERROR_PERMISION <<endl; 
		return 0;
	}
	for (int i = 0 ;newDetails.size();i++){
		if (newDetails[i].first == MAPS_NAME || newDetails[i].first == MAPS_YEAR || newDetails[i].first == MAPS_LENGTH || newDetails[i].first == MAPS_DIRECTOR || newDetails[i].first == MAPS_SUMMERY)
			changeThisBlockOfMap(newDetails[i].first,newDetails[i].second);
		else{
			cout << ERROR_BADREQUEST << endl;
			return 0;
		}
	}
	cout << DONE_MAEESAGE << endl;
	return 1;
}



















class Ifilm{
public:
	int addFilm(int creatorId, map <string,string> details);
	void deleteComment(int filmId, int userId, int commentId);
	void tellFilmDetail(int filmId);
	int changeFilmDetails(int filmId, int userId, vector< pair<string,string>> newDetails);
	int addCommentToFilm (int userId, int filmId, string comment);
	int replyToThisComment(int userId, int filmId, int commentId, string reply);
	int rateThisFilm(int userId, int filmId, float score);
	void buyFilm(int filmId, int buyerId);
	void tellFilmThatItIsBought(int filmId, int buyerId);
	void printRecomendedFilms(int filmId);
	void updateFilmsGraph(int filmId, int buyerId);
	void deleteThisFilm(int filmId, int userId);	
	void showMyBoughtFilms(int userId);
	void showFilmsIAdded(int userId);
private:
	vector<int> tellMostSutableFilmRecomendationForFilm(int filmId);
	vector<int> listScores(vector<int> scores);
	void addNewFilmToGraph();
	void adaptFilmGraph();
	vector <Film*> films;
	vector<vector<int>> filmsGraph;
};

void Ifilm::printRecomendedFilms(int filmId){
	vector<int> recomFilms = tellMostSutableFilmRecomendationForFilm(filmId);
	adaptFilmGraph();
	cout << OUT_RECOM;
	cout << RECOM_OUT_START << RECOM_OUT_FID << RECOM_OUT_FNAME 
			<< RECOM_OUT_FLENGTH << RECOM_OUT_FDIRECTOR;
	for(int i = 0;(i < recomFilms.size() && i < 4);i++){ 
		cout << i+1 << ". ";
		this->films[recomFilms[i]]->tellVeryBrifDetail();
		cout << endl;
	}
}

void Ifilm::showMyBoughtFilms(int userId){
	cout << RECOM_OUT_START << RECOM_OUT_FID << RECOM_OUT_FNAME 
			<< RECOM_OUT_FLENGTH << RECOM_OUT_FPRICE << RECOM_OUT_FRATE 
				<< RECOM_OUT_FYEAR << RECOM_OUT_FDIRECTOR;

	for(int i = 0;i < films.size();i++){
		if(films[i]->isHeHasTheFilm(userId)){
			films[i]->tellBrifDetail();
			cout << endl;
		}
	}
}

void Ifilm::showFilmsIAdded(int userId){
	cout << RECOM_OUT_START << RECOM_OUT_FID << RECOM_OUT_FNAME 
			<< RECOM_OUT_FLENGTH << RECOM_OUT_FPRICE << RECOM_OUT_FRATE 
				<< RECOM_OUT_FYEAR << RECOM_OUT_FDIRECTOR;

		
	for(int i = 0;i < films.size();i++){
			if(films[i]->isUserTheCreator(userId)){
				films[i]->tellBrifDetail();
				cout << endl;
			}
		}

}

void Ifilm::deleteThisFilm(int filmId, int userId){
	if(filmId > films.size()){
		cout << ERROR_NOTFOUND <<endl;		 
		return;
	}
	films[filmId - 1]->deleteFilm(userId);	
	for(int i = 0;i < films.size();i++){
		filmsGraph[filmId - 1][i] = -1;
		filmsGraph[i][filmId -1] = -1;	
	}
}

void Ifilm::updateFilmsGraph(int filmId, int buyerId){
	for(int i = 0;i < films.size();i++){
		if(films[i]->isHeHasTheFilm(buyerId)){
			if(filmsGraph[filmId - 1][i] != -1)
				filmsGraph[filmId - 1][i]++;
			if(filmsGraph[i][filmId -1] != -1)
				filmsGraph[i][filmId -1]++;	
		}	
	}
}

vector<int> Ifilm::listScores(vector<int> scores){
	vector <int> result;
	vector<int> scoresCopy = scores;
	sort(scores.begin(),scores.end(),greater<int>());
	for(int i = 0 ;i < scores.size();i++){
		for(int j = 0;j < scoresCopy.size();j++){
			if(scores[i] == scoresCopy[j]){
				result.push_back(j);
				scoresCopy[j] = -150;
				continue;
			}
		}
	}
	return result;
}

vector<int> Ifilm::tellMostSutableFilmRecomendationForFilm(int filmId){
	vector<int> scores = filmsGraph[filmId - 1];
	return listScores(scores);
}

void Ifilm::adaptFilmGraph(){
	if ( filmsGraph.size() != filmsGraph[filmsGraph.size() - 2].size()){
		cout <<"error in program = matrix is not 'motegaren :)' " <<endl;
		return;
	}
	for(int i = 0,j = 0;i < filmsGraph.size();i=j=j+1){
		filmsGraph[i][j] = 0;
	}
}

void Ifilm::buyFilm(int filmId, int buyerId){
	tellFilmThatItIsBought(filmId,buyerId);
	updateFilmsGraph(filmId,buyerId);
}

void Ifilm::tellFilmThatItIsBought(int filmId, int buyerId){
	if(filmId > films.size()){
		cout << ERROR_NOTFOUND <<endl;		 
		return;
	}
	films[filmId - 1]->addBuyer(buyerId);
}

int Ifilm::rateThisFilm(int userId, int filmId, float score){
	if(filmId > films.size()){
		cout << ERROR_NOTFOUND << endl;		 
		return 0;
	}
	if (films[filmId - 1]->isHeHasTheFilm(userId)){
		films[filmId - 1]->addRate(score);
		return 1;
	}
	cout << ERROR_PERMISION << endl;
	return 0;
}

int Ifilm::replyToThisComment(int userId, int filmId, int commentId, string reply){
	if(filmId > films.size()){
		cout << ERROR_NOTFOUND <<endl;		 
		return 0;
	}
	if (films[filmId - 1]->isUserTheCreator(userId)){
	 films[filmId - 1]->replyToComment(commentId,reply);
	 return 1;
	}
	cout << ERROR_PERMISION << endl;
	return 0;
}

int Ifilm::addCommentToFilm (int userId, int filmId, string comment){
	if(filmId > films.size()){
		cout << ERROR_NOTFOUND <<endl;		 
		return 0;
	}
	if (films[filmId - 1]->isHeHasTheFilm(userId)){
		films[filmId - 1]->addComment(comment);
		return 1;
	}
	cout << ERROR_PERMISION << endl;
	return 0;
}

int Ifilm::changeFilmDetails(int filmId, int userId, vector< pair<string,string>> newDetails){
	if(filmId > films.size()){
		cout << ERROR_NOTFOUND <<endl;		 
		return 0;
	}
	films[filmId - 1]->changeDetails(userId,newDetails);
	return 1;
}

void Ifilm::addNewFilmToGraph(){
	if(filmsGraph.size() == 0){
		filmsGraph[0].push_back(0);
		return;
	}

	for(int i = 0 ;i < filmsGraph.size();i++){
		filmsGraph[i].push_back(0);
	}
	vector<int> emptyVector;
	filmsGraph.push_back(vector<int>());
	for(int i = 0;i < filmsGraph.size();i++)
		filmsGraph[filmsGraph.size() - 1].push_back(0);
} 

int Ifilm::addFilm(int creatorId, map <string,string> details){
	Film* newFilm = new Film(creatorId,details,films.size() + 1);
	films.push_back(newFilm);
	addNewFilmToGraph();
	return 1;
}

void Ifilm::tellFilmDetail(int filmId){
	if(filmId > films.size()){
		cout << ERROR_NOTFOUND <<endl;		 
		return;
	}
	films[filmId - 1]->tellDetail();
	printRecomendedFilms(filmId);
}

void Ifilm::deleteComment(int filmId, int userId, int commentId){
	if (filmId > films.size()){
		cout << ERROR_NOTFOUND << endl;
		return;
	}
	if (films[filmId - 1]->isUserTheCreator(userId)){
 		films[filmId - 1]->deleteThisComment(commentId);
 		return;
 	}
 	cout << ERROR_PERMISION << endl;
}
	






























class Imain{
public:
	Imain();
	void signup(string userName, map <string,string> carectristics, bool userType);
	int login(string userName, string passWord);
	int buyFilm(); 

private:
	vector <pair<int,int>> systemsDebtToPublishers;
	Ifilm * films;
	User* currentUser;
	vector<User*> users;
};

Imain::Imain(){
	films = new Ifilm();
}

void Imain::signup(string userName, map <string,string> carectristics, bool userType){
	for(int i = 0;i < users.size();i++){
		if(users[i]->isThisMyName(userName)){
			cout << ERROR_BADREQUEST << endl;
			return;
		}
	}
	User* newUser = new User(carectristics,users.size() + 1,userType); 
	users.push_back(newUser);
	currentUser = newUser;
	cout << DONE_MAEESAGE << endl;
}

int Imain::login(string userName, string passWord){
	for(int i = 0 ;i < users.size();i++){
		if(users[i]->isThisMe(userName,passWord)){
			currentUser = users[i];
			cout << DONE_MAEESAGE << endl;
			return 1;
		}
	}
	cout << ERROR_NOTFOUND << endl;
	return 0;
}
	







































vector<string> parseCommand(string command){
	vector<string> result;
	string singleCommand = "";
	for(int i = 0;i < command.length();i++){
		if(command[i] != ' '){
			singleCommand += command[i];
		}
		else{
			result.push_back(singleCommand);
			singleCommand = "";
		}
	}
	return result;
}
map<string,string> parseData(string data) {
	vector<string> datas = parseCommand(data);
	map<string,string> resultMap;
	pair<string,string> dummy;
	for(int i = 0;i < datas.size();i+=2){
		dummy.first = datas[i];
		dummy.second = datas[i+1];
		resultMap.insert(dummy);
	}
	return resultMap;
}

vector <pair<vector<string>,map<string,string>>> handleInput(){
	vector <pair<vector<string>,map<string,string>>> input;
	pair<vector<string>,map<string,string>> singlePair;
	string line;
	string flagi = "?";
	while(getline(cin,line)){
		singlePair.first = parseCommand(line.substr(0,line.find(flagi)));		
		singlePair.second = parseData(line.substr(line.find(flagi) + flagi.length()));
		input.push_back(singlePair);
	}
	return input;
}

int main (){
	
	Imain* imain;
	vector <pair<vector<string>,map<string,string>>> input = handleInput();


}




