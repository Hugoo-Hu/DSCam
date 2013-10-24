
#pragma once


class Csettings
{
private:
	Csettings(void);
	static Csettings *singleton;

	string m_settingxml;

	//DOM
	MSXML2::IXMLDOMDocument2Ptr m_pxmldoc;
	BOOL m_isloaded;

public:
	~Csettings(void);

	static Csettings *getInstance()
	{
		if(singleton==NULL)
			singleton=new Csettings;
		return singleton;
	}

	string get_vsport();
	void set_vsport(string port);

	string getpath2save();
	void setpath2save(string path);

	//DS_FILE_TYPE getimagetype();
	//void setimagetype(DS_FILE_TYPE imagetype);

	void get_image_attr(string &path,DS_FILE_TYPE &type);
	void set_image_attr(string path,DS_FILE_TYPE type);

	double get_wl_step();
	void set_wl_step(double wl_step);

	int get_wl_cap_times();
	void set_wl_cap_times(int times=1);


	//DOM
	HRESULT load();
	void save();
	void release();

	string get_vsport_dom();
	void set_vsport_dom(string port);

	void get_image_attr_dom(string &path,DS_FILE_TYPE &type);
	void set_image_attr_dom(string path,DS_FILE_TYPE type);

	double get_wl_step_dom();
	void set_wl_step_dom(double wl_step);

	int get_wl_cap_times_dom();
	void set_wl_cap_times_dom(int times=1);
};

