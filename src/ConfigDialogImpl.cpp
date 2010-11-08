#include <wx/wx.h>
#include <wx/string.h>
#include <wx/utils.h>

#include "ConfigDialogImpl.h"

ConfigDialogImpl::ConfigDialogImpl(wxWindow*& parent)
: ConfigDialog(parent)
{

}

void ConfigDialogImpl::SaveConfig() {
//    printf("Saving config...%s\n", m_log_location_picker->GetPath().wchar_str());
    wxPuts(wxT("LOL"));
    wxPuts(m_log_location_picker->GetPath());
    wxPrintf(wxT("wut"));
    fflush(stdout);
    fflush(stderr);

// WHY THE FUCK IS THIS NOT WORKING?  I HATE C++!!!
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
