#pragma once
#include <string>

using std::string;

enum NoticeType {NOTICE_CLOSE, NOTICE_SIM_CHANGE, NOTICE_SIM_PAUSE, NOTICE_SPEED_CHANGE};

class Notice
{
private:
	NoticeType type;
	string msg;

protected:
	void setType(NoticeType t);

public:
	Notice();
	~Notice();

	NoticeType getType();

	void setMessage(string str);
	string getMessage();

};

