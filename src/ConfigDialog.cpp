///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ConfigDialog.h"

///////////////////////////////////////////////////////////////////////////

ConfigDialog::ConfigDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	bSizer2->SetMinSize( wxSize( -1,20 ) ); 
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Log location"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer2->Add( m_staticText4, 0, wxALL, 10 );
	
	m_log_location_picker = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxEmptyString, wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_SAVE|wxFLP_USE_TEXTCTRL );
	bSizer2->Add( m_log_location_picker, 1, wxALL, 5 );
	
	bSizer1->Add( bSizer2, 1, wxALIGN_TOP|wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_ok_button = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_ok_button, 0, wxALL|wxALIGN_BOTTOM, 5 );
	
	m_cancel_button = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_cancel_button, 0, wxALL|wxALIGN_BOTTOM, 5 );
	
	bSizer1->Add( bSizer3, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ConfigDialog::OnClose ) );
	m_ok_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigDialog::OnOKButtonClicked ), NULL, this );
	m_cancel_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigDialog::OnCancelButtonClicked ), NULL, this );
}

ConfigDialog::~ConfigDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ConfigDialog::OnClose ) );
	m_ok_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigDialog::OnOKButtonClicked ), NULL, this );
	m_cancel_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigDialog::OnCancelButtonClicked ), NULL, this );
}
