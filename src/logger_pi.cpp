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


#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include <wx/aui/aui.h>
#include <wx/datetime.h>
#include <wx/file.h>

#include "logger_pi.h"

#ifndef DECL_EXP
#ifdef __WXMSW__
#  define DECL_EXP     __declspec(dllexport)
#else
#  define DECL_EXP
#endif
#endif


// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return new logger_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}


//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

int logger_pi::Init(void)
{
      printf("logger_pi Init()\n");

//      m_plogger_window = NULL;
      m_config_dialog = NULL;

      // Get a pointer to the opencpn display canvas, to use as a parent for windows created
      m_parent_window = GetOCPNCanvasWindow();

      // Create the Context Menu Items

      //    In order to avoid an ASSERT on msw debug builds,
      //    we need to create a dummy menu to act as a surrogate parent of the created MenuItems
      //    The Items will be re-parented when added to the real context meenu
      wxMenu dummy_menu;

      wxMenuItem *pmi = new wxMenuItem(&dummy_menu, -1, _("Show logger plugin config"));
      m_show_id = AddCanvasContextMenuItem(pmi, this );
      SetCanvasContextMenuItemViz(m_show_id, true);

      wxMenuItem *pmih = new wxMenuItem(&dummy_menu, -1, _("Hide logger plugin config"));
      m_hide_id = AddCanvasContextMenuItem(pmih, this );
      SetCanvasContextMenuItemViz(m_hide_id, false);

/*
        m_plogger_window = new LoggerWindow(m_parent_window, wxID_ANY);

        m_AUImgr = GetFrameAuiManager();
        m_AUImgr->AddPane(m_plogger_window);
        m_AUImgr->GetPane(m_plogger_window).Name(_T("Logger plugin config"));

        m_AUImgr->GetPane(m_plogger_window).Float();
        m_AUImgr->GetPane(m_plogger_window).FloatingPosition(300,30);

        m_AUImgr->GetPane(m_plogger_window).Caption(_T("AUI Managed Demo Window"));
        m_AUImgr->GetPane(m_plogger_window).CaptionVisible(true);
        m_AUImgr->GetPane(m_plogger_window).GripperTop(true);
        m_AUImgr->GetPane(m_plogger_window).CloseButton(true);
        m_AUImgr->GetPane(m_plogger_window).Show(false);
        m_AUImgr->Update();
*/

      return (
           INSTALLS_CONTEXTMENU_ITEMS     |
           WANTS_NMEA_SENTENCES           |
           USES_AUI_MANAGER
            );
}

bool logger_pi::DeInit(void)
{
//      printf("logger_pi DeInit()\n");
//      m_AUImgr->DetachPane(m_plogger_window);

      if(m_config_dialog)
      {
            m_config_dialog->Close();
            m_config_dialog->Destroy();
      }
      
      return true;
}

int logger_pi::GetAPIVersionMajor()
{
      return MY_API_VERSION_MAJOR;
}

int logger_pi::GetAPIVersionMinor()
{
      return MY_API_VERSION_MINOR;
}

int logger_pi::GetPlugInVersionMajor()
{
      return PLUGIN_VERSION_MAJOR;
}

int logger_pi::GetPlugInVersionMinor()
{
      return PLUGIN_VERSION_MINOR;
}

wxString logger_pi::GetCommonName()
{
      return _("Logger");
}

wxString logger_pi::GetShortDescription()
{
      return _("Logger PlugIn for OpenCPN");
}

wxString logger_pi::GetLongDescription()
{
      return _("Logger PlugIn for OpenCPN\n\
Logs all incoming NMEA sentences to a log file.");

}

void logger_pi::SetNMEASentence(wxString &sentence)
{
//      printf("logger_pi::SetNMEASentence\n");

	// log the sentence

	wxDateTime now = wxDateTime::Now();
//	now.Format(wxT("%c"), wxDateTime::CET)
	wxString dateFormatted = now.FormatISODate();
	wxString nmeaLogfileName;

	// determine ais or gps
//	wxString source = wxT("");
//	m_launcher->GetSource(source);
//	if (source.Contains(_T("AIS"))) {
//		nmeaLogfileName = wxT("ais.") + dateFormatted + wxT(".nmea");
//	} else {
		nmeaLogfileName = wxT("gps.") + dateFormatted + wxT(".nmea");
//	}

	wxFile nmeaLogOut(nmeaLogfileName, wxFile::write_append);
	nmeaLogOut.Write(sentence);
	nmeaLogOut.Close();


/*      if(m_plogger_window)
      {
            m_plogger_window->SetSentence(sentence);
      }*/
}


void logger_pi::OnContextMenuItemCallback(int id)
{
    wxLogMessage(_T("logger_pi OnContextMenuCallBack()"));

         ::wxBell();


      if(NULL == m_config_dialog)
            m_config_dialog = new ConfigDialog(m_parent_window);

      m_config_dialog->Show();

}

void logger_pi::UpdateAuiStatus(void)
{
      //    This method is called after the PlugIn is initialized
      //    and the frame has done its initial layout, possibly from a saved wxAuiManager "Perspective"
      //    It is a chance for the PlugIn to syncronize itself internally with the state of any Panes that
      //    were added to the frame in the PlugIn ctor.

      //    We use this callback here to keep the context menu selection in sync with the window state


/*  
      wxAuiPaneInfo &pane = m_AUImgr->GetPane(m_plogger_window);
      if(!pane.IsOk())
            return;

      printf("update %d\n",pane.IsShown());

      SetCanvasContextMenuItemViz(m_hide_id, pane.IsShown());
      SetCanvasContextMenuItemViz(m_show_id, !pane.IsShown());
*/
}


//----------------------------------------------------------------
//
//    Demo Window Implementation
//
//----------------------------------------------------------------

BEGIN_EVENT_TABLE(LoggerWindow, wxWindow)
  EVT_PAINT ( LoggerWindow::OnPaint )
  EVT_SIZE(LoggerWindow::OnSize)


END_EVENT_TABLE()

LoggerWindow::LoggerWindow(wxWindow *pparent, wxWindowID id)
      :wxWindow(pparent, id, wxPoint(10,10), wxSize(200,200),
             wxSIMPLE_BORDER, _T("OpenCPN PlugIn"))
{
      mLat = 0.0;
      mLon = 1.0;
      mSog = 2.0;
      mCog = 3.0;
      mVar = 4.0;
}

LoggerWindow::~LoggerWindow()
{
}

void LoggerWindow::OnSize(wxSizeEvent& event)
{
      printf("LoggerWindow OnSize()\n");
}


void LoggerWindow::SetSentence(wxString &sentence)
{
      m_NMEA0183 << sentence;

      bool bGoodData = false;

      if(m_NMEA0183.PreParse())
      {
            if(m_NMEA0183.LastSentenceIDReceived == _T("RMC"))
            {
                  if(m_NMEA0183.Parse())
                  {
                              if(m_NMEA0183.Rmc.IsDataValid == NTrue)
                              {
                                    float llt = m_NMEA0183.Rmc.Position.Latitude.Latitude;
                                    int lat_deg_int = (int)(llt / 100);
                                    float lat_deg = lat_deg_int;
                                    float lat_min = llt - (lat_deg * 100);
                                    mLat = lat_deg + (lat_min/60.);
                                    if(m_NMEA0183.Rmc.Position.Latitude.Northing == South)
                                          mLat = -mLat;

                                    float lln = m_NMEA0183.Rmc.Position.Longitude.Longitude;
                                    int lon_deg_int = (int)(lln / 100);
                                    float lon_deg = lon_deg_int;
                                    float lon_min = lln - (lon_deg * 100);
                                    mLon = lon_deg + (lon_min/60.);
                                    if(m_NMEA0183.Rmc.Position.Longitude.Easting == West)
                                          mLon = -mLon;

                                    mSog = m_NMEA0183.Rmc.SpeedOverGroundKnots;
                                    mCog = m_NMEA0183.Rmc.TrackMadeGoodDegreesTrue;

                                    if(m_NMEA0183.Rmc.MagneticVariationDirection == East)
                                          mVar =  m_NMEA0183.Rmc.MagneticVariation;
                                    else if(m_NMEA0183.Rmc.MagneticVariationDirection == West)
                                          mVar = -m_NMEA0183.Rmc.MagneticVariation;

                                    bGoodData = true;

                              }
                        }
                  }
        }

      //    Got the data, now do something with it

      if(bGoodData)
      {
            Refresh(false);
      }
}

void LoggerWindow::OnPaint(wxPaintEvent& event)
{
      wxLogMessage(_T("logger_pi onpaint"));

      wxPaintDC dc ( this );

//      printf("onpaint\n");

      {
            dc.Clear();

            wxString data;
            data.Printf(_T("Lat: %g "), mLat);
            dc.DrawText(data, 10, 10);

            data.Printf(_T("Lon: %g"), mLon);
            dc.DrawText(data, 10, 40);

            data.Printf(_T("Sog: %g"), mSog);
            dc.DrawText(data, 10, 70);

            data.Printf(_T("Cog: %g"), mCog);
            dc.DrawText(data, 10, 100);
      }
}
