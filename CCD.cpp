#include "StdAfx.h"
#include "CCD.h"


CCCD::CCCD(void)
{
	m_runstatus=RUNMODE_STOP;
	m_isinit=FALSE;
	m_ismono=FALSE;
}


CCCD::~CCCD(void)
{
}


BOOL CCCD::isCCDopen()
{
	return m_bisCCDopen;
}

string CCCD::getport()
{
	return m_sport;
}

//DS_RUNMODE CCCD::getCCDstatus()
//{
//	return m_ccdstatus;
//}

