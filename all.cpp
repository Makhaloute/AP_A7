#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>


using namespace std;




class User{

};

struct Comment{
	int id;
	string comment;
	vector <string> replyes;
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
	double rate;
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
private:
	vector <Film*> films;
};


class Imain(){
public:

private:

};





int main (){
	;
}