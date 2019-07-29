#include "Notice.h"

void Notice::setType(NoticeType t)
{
	type = t;
}

Notice::Notice()
{
}


Notice::~Notice()
{
}

NoticeType Notice::getType()
{
	return type;
}

void Notice::setMessage(string str)
{
	msg = str;
}

string Notice::getMessage()
{
	return msg;
}
