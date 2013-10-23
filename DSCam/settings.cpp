#include "StdAfx.h"

//#include <boost/program_options/detail/utf8_codecvt_facet.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#define BOOST_UTF8_BEGIN_NAMESPACE namespace boost { namespace property_tree {
#define BOOST_UTF8_END_NAMESPACE }}
#define BOOST_UTF8_DECL
#include <boost/detail/utf8_codecvt_facet.hpp>
//#include <libs/detail/

#include "settings.h"

//#ifdef _DEBUG
//#pragma comment(lib,"libboost_program_options-vc100-mt-sgd-1_54.lib")
//#else
//#pragma comment(lib,"libboost_program_options-vc100-mt-s-1_54.lib")
//#endif

using namespace boost::property_tree;

Csettings *Csettings::singleton=NULL;

Csettings::Csettings(void)
{
	TCHAR tmp[MAX_PATH];
	memset(tmp,0,MAX_PATH);
	::GetModuleFileName(NULL,tmp,MAX_PATH);

	PathRemoveFileSpec(tmp);
	m_settingxml=tmp;
	m_settingxml+="\\settings.xml";

	m_isloaded=FALSE;
	m_pxmldoc=NULL;
	//Â·¾¶ÖÐÔÊÐíÓÐÖÐÎÄ×Ö·û
	std::locale::global(std::locale(""));
}


Csettings::~Csettings(void)
{
}

string Csettings::get_vsport()
{
	using boost::property_tree::ptree;
	//using boost::program_options::detail::utf8_codecvt_facet;
	using std::locale;

	ptree pt;
	//std::locale loc(locale(),new utf8_codecvt_facet);
	std::locale loc(locale(""));
	
	string strret(_T(""));

	try
	{
		read_xml(m_settingxml,pt,0,loc);
		strret=pt.get<string>("settings.VsGui.serialport");
	}
	catch(std::exception &e)
	{
		strret="";
		string strerr=e.what();
		MessageBox(AfxGetApp()->GetMainWnd()->GetSafeHwnd(),strerr.c_str(),_T("´íÎó"),MB_ICONERROR);
	}


	return strret;
}

void Csettings::set_vsport(string port)
{
	using boost::property_tree::ptree;
	using std::locale;
	std::locale loc(locale(""));
	ptree pt;

	try
	{
		read_xml(m_settingxml,pt,0,loc);
		pt.put<string>("settings.VsGui.serialport",port);
		write_xml(m_settingxml,pt,loc);
	}
	catch(std::exception &e)
	{
		string strerr=e.what();
		MessageBox(AfxGetApp()->GetMainWnd()->GetSafeHwnd(),strerr.c_str(),_T("´íÎó"),MB_ICONERROR);
	}
}

string Csettings::getpath2save()
{
	using boost::property_tree::ptree;
	using std::locale;
	std::locale loc(locale(""));
	ptree pt;
	string strret(_T(""));

	try
	{
		read_xml(m_settingxml,pt,0,loc);
		strret=pt.get<string>("settings.CCD.image.<xmlattr>.path2save");
	}
	catch(std::exception &e)
	{
		string strerr=e.what();
		MessageBox(AfxGetApp()->GetMainWnd()->GetSafeHwnd(),strerr.c_str(),_T("´íÎó"),MB_ICONERROR);
		strret="";
	}

	return strret;
}

void Csettings::setpath2save(string path)
{
	using boost::property_tree::ptree;
	using std::locale;
	std::locale loc(locale(""));
	ptree pt;

	try
	{
		read_xml(m_settingxml,pt,0,loc);
		pt.put<string>("settings.CCD.image.<xmlattr>.path2save",path);
		write_xml(m_settingxml,pt,loc);
	}
	catch(std::exception &e)
	{
		string strerr=e.what();
		MessageBox(AfxGetApp()->GetMainWnd()->GetSafeHwnd(),strerr.c_str(),_T("´íÎó"),MB_ICONERROR);
	}
}

void Csettings::get_image_attr(string &path,DS_FILE_TYPE &type)
{
	using boost::property_tree::ptree;
	using std::locale;
	std::locale loc(locale(""));
	ptree pt;

	try
	{
		read_xml(m_settingxml,pt,0,loc);
		path=pt.get<string>("settings.CCD.image.<xmlattr>.path2save");
		string strtype=pt.get<string>("settings.CCD.image.<xmlattr>.type");
		transform(strtype.begin(),strtype.end(),strtype.begin(),tolower);
		if(strtype=="jpg")
			type=FILE_JPG;
		else if(strtype=="bmp")
			type=FILE_BMP;
		else if(strtype=="raw")
			type=FILE_RAW;
		else
			type=FILE_JPG;
	}
	catch(std::exception &e)
	{
		string strerr=e.what();
		MessageBox(AfxGetApp()->GetMainWnd()->GetSafeHwnd(),strerr.c_str(),_T("´íÎó"),MB_ICONERROR);
		path="";
		type=FILE_JPG;
	}
}

void Csettings::set_image_attr(string path,DS_FILE_TYPE type)
{
	using boost::property_tree::ptree;
	using std::locale;
	std::locale loc(locale(""));
	ptree pt;

	try
	{
		string strtype;
		switch(type)
		{
			case FILE_JPG:
				strtype="jpg";
				break;
			case FILE_BMP:
				strtype="bmp";
				break;
			case FILE_RAW:
				strtype="raw";
				break;
			default:
				strtype="jpg";
				break;
		}
		read_xml(m_settingxml,pt,0,loc);
		pt.put<string>("settings.CCD.image.<xmlattr>.path2save",path);
		pt.put<string>("settings.CCD.image.<xmlattr>.type",strtype);
		write_xml(m_settingxml,pt,loc);
	}
	catch(std::exception &e)
	{
		string strerr=e.what();
		MessageBox(AfxGetApp()->GetMainWnd()->GetSafeHwnd(),strerr.c_str(),_T("´íÎó"),MB_ICONERROR);
	}
}

double Csettings::get_wl_step()
{
	using boost::property_tree::ptree;
	using std::locale;
	std::locale loc(locale(""));
	ptree pt;
	double wl_step=0.0f;
	string strvalue(_T(""));

	try
	{
		read_xml(m_settingxml,pt);
		strvalue=pt.get<string>("settings.VsGui.wl_step");
		wl_step=_tstof(strvalue.c_str());
	}
	catch(std::exception &e)
	{
		string strerr=e.what();
		MessageBox(AfxGetApp()->GetMainWnd()->GetSafeHwnd(),strerr.c_str(),_T("´íÎó"),MB_ICONERROR);
		wl_step=0.0f;
	}

	return wl_step;
}

void Csettings::set_wl_step(double wl_step)
{
	using boost::property_tree::ptree;
	using std::locale;
	std::locale loc(locale(""));
	ptree pt;
	string strvalue(_T(""));

	try
	{
		TCHAR buf[20];
		memset(buf,0,20);
		_stprintf_s(buf,20,_T("%.2f"),wl_step);
		strvalue=buf;
		read_xml(m_settingxml,pt);
		pt.put<string>("settings.VsGui.wl_step",strvalue);
		write_xml(m_settingxml,pt);
	}
	catch(std::exception &e)
	{
		string strerr=e.what();
		MessageBox(AfxGetApp()->GetMainWnd()->GetSafeHwnd(),strerr.c_str(),_T("´íÎó"),MB_ICONERROR);
	}
}

HRESULT Csettings::load()
{
	HRESULT hr=S_OK;
	hr=m_pxmldoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
		return hr;

	if(m_pxmldoc->load(m_settingxml.c_str())!=VARIANT_TRUE)
		hr=S_FALSE;

	m_isloaded=TRUE;

	return hr;
}

void Csettings::save()
{
	m_pxmldoc->save(m_settingxml.c_str());
}

void Csettings::release()
{
	//m_pxmldoc->Release();
	m_pxmldoc.Release();
	m_pxmldoc=NULL;
	m_isloaded=FALSE;
}

string Csettings::get_vsport_dom()
{
	if(m_pxmldoc==NULL||!m_isloaded)
		return "";
	
	string strvalue;
	MSXML2::IXMLDOMNodePtr xmlnode=m_pxmldoc->selectSingleNode(_T("settings/VsGui/serialport"));
	strvalue=xmlnode->text;

	return strvalue;
}

void Csettings::set_vsport_dom(string port)
{
	if(m_pxmldoc==NULL||!m_isloaded)
		return ;

	MSXML2::IXMLDOMNodePtr xmlnode=m_pxmldoc->selectSingleNode(_T("settings/VsGui/serialport"));
	xmlnode->text=port.c_str();

	m_pxmldoc->save(m_settingxml.c_str());
}

void Csettings::get_image_attr_dom(string &path,DS_FILE_TYPE &type)
{
	if(m_pxmldoc==NULL||!m_isloaded)
	{
		path="";
		type=FILE_JPG;
		return ;
	}

	MSXML2::IXMLDOMNodePtr xmlnode=m_pxmldoc->selectSingleNode(_T("settings/CCD/image"));
	MSXML2::IXMLDOMElementPtr xmlelement=xmlnode;
	_variant_t var;
	//try
	//{
		
	var=xmlelement->getAttribute(_T("path2save"));
	path=(LPCTSTR)_bstr_t(var);
	//}
	//catch(_com_error &e)
	//{
	//	string strerr;
	//	//strerr=e.Description();
	//	strerr=e.ErrorMessage();
	//}
	string strtype;
	var=xmlelement->getAttribute(_T("type"));
	strtype=(LPCSTR)_bstr_t(var);

	transform(strtype.begin(),strtype.end(),strtype.begin(),tolower);
	if(strtype=="jpg")
		type=FILE_JPG;
	else if(strtype=="bmp")
		type=FILE_BMP;
	else if(strtype=="raw")
		type=FILE_RAW;
	else
		type=FILE_JPG;
}

void Csettings::set_image_attr_dom(string path,DS_FILE_TYPE type)
{
	if(m_pxmldoc==NULL||!m_isloaded)
	{
		return ;
	}
	MSXML2::IXMLDOMNodePtr xmlnode=m_pxmldoc->selectSingleNode(_T("settings/CCD/image"));
	MSXML2::IXMLDOMElementPtr xmlelement=xmlnode;
	xmlelement->setAttribute(_T("path2save"),path.c_str());
	
	string strvalue;
	switch(type)
	{
		case FILE_JPG:
			strvalue="jpg";
			break;
		case FILE_BMP:
			strvalue="bmp";
			break;
		case FILE_RAW:
			strvalue="raw";
			break;
		default:
			strvalue="jpg";
			break;
	}
	xmlelement->setAttribute(_T("type"),strvalue.c_str());

	m_pxmldoc->save(m_settingxml.c_str());
}

double Csettings::get_wl_step_dom()
{
	if(m_pxmldoc==NULL||!m_isloaded)
	{
		return 0.0f;
	}

	double wl_step=0.0f;
	MSXML2::IXMLDOMNodePtr xmlnode=m_pxmldoc->selectSingleNode(_T("settings/VsGui/wl_step"));
	string strvalue=xmlnode->text;
	wl_step=_tstof(strvalue.c_str());

	return wl_step;
}

void Csettings::set_wl_step_dom(double wl_step)
{
	if(m_pxmldoc==NULL||!m_isloaded)
	{
		return ;
	}
	TCHAR buf[20];
	memset(buf,0,20);
	_stprintf_s(buf,20,_T("%.2f"),wl_step);
	MSXML2::IXMLDOMNodePtr xmlnode=m_pxmldoc->selectSingleNode(_T("settings/VsGui/wl_step"));
	xmlnode->text=buf;

	m_pxmldoc->save(m_settingxml.c_str());

}
