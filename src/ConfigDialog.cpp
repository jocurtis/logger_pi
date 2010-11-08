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
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 2, 10, 10 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Log location"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer1->Add( m_staticText4, 0, wxALL, 5 );
	
	m_textCtrl4 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 250,-1 ), 0 );
	fgSizer1->Add( m_textCtrl4, 0, wxALL, 5 );
	
	m_button3 = new wxButton( this, wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_button3, 0, wxALL, 5 );
	
	m_button4 = new wxButton( this, wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_button4, 0, wxALL, 5 );
	
	this->SetSizer( fgSizer1 );
	this->Layout();
}

ConfigDialog::~ConfigDialog()
{
}
