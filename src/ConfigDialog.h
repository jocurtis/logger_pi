///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __ConfigDialog__
#define __ConfigDialog__

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/filepicker.h>
#include <wx/sizer.h>
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
		wxStaticText* m_staticText4;
		wxFilePickerCtrl* m_log_location_picker;
		wxButton* m_ok_button;
		wxButton* m_cancel_button;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnOkButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ConfigDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Logger config"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,150 ), long style = wxDEFAULT_DIALOG_STYLE );
		~ConfigDialog();
	
};

#endif //__ConfigDialog__
