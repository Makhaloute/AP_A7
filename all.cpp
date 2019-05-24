#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>


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
	INotification();
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



	bool isThisPublisher() {return functionalType;}
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
	string comment;
	vector <string> replyes;
	bool commentActiveness;
	int id;
};
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


class Film{
public:
	Film(int _creatorId, map <string,string> _details, int id);
	int deleteThisFilm(int userId);
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
	pair<int,float>tellPriceAndRate();
private:
	int changeMapOfDetails(string key , string data);
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


int Film::deleteThisFilm(int userId){
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
	cout <<	ERROR_BADREQUEST <<endl;
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
	cout << OUT_DETAIL_PRICE << this->price << endl;
	return 1;
}




int Film::changeMapOfDetails(string key , string data){
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
			changeMapOfDetails(newDetails[i].first,newDetails[i].second);
		else{
			cout << ERROR_BADREQUEST << endl;
			return 0;
		}
	}
	cout << DONE_MAEESAGE << endl;
	return 1;
}























void f(){	;// not exacly this
	//dummy function
	//cout << this->filmId << SPACEINOUTOFFILMDETAILS;
	//cout << giveDataInMap(MAPS_NAME) << SPACEINOUTOFFILMDETAILS;
	//cout << giveDataInMap(MAPS_LENGTH) << SPACEINOUTOFFILMDETAILS;
	//cout << giveDataInMap(MAPS_PRICE) << SPACEINOUTOFFILMDETAILS;
	//cout << this->rate << SPACEINOUTOFFILMDETAILS;
	//cout << giveDataInMap(MAPS_YEAR) << SPACEINOUTOFFILMDETAILS;
	//cout << giveDataInMap(MAPS_DIRECTOR);
}

class Ifilm{
//constexpr string TITLEOFFILMSHOW = "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director";

public:
	int addFilm(int creatorId, map <string,string> details);
	void deleteComment(int filmId, int userId, int commentId );
	void tellFilmDetail(int filmId);
	int changeFilmDetails(int filmId, int userId, vector< pair<string,string>> newDetails);

	int addCommentToFilm (int userId, int filmId, string comment);
	int replyToComment(int userId, int filmId, int commentId, string reply);
	void showMyBoughtFilms(int userId);
	void showFilmsIAdded(int userId);
	int rateThisFilm(int filmId, float score);
	void buyFilm(int filmId, int buyerId);

private:
	vector <Film*> films;
};



























class Imain{
public:
	Imain(){films = new Ifilm();};
	void signup(map <string,string> carectristics , bool userType);
	int login(map <string,string> claims);
	int buyFilm(); // 

private:
	vector <pair<int,int>> systemsDebtToPublishers;
	Ifilm * films;
	User* currentUser;
	vector<User*> users;
};


















int main (){;}