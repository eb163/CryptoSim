#pragma once
enum NoticeType {CLOSE, SIM_CHANGE};

class Notice
{
private:
	NoticeType type;

protected:
	void setType(NoticeType t);

public:
	Notice();
	~Notice();

	NoticeType getType();

};

