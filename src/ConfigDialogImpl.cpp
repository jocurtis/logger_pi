#include <wx/wx.h>
#include <wx/string.h>
#include <wx/utils.h>

#include "ConfigDialogImpl.h"
#include "logger_pi.h"

ConfigDialogImpl::ConfigDialogImpl(wxWindow*& parent, logger_pi* m_logger_pi_ref)
: ConfigDialog(parent)
{
    m_logger_pi = m_logger_pi_ref;

    // populate GUI fields with config info
    UpdateFromLogger();

//    wxLogMessage(wxT("GPS logfile full path: ") + m_gps_log_location_picker->GetPath());
}

void ConfigDialogImpl::UpdateFromLogger() {
    m_gps_log_location_picker->SetPath(m_logger_pi->gpsLogfileFullPath);
    m_ais_log_location_picker->SetPath(m_logger_pi->aisLogfileFullPath);
    m_nmea_log_location_picker->SetPath(m_logger_pi->nmeaLogfileFullPath);
}

void ConfigDialogImpl::SaveConfig() {
    m_logger_pi->gpsLogfileFullPath = m_gps_log_location_picker->GetPath();
    m_logger_pi->aisLogfileFullPath = m_ais_log_location_picker->GetPath();
    m_logger_pi->nmeaLogfileFullPath = m_nmea_log_location_picker->GetPath();

//    wxLogMessage(wxT("gpsLogfileFullPath: ") + m_logger_pi->gpsLogfileFullPath);

    m_logger_pi->SaveConfig();
}

void ConfigDialogImpl::OnClose( wxCloseEvent& event ) {
    event.Skip();
    printf("Closed\n");
}

void ConfigDialogImpl::OnOKButtonClicked( wxCommandEvent& event ) {
    event.Skip();
    printf("OK\n");
    SaveConfig();
}

void ConfigDialogImpl::OnCancelButtonClicked( wxCommandEvent& event ) {
    event.Skip();
    printf("Cancel\n");
}
