#include "CloseNotice.h"



CloseNotice::CloseNotice()
{
	setType(NoticeType::NOTICE_CLOSE);
	setMessage("NOTICE: Program is shutting down!");
}


CloseNotice::~CloseNotice()
{

}
