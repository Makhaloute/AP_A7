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
		int _notificationType, int _filmId = 0, string _filmName = 0);

	void printNotification();
private:
	string notifMakerName;
	int notifMakerId;
	int notificationType;
	int filmId;
	string filmName;
};

Notification::Notification(string nameOfNotifMaker, int _notifMakerId,
					 int _notificationType, int _filmId = 0, string _filmName = 0){

	notifMakerName = nameOfNotifMaker;
	notifMakerId = _notifMakerId;
	notificationType = _notificationType;
	if (_notificationType == PUBLISHER_BUOUGTYOURFILM_NOTIF || _notificationType == PUBLISHER_RATEDYOURFILM_NOTIF || PUBLISHER_COMMENTEDYOURFILM_NOTIF){
		filmId = _filmId;
		filmName = _filmName;
	}
	else{
		filmId = 0;
		filmName = "";
	}
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
				<< NotifMakerId << " register new film."<<endl;
	if(notificationType == USER_COMMENTREPLY_NOTIF)
		cout << "Publisher " << notifMakerName << " with id " 
				<< NotifMakerId << " reply to your comment."<<endl;
}







class INotification{
public:
	INotification();
	void addNotification(string nameOfNotifMaker, int NotifMakerId,
			 int notificationType, int filmId = 0, string _filmName = 0);
	int showNewNotifications();
	int showAllNotifications();
private:
	vector <Notification*> unreadNotifications;//important note: if you pup then push imedieatly the order would fail
											   // the way is a for loop (backward) ...  
	vector <Notification*> readNotifications;
};











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