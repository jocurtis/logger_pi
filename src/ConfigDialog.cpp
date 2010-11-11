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
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("GPS log location") ), wxHORIZONTAL );
	
	m_gps_log_enabled = new wxCheckBox( this, wxID_ANY, wxT("enabled"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer2->Add( m_gps_log_enabled, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_gps_log_location_picker = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxEmptyString, wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_SAVE|wxFLP_USE_TEXTCTRL );
	sbSizer2->Add( m_gps_log_location_picker, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( sbSizer2, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("AIS log location") ), wxHORIZONTAL );
	
	m_ais_log_enabled = new wxCheckBox( this, wxID_ANY, wxT("enabled"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer6->Add( m_ais_log_enabled, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_ais_log_location_picker = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_SAVE|wxFLP_USE_TEXTCTRL );
	sbSizer6->Add( m_ais_log_location_picker, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( sbSizer6, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Combined log location") ), wxHORIZONTAL );
	
	m_combined_log_enabled = new wxCheckBox( this, wxID_ANY, wxT("enabled"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer7->Add( m_combined_log_enabled, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_combined_log_location_picker = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_SAVE|wxFLP_USE_TEXTCTRL );
	sbSizer7->Add( m_combined_log_location_picker, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( sbSizer7, 1, wxEXPAND, 5 );
	
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
