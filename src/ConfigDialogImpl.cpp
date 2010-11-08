#include <wx/wx.h>
#include <wx/string.h>
#include <wx/utils.h>

#include "ConfigDialogImpl.h"

ConfigDialogImpl::ConfigDialogImpl(wxWindow*& parent)
: ConfigDialog(parent)
{

}

void ConfigDialogImpl::SaveConfig() {
    wxLogMessage(wxT("Log location: ") + m_log_location_picker->GetPath());
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
