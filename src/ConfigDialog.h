///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __ConfigDialog__
#define __ConfigDialog__

#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/filepicker.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ConfigDialog
///////////////////////////////////////////////////////////////////////////////
class ConfigDialog : public wxDialog 
{
	private:
	
	protected:
		wxCheckBox* m_gps_log_enabled;
		wxFilePickerCtrl* m_gps_log_location_picker;
		wxCheckBox* m_ais_log_enabled;
		wxFilePickerCtrl* m_ais_log_location_picker;
		wxCheckBox* m_combined_log_enabled;
		wxFilePickerCtrl* m_combined_log_location_picker;
		wxButton* m_ok_button;
		wxButton* m_cancel_button;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnOKButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancelButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ConfigDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Logger config"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_DIALOG_STYLE );
		~ConfigDialog();
	
};

#endif //__ConfigDialog__
