#pragma once
#include <string>

using std::string;

enum NoticeType {CLOSE, SIM_CHANGE, SIM_PAUSE};

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

