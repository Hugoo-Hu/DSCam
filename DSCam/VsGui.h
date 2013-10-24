#pragma once

#include "Exceptions.h"

class CVsGui
{
public:
	CVsGui(void);
	~CVsGui(void);

//	BOOL isVsOpen();
//	std::string get_vs_port();
//	void vsopen(string strport) throw(Cerr_vs_communication,/*Cerr_vs_no_character_echo,Cerr_vs_already_open,*/ \
//		Cerr_vs_not_open,Cerr_vs_interface_not_available,Cerr_vs_no_dev_present,Cerr_other);
//	void vsclose();
//
//	void vsopen(VS_HANDLE *phwnd,string strport) throw(Cerr_vs_communication,Cerr_vs_no_character_echo,Cerr_other);	
//	void vsclose(VS_HANDLE hwnd);
//
//	BOOL clear_pending_cmd(VS_HANDLE hwnd);
//	BOOL clear_pending_cmd();
//
//	BOOL get_filter_identity(VS_HANDLE hwnd,VS_SETUP &vs_info);
//	BOOL get_filter_identity(VS_SETUP &vs_info);
//	BOOL get_filter_identity();
//
//	BOOL get_temperature(VS_HANDLE hwnd,double &temperature);
//	BOOL get_temperature(double &temperature);
//
//	BOOL get_wavelength(VS_HANDLE hwnd,double &wavelength);
//	BOOL get_wavelength(double &wavelength);
//
//	BOOL set_wavelength_step(VS_HANDLE hwnd,double step);
//	BOOL set_wavelength_step(double step);
//
//	BOOL set_wavelength(VS_HANDLE hwnd,double wavelength);
//	BOOL set_wavelength(double wavelength);
//
//	VS_SETUP get_vsinfo();
//
//private:
//	BOOL m_bisVsOpen;
//	
//	
//
//	//the filter's range of wavelength
//	double m_dminwl;
//	double m_dmaxwl;
//	
//
//public:
//	double m_dsweepstep;
//	double m_dsweepinterval;
//	double m_wl_curr;
//	double m_wl_min_cap;
//	double m_wl_max_cap;
//
//	//double m_wl_max_cap_prev;
//	//double m_wl_min_cap_prev;
//	//double m_wl_step_prev;
//
//	std::string m_sport;

public:
	BOOL m_isopen;
	string m_comport;
	int m_wl_cap_times;
	double m_wl_curr;
	//double m_wl_min;
	//double m_wl_max;
	double m_wl_min_cap;
	double m_wl_max_cap;
	double m_wl_step;
	VS_SETUP m_vsinfo;

//public:
//	BOOL open();

//private:
	VS_HANDLE m_vshwnd;

};

