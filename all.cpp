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




class Notification{

};
class INotification{
public:

private:
	
};

class IFollow{

};

class User{
public:
	bool isThisPublisher();
	void addMoney(int amount);
	int showNewNotifications();
	int showAllNotifications();
	

	int addNotification(string nameOfUser, int userId, int notificationType, int filmId = 0);//unacceptable as is
																							 //parse in some other functions
private:
	INotification* notifs;
	IFollow* fowloings;
	int moneyStock;
	bool functionalType;
	int id;
	map <string,string> characteristics;
};





struct Comment{
	comment(int _id, string _comment):id(_id),comment(_comment);
	void addReply(string repy);
	int id;
	string comment;
	vector <string> replyes;
}
void addReply(string repy){
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


	bool isUserTheCreator(int userId);
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
private:
	vector <Film*> films;
};




class Imain(){
public:
	Imain(){films = new Ifilm();};
	void signup(map <string,string> carectristics , bool userType);
	int login(map <string,string> claims);


private:

	Ifilm * films;
	User* currentUser;
	vector<User*> users;
};


















int main (){;}