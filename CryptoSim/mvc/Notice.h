#pragma once
enum NoticeType {CLOSE, MOVED_MESSAGE, RECOLOR_MESSAGE, CHANGED_TEXT, CLOCK_UPDATE};

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

