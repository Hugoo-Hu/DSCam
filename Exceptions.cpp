
#include "stdafx.h"
#include "Exceptions.h"

const char *Cerr_vs_not_open::what() const
{
	return "VsGui is not open.";
}

const char *Cerr_vs_already_open::what() const
{	
	return "VsGui is already open.";
}

const char *Cerr_vs_bad_handle::what() const
{
	return "the handle of the window is invalid.";
}

const char *Cerr_vs_interface_not_available::what() const
{
	return "the interface of the VsGui is not available.";
}

Cerr_other::Cerr_other(int err)
{
	m_ierr=err;
	memset(m_szerr,0,60);
	_stprintf_s(m_szerr,60,"other error, the error code is %d",m_ierr);
}

const char *Cerr_other::what() const
{
	return m_szerr;
}

const char *Cerr_vs_2_many_dev_open::what()  const
{
	return "too many device open.";
}

const char *Cerr_vs_attempt_to_set_ro_param::what() const
{
	return "fail to attempt to set RO parameter.";
}

const char *Cerr_vs_block_receive::what() const 
{
	return "block receive error.";
}

const char *Cerr_vs_block_send::what() const
{
	return "block send error.";
}

const char *Cerr_vs_busy::what() const
{
	return "VsGui is busy with cmd.";
}

const char *Cerr_vs_cmd_2_long::what() const
{
	return "the length of cmd is too long.";
}

const char *Cerr_vs_communication::what() const
{
	return "there is something wrong with communication.";
}

const char *Cerr_vs_communication_general::what() const
{
	return "general error on communication.";
}

const char *Cerr_vs_communication_reply::what() const
{
	return "communication error on reply.";
}

const char *Cerr_vs_config_read::what() const
{
	return "there is something wrong with configuration reading.";
}

const char *Cerr_vs_get_error_fail::what() const
{
	return "fail to get error.";
}

const char *Cerr_vs_get_param::what() const 
{
	return "fail to get parameter.";
}

const char *Cerr_vs_initialize_fail::what() const
{
	return "fail to initialize the device.";
}

const char *Cerr_vs_internal_range::what() const
{
	return "out of internal range.";
}

const char *Cerr_vs_int_obj_create::what() const
{
	return "fail to create object.";
}

const char *Cerr_vs_int_waveplatestage_invalid::what() const
{
	return "the waveplatestage is invalid.";
}

const char *Cerr_vs_not_initialized::what() const
{
	return "the device is not initialized.";
}

const char *Cerr_vs_no_character_echo::what() const
{
	return "no echo.";
}

const char *Cerr_vs_no_dev_present::what() const
{
	return "no device is present.";
}

const char *Cerr_vs_no_ready_reply::what() const
{
	return "no reply for the isready cmd.";
}

const char *Cerr_vs_no_waveplates_present::what() const
{
	return "no waveplates is present.";
}

const char *Cerr_vs_null_ptr::what() const
{
	return "the pointer is null.";
}

const char *Cerr_vs_set_block_timeout::what() const
{
	return "the action to set block is timeout.";
}

const char *Cerr_vs_set_float::what() const
{
	return "fail to set float.";
}

const char *Cerr_vs_set_param::what() const
{
	return "fail to set parameter.";
}

const char *Cerr_vs_version_read::what() const
{
	return "fail to read the version of device.";
}