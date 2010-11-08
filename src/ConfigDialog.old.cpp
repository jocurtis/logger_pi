/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  Logger plugin
 * Author:   Joseph Curtis
 *
 ***************************************************************************
 *   Copyright (C) 2010 by Sean D'Epagnier   *
 *   $EMAIL$   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 *
 */

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/listimpl.cpp>    // toh, 2009.02.22

#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "wx/notebook.h"
#include "wx/datetime.h"
#include "wx/colordlg.h"

#include "../../../include/ocpn_plugin.h"

#include "ConfigDialog.h"

#define ID_CHOICE_BODY  wxID_HIGHEST + 1


/*!
 * ConfigDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( ConfigDialog, wxDialog )

/*!
 * ConfigDialog event table definition
 */

BEGIN_EVENT_TABLE( ConfigDialog, wxDialog )
    EVT_BUTTON( ID_ConfigDialog_CANCEL, ConfigDialog::OnConfigDialogCancelClick )
    EVT_BUTTON( ID_ConfigDialog_OK, ConfigDialog::OnConfigDialogOkClick )
    EVT_CLOSE(ConfigDialog::OnClose )
END_EVENT_TABLE()

/*!
 * ConfigDialog constructors
 */
ConfigDialog::ConfigDialog() {}

ConfigDialog::ConfigDialog( wxWindow* parent, wxWindowID id,
                     const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
      Create(parent, id, caption, pos, size, style);
      GetSizer()->SetSizeHints(this);
      Centre();
}


ConfigDialog::~ConfigDialog( )
{
}


/*!
 * ConfigDialog creator
 */

bool ConfigDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{

    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    SetDialogTitle(wxT("Logger config"));

	wxMessageBox(wxT("Quit program?"), wxT("Confirm"), wxOK, parent);


    CreateControls();

    return TRUE;
}

/*!
 * Control creation for ConfigDialog
 */

void ConfigDialog::CreateControls()
{
////@begin ConfigDialog content construction

    ConfigDialog* itemDialog1 = this;

    wxBoxSizer* itemBox = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBox);

//    wxNotebook *itemNotebook = new wxNotebook( itemDialog1, wxID_STATIC, wxDefaultPosition, wxSize(-1, -1), wxNB_TOP );
//    itemBox->Add(itemNotebook, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    wxPanel *itemPanel1 = new wxPanel( itemDialog1, wxID_STATIC, wxDefaultPosition, wxDefaultSize,
                                       wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
  //  itemNotebook->AddPage(itemPanel1, _("Sight"));
    itemBox->Add(itemPanel1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    wxGridSizer* itemGrid1 = new wxGridSizer(3);
    itemPanel1->SetSizer(itemGrid1);

    itemGrid1->Add(new wxStaticText( itemPanel1, wxID_STATIC, _("Type"), wxDefaultPosition, wxDefaultSize, 0 ), 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);


    wxBoxSizer* buttonBox = new wxBoxSizer(wxHORIZONTAL);
    itemBox->Add(buttonBox, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_CancelButton = new wxButton( itemDialog1, ID_ConfigDialog_CANCEL, _("Cancel"),
                                   wxDefaultPosition, wxDefaultSize, 0 );
    buttonBox->Add(m_CancelButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_OKButton = new wxButton( itemDialog1, ID_ConfigDialog_OK, _("OK"),
                               wxDefaultPosition, wxDefaultSize, 0 );
    buttonBox->Add(m_OKButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    m_OKButton->SetDefault();


}

/*!
 * Should we show tooltips?
 */

bool ConfigDialog::ShowToolTips()
{
    return TRUE;
}


void ConfigDialog::SetDialogTitle(wxString title)
{
      SetTitle(title);
}

void ConfigDialog::OnConfigDialogCancelClick( wxCommandEvent& event )
{
   wxPuts(wxT("CANCEL!"));
   EndModal(wxID_CANCEL);
}


void ConfigDialog::OnConfigDialogOkClick( wxCommandEvent& event )
{
   wxPuts(wxT("OK!"));
   EndModal(wxID_OK);
}

void ConfigDialog::OnClose(wxCloseEvent& event)
{
   EndModal(wxID_CANCEL);
}

