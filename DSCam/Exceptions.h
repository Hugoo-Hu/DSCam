

#pragma once

// VsGui error codes
class Cerr_vs_not_open:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_bad_handle:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_not_initialized:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_already_open:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_interface_not_available:public exception
{
public:
	const char *what()const;
};

class Cerr_vs_communication:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_no_dev_present:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_communication_send:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_communication_reply:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_communication_general:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_block_send:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_block_receive:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_no_ready_reply:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_cmd_2_long:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_set_param:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_get_param:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_busy:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_no_character_echo:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_set_block_timeout:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_set_float:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_initialize_fail:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_get_error_fail:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_version_read:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_config_read:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_attempt_to_set_ro_param:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_null_ptr:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_internal_range:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_2_many_dev_open:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_no_waveplates_present:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_int_obj_create:public exception
{
public:
	const char *what() const;
};

class Cerr_vs_int_waveplatestage_invalid:public exception
{
public:
	const char *what() const;
};

class Cerr_other:public exception
{
public:
	const char *what() const;
	Cerr_other(int err);

private:
	int m_ierr;
	char m_szerr[60];
};