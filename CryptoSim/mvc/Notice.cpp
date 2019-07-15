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
