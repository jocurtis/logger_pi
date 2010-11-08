/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  Logger Plugin
 * Author:   Joseph Curtis
 *
 ***************************************************************************
 *   Copyright (C) 2010 by David S. Register   *
 *   $EMAIL$   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
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
 */

#ifndef _LOGGERPI_H_
#define _LOGGERPI_H_

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#define     PLUGIN_VERSION_MAJOR    1
#define     PLUGIN_VERSION_MINOR    0

#define     MY_API_VERSION_MAJOR    1
#define     MY_API_VERSION_MINOR    1

#include "ocpn_plugin.h"

#include "nmea0183/nmea0183.h"

#include "ConfigDialog.h"

class LoggerWindow;

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------


class logger_pi : public opencpn_plugin
{
public:
      logger_pi(void *ppimgr):opencpn_plugin(ppimgr){}

//    The required PlugIn Methods
      int Init(void);
      bool DeInit(void);

      int GetAPIVersionMajor();
      int GetAPIVersionMinor();
      int GetPlugInVersionMajor();
      int GetPlugInVersionMinor();

      wxString GetCommonName();
      wxString GetShortDescription();
      wxString GetLongDescription();

//    The optional method overrides

      void SetNMEASentence(wxString &sentence);
      void OnContextMenuItemCallback(int id);

private:
      bool LoadConfig(void);
      bool SaveConfig(void);

      wxWindow         *m_parent_window;
      wxFileConfig     *m_pconfig;
      ConfigDialog     *m_config_dialog;
      wxAuiManager     *m_AUImgr;
      int               m_show_id;
      int               m_hide_id;
};



class LoggerWindow : public wxWindow
{
public:
      LoggerWindow(wxWindow *pparent, wxWindowID id);
      ~LoggerWindow();

      void OnPaint(wxPaintEvent& event);
      void SetSentence(wxString &sentence);
      void OnSize(wxSizeEvent& event);

      NMEA0183        m_NMEA0183;                 // Used to parse NMEA Sentences

      wxString          m_NMEASentence;
      double            mLat, mLon, mSog, mCog, mVar;

DECLARE_EVENT_TABLE()
};


#endif



