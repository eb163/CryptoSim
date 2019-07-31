#include "NoticeClose.h"



NoticeClose::NoticeClose()
{
	setType(NoticeType::NOTICE_CLOSE);
	setMessage("NOTICE: Program is shutting down!");
}


NoticeClose::~NoticeClose()
{

}
