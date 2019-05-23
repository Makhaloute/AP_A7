#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>


using namespace std;


/*
 the IFollow is a big class , that has a methods and these methods are defrent
 so each child execute methods diffrently
 */










constexpr int PUBLISHER_FOLLOWED_NOTIF = 270;
constexpr int PUBLISHER_BUOUGTYOURFILM_NOTIF = 250;
constexpr int PUBLISHER_RATEDYOURFILM_NOTIF = 260;
constexpr int PUBLISHER_COMMENTEDYOURFILM_NOTIF = 285;
constexpr int USER_PUBLISERNEWFILM_NOTIF = 385;
constexpr int USER_COMMENTREPLY_NOTIF = 485;


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







class User{
public:
	bool isThisPublisher();
	void addMoney(int amount);
	int showNewNotifications();
	int showAllNotifications();
	bool isHeSomeOneIFollow(int userId);
	int addFollowr(int follwerId);
	bool isMoneyEnogh(int price);
	void subtractBuyingCost(int cost);
	int addNotification(string nameOfUserWhoYourNotifiedFor,
	 		int whoYourNotifiedForId, int notificationType, 
	 			int filmId = 0, string _filmName = 0);//unacceptable as is
													  //parse in some other functions
private:
	INotification* notifs;
	int moneyStock;
	bool functionalType;
	int id;
	map <string,string> characteristics;
	vector<int> follwersId;
};






struct Comment{
	Comment(int _id, string _comment):id(_id),comment(_comment){}
	void addReply(string reply);

	string comment;
	vector <string> replyes;
	bool commentActiveness;
	int id;
};
void Comment::addReply(string reply){
	if(reply != "")
		replyes.push_back(reply);
	else
		cerr<<"there is an empty reply";
}






class Film{
public:
	int deleteThisComment(int commentId);
	int tellDetail();
	int changeDetails(int userId, map<string,string> newDetails);
	int addComment(string comment);
	int replyToComment(int commentId);
	void addRate(float newRate);
	float getRate(){return rate;}
	void addBuyer(int buyerId);
	bool isUserTheCreator(int userId);
	pair<int,float>tellPriceAndRate();
private:
	vector <Comment> comments;
	map <string,string> details;
	vector<int> buyersId;
	bool saleStatus;
	float rate;
	int creatorId;
};







class Ifilm{
public:
	void deleteComment(int filmId, int userId, int commentId );
	void tellFilmDetail(int filmId);
	int changeFilmDetails(int filmId, int userId, map <string,string> newDetails);
	int addFilm(User * user, map <string,string> details);
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

	Ifilm * films;
	User* currentUser;
	vector<User*> users;
};


















int main (){;}