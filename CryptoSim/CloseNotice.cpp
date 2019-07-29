#include "CloseNotice.h"



CloseNotice::CloseNotice()
{
	setType(NoticeType::CLOSE);
	setMessage("NOTICE: Program is shutting down!");
}


CloseNotice::~CloseNotice()
{

}
