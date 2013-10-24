#include "StdAfx.h"

#include "VsGui.h"


extern string getCommPort();

CVsGui::CVsGui(void)
{
	m_comport="";
	m_isopen=FALSE;
	m_vshwnd=NULL;
	m_vsinfo.maxWl=0.0f;
	m_vsinfo.minWl=0.0f;
	m_vsinfo.serNo=0;
	m_vsinfo.version=0;
	m_wl_curr=0.0f;
	m_wl_max_cap=0.0f;
	m_wl_min_cap=0.0f;
	m_wl_step=0.0f;
}


CVsGui::~CVsGui(void)
{
	m_vshwnd=NULL;
}



//BOOL CVsGui::isVsOpen()
//{
//	return m_bisVsOpen;
//}
//
//std::string CVsGui::get_vs_port()
//{
//	return m_sport;
//}

//VS_SETUP CVsGui::get_vsinfo()
//{
//	return m_vsinfo;
//}
//
//void CVsGui::vsopen(string strport)
//{
//	if(m_bisVsOpen) return;
//
//	int err=0;
//	if(!VsOpen(&m_vshwnd,strport.c_str(),&err))
//	{
//		m_vshwnd=NULL;
//		switch(err)
//		{
//			case VSD_ERR_NOERROR:
//				break;
//			case VSD_ERR_COMMUNICATION_ERROR:
//				throw Cerr_vs_communication();
//				break;
//			case VSD_ERR_NO_CHARACTER_ECHO:
//				//m_bisVsOpen=TRUE;
//				//m_sport=strport;
//				//throw Cerr_vs_no_character_echo();
//				break;
//			case VSD_ERR_ALREADY_OPEN:
//				//m_bisVsOpen=TRUE;
//				//m_sport=strport;
//				//throw Cerr_vs_already_open();
//				break;
//			case VSD_ERR_NOT_OPEN:
//				throw Cerr_vs_not_open();
//				break;
//			case VSD_ERR_INTERFACE_NOT_AVAILABLE:
//				throw Cerr_vs_interface_not_available();
//				break;
//			case VSD_ERR_NO_DEVICE_PRESENT:
//				throw Cerr_vs_no_dev_present();
//				break;
//			default:
//				throw Cerr_other(err);
//				break;
//		}
//	}
//
//	m_bisVsOpen=TRUE;
//	m_sport=strport;
//}
//
//void CVsGui::vsopen(VS_HANDLE *phwnd, string strport)
//{
//	if(m_bisVsOpen) return;
//
//	int err=0;
//	if(!VsOpen(phwnd,strport.c_str(),&err))
//	{
//		switch(err)
//		{
//			case VSD_ERR_NOERROR:
//				break;
//			case VSD_ERR_COMMUNICATION_ERROR:
//				throw Cerr_vs_communication();
//				break;
//			case VSD_ERR_NO_CHARACTER_ECHO:
//				throw Cerr_vs_no_character_echo();
//				break;
//			default:
//				throw Cerr_other(err);
//				break;
//		}
//	}
//
//	m_bisVsOpen=TRUE;
//}
//
//void CVsGui::vsclose()
//{
//	VsClose(m_vshwnd);
//	m_bisVsOpen=FALSE;
//	m_vshwnd=NULL;
//}
//
//void CVsGui::vsclose(VS_HANDLE hwnd)
//{
//	VsClose(hwnd);
//	m_bisVsOpen=FALSE;
//}
//
//BOOL CVsGui::clear_pending_cmd(VS_HANDLE hwnd)
//{
//	if(!m_bisVsOpen||hwnd==NULL)
//		return FALSE;
//	return VsClearPendingCommands(hwnd);
//}
//
//BOOL CVsGui::clear_pending_cmd()
//{
//	if(!m_bisVsOpen||m_vshwnd==NULL)
//		return FALSE;
//
//	return VsClearPendingCommands(m_vshwnd);
//}
//
//BOOL CVsGui::get_filter_identity(VS_HANDLE hwnd,VS_SETUP &vs_info)
//{
//	if(!m_bisVsOpen||hwnd==NULL)
//		return FALSE;
//
//	int version=0;
//	int serno=0;
//	double minwl=0.0F,maxwl=0.0F;
//	BOOL ret=VsGetFilterIdentity(hwnd,&version,&serno,&minwl,&maxwl);
//	vs_info.version=version;
//	vs_info.serNo=serno;
//	vs_info.minWl=minwl;
//	vs_info.maxWl=maxwl;
//
//	return ret;
//}
//
//BOOL CVsGui::get_filter_identity(VS_SETUP &vs_info)
//{
//	if(!m_bisVsOpen||m_vshwnd==NULL)
//		return FALSE;
//
//	int version=0;
//	int serno=0;
//	double minwl=0.0F,maxwl=0.0F;
//	BOOL ret=VsGetFilterIdentity(m_vshwnd,&version,&serno,&minwl,&maxwl);
//	vs_info.version=version;
//	vs_info.serNo=serno;
//	vs_info.minWl=minwl;
//	vs_info.maxWl=maxwl;
//
//	return ret;
//}
//
//BOOL CVsGui::get_filter_identity()
//{
//	if(!m_bisVsOpen||m_vshwnd==NULL)
//		return FALSE;
//
//	int version=0;
//	int serno=0;
//	double minwl=0.0F,maxwl=0.0F;
//	BOOL ret=VsGetFilterIdentity(m_vshwnd,&version,&serno,&minwl,&maxwl);
//	m_vsinfo.version=version;
//	m_vsinfo.serNo=serno;
//	m_vsinfo.minWl=minwl;
//	m_vsinfo.maxWl=maxwl;
//
//	m_wl_min_cap=minwl;
//	m_wl_max_cap=maxwl;
//
//	//ret=VsGetWavelengthStep(m_vshwnd,m_dsweepstep);
//
//	return ret;
//}
//
//BOOL CVsGui::get_temperature(VS_HANDLE hwnd,double &temperature)
//{
//	if(!m_bisVsOpen||hwnd==NULL)
//		return FALSE;
//	return VsGetTemperature(hwnd,&temperature);
//}
//
//BOOL CVsGui::get_temperature(double &temperature)
//{
//	if(!m_bisVsOpen||m_vshwnd==NULL)
//		return FALSE;
//	return VsGetTemperature(m_vshwnd,&temperature);
//}
//
//BOOL CVsGui::get_wavelength(VS_HANDLE hwnd,double &wavelength)
//{
//	if(!m_bisVsOpen||&wavelength==NULL||hwnd==NULL)
//		return FALSE;
//
//	return VsGetWavelength(hwnd,&wavelength);
//}
//
//BOOL CVsGui::get_wavelength(double &wavelength)
//{
//	if(!m_bisVsOpen||m_vshwnd==NULL)
//		return FALSE;
//
//	return VsGetWavelength(m_vshwnd,&wavelength);
//}
//
//BOOL CVsGui::set_wavelength_step(double step)
//{
//	if(!m_bisVsOpen||m_vshwnd==NULL)
//		return FALSE;
//
//	return VsSetWavelengthStep(m_vshwnd,step,TRUE);
//}
//
//BOOL CVsGui::set_wavelength_step(VS_HANDLE hwnd,double step)
//{
//	if(!m_bisVsOpen||hwnd==NULL)
//		return FALSE;
//
//	return VsSetWavelengthStep(hwnd,step,TRUE);
//}
//
//BOOL CVsGui::set_wavelength(VS_HANDLE hwnd,double wavelength)
//{
//	if(!m_bisVsOpen||hwnd==NULL)
//		return FALSE;
//
//	return VsSetWavelength(hwnd,wavelength,TRUE);
//}
//
//BOOL CVsGui::set_wavelength(double wavelength)
//{
//	if(!m_bisVsOpen||m_vshwnd==NULL)
//		return FALSE;
//
//	return VsSetWavelength(m_vshwnd,wavelength,TRUE);
//}