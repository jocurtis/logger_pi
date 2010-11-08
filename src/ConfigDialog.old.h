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

#ifndef _ConfigDialog_H_
#define _ConfigDialog_H_

/*!
 * Includes
 */
#include "wx/listctrl.h"
#include "wx/calctrl.h"

/*!
 * Forward declarations
 */

class   wxListCtrl;
/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_ConfigDialog 7000
#define SYMBOL_ConfigDialog_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_ConfigDialog_TITLE _("Logger Config")
#define SYMBOL_ConfigDialog_IDNAME ID_ConfigDialog
#define SYMBOL_ConfigDialog_SIZE wxSize(400, 300)
#define SYMBOL_ConfigDialog_POSITION wxDefaultPosition

#define ID_ConfigDialog_CANCEL 7010
#define ID_ConfigDialog_OK 7011


////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

/*!
 * ConfigDialog class declaration
 */

class ConfigDialog: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( ConfigDialog )
    DECLARE_EVENT_TABLE()

public:
   enum {ALTITUDE, AZIMUTH, LUNAR};

    /// Constructors
    ConfigDialog();
    ConfigDialog(wxWindow* parent, wxWindowID id = SYMBOL_ConfigDialog_IDNAME,
        const wxString& caption = SYMBOL_ConfigDialog_TITLE,
        const wxPoint& pos = SYMBOL_ConfigDialog_POSITION,
        const wxSize& size = SYMBOL_ConfigDialog_SIZE,
        long style = SYMBOL_ConfigDialog_STYLE );
    ~ConfigDialog( );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ConfigDialog_IDNAME,
                 const wxString& caption = SYMBOL_ConfigDialog_TITLE,
                 const wxPoint& pos = SYMBOL_ConfigDialog_POSITION,
                 const wxSize& size = SYMBOL_ConfigDialog_SIZE,
                 long style = SYMBOL_ConfigDialog_STYLE );

    void CreateControls();

//    void SetColorScheme(ColorScheme cs);
    void SetDialogTitle(wxString title);

    void OnConfigDialogCancelClick( wxCommandEvent& event );
    void OnConfigDialogOkClick( wxCommandEvent& event );
    void OnClose(wxCloseEvent& event);


    /// Should we show tooltips?
    static bool ShowToolTips();

    wxButton*     m_CancelButton;
    wxButton*     m_OKButton;
};



#endif
    // _ConfigDialog_H_
