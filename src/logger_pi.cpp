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
#include <wx/filefn.h>
#include <wx/dir.h>

#include "logger_pi.h"
#include "ConfigDialogImpl.h"

#include <wx/filename.h>

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

      m_config_dialog = NULL;

      // Get a pointer to the opencpn display canvas, to use as a parent for windows created
      m_parent_window = GetOCPNCanvasWindow();
      m_pconfig = GetOCPNConfigObject();

      LoadConfig();

      // Create the Context Menu Items

      //    In order to avoid an ASSERT on msw debug builds,
      //    we need to create a dummy menu to act as a surrogate parent of the created MenuItems
      //    The Items will be re-parented when added to the real context menu
      wxMenu dummy_menu;

      wxMenuItem *pmi = new wxMenuItem(&dummy_menu, -1, _("Show logger plugin config"));
      m_show_id = AddCanvasContextMenuItem(pmi, this );
      SetCanvasContextMenuItemViz(m_show_id, true);

      wxMenuItem *pmih = new wxMenuItem(&dummy_menu, -1, _("Hide logger plugin config"));
      m_hide_id = AddCanvasContextMenuItem(pmih, this );
      SetCanvasContextMenuItemViz(m_hide_id, false);

      return (
           INSTALLS_CONTEXTMENU_ITEMS     |
           WANTS_NMEA_SENTENCES           |
           WANTS_CONFIG
            );
}

bool logger_pi::DeInit(void)
{
//      printf("logger_pi DeInit()\n");

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
	// TODO: * Differentiate between AIS AND GPS
	//	 * Clean up code and submit?

  switch (determineNMEASentenceType(sentence)) {
    case GPS:
	  if (gpsLogEnabled) {
		appendSentenceToFile(gpsLogfileFullPath, sentence);
	  }
    break;
    case AIS:
	if (aisLogEnabled) {
		appendSentenceToFile(aisLogfileFullPath, sentence);
	}
    break;
    default:
    break;
  }

  if (combinedLogEnabled) {
    appendSentenceToFile(combinedLogfileFullPath, sentence);
  }


}

void logger_pi::appendSentenceToFile(wxString fileFullPath, wxString sentence) {
  wxDateTime now = wxDateTime::Now();

  // format the gps path
  wxString logfileFullPathFormatted = now.Format(fileFullPath, wxDateTime::CET);

  // get the base dir and create if necessary
  wxString baseDir = ::wxPathOnly(logfileFullPathFormatted);
  wxFileName::Mkdir(baseDir, 0755, wxPATH_MKDIR_FULL);
  
  // log it
  wxFile logOut(logfileFullPathFormatted, wxFile::write_append);
  logOut.Write(sentence);
  logOut.Close();
}

NMEASentenceType logger_pi::determineNMEASentenceType(wxString sentence) {
    if (sentence.StartsWith(wxT("$GP"), NULL)) {
        return GPS;
    } else if (sentence.StartsWith(wxT("!AIVDM"), NULL)) {
        return AIS;
    } else {
        return UNKNOWN;
    }
}


void logger_pi::OnContextMenuItemCallback(int id)
{
    //wxLogMessage(_T("logger_pi OnContextMenuCallBack()"));

         ::wxBell();

      LoadConfig();

      if(m_config_dialog == NULL) {
            m_config_dialog = new ConfigDialogImpl(m_parent_window, this);
      }

      m_config_dialog->UpdateFromLogger();
      m_config_dialog->Show();

}

bool logger_pi::LoadConfig(void)
{
      wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

      if(pConf)
      {
	    wxLogMessage(wxT("Loading settings"));
            pConf->SetPath ( _T( "/Settings" ) );
	    pConf->Read ( _T( "LOGGERcombinedLogfileFullPath" ),  &combinedLogfileFullPath, _T(COMBINED_LOGFILE_FULL_PATH_DEFAULT) );
	    wxLogMessage(_T ("LOGGERcombinedLogfileFullPath: ") + combinedLogfileFullPath);

	    pConf->Read ( _T( "LOGGERgpsLogfileFullPath" ),  &gpsLogfileFullPath, _T(GPS_LOGFILE_FULL_PATH_DEFAULT) );
	    wxLogMessage(_T ("LOGGERgpsLogfileFullPath: ") + gpsLogfileFullPath);

	    pConf->Read ( _T( "LOGGERaisLogfileFullPath" ),  &aisLogfileFullPath, _T(AIS_LOGFILE_FULL_PATH_DEFAULT) );
	    wxLogMessage(_T ("LOGGERaisLogfileFullPath: ") + aisLogfileFullPath);

	    pConf->Read ( _T( "LOGGERcombinedLogEnabled" ),  &combinedLogEnabled, COMBINED_LOG_ENABLED_DEFAULT );
	    wxLogMessage(_T ("LOGGERcombinedLogEnabled: ") + combinedLogEnabled);

	    pConf->Read ( _T( "LOGGERgpsLogEnabled" ),  &gpsLogEnabled, GPS_LOG_ENABLED_DEFAULT );
	    wxLogMessage(_T ("LOGGERgpsLogEnabled: ") + gpsLogEnabled);

	    pConf->Read ( _T( "LOGGERaisLogEnabled" ),  &aisLogEnabled, AIS_LOG_ENABLED_DEFAULT );
	    wxLogMessage(_T ("LOGGERaisLogEnabled: ") + aisLogEnabled);

            return true;
      }
      else
            return false;
}

bool logger_pi::SaveConfig(void)
{
      wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

      if(pConf)
      {
	    wxLogMessage(wxT("Saving settings"));
            pConf->SetPath ( _T ( "/Settings" ) );
            pConf->Write ( _T ( "LOGGERcombinedLogfileFullPath" ), combinedLogfileFullPath );
	    wxLogMessage(_T ("LOGGERcombinedLogfileFullPath: ") + combinedLogfileFullPath);

            pConf->Write ( _T ( "LOGGERgpsLogfileFullPath" ), gpsLogfileFullPath );
	    wxLogMessage(_T ("LOGGERgpsLogfileFullPath: ") + gpsLogfileFullPath);

            pConf->Write ( _T ( "LOGGERaisLogfileFullPath" ), aisLogfileFullPath );
	    wxLogMessage(_T ("LOGGERaisLogfileFullPath: ") + aisLogfileFullPath);

            pConf->Write ( _T ( "LOGGERcombinedLogEnabled" ), combinedLogEnabled );
	    wxLogMessage(_T ("LOGGERcombinedLogEnabled: ") + combinedLogEnabled);

            pConf->Write ( _T ( "LOGGERgpsLogEnabled" ), gpsLogEnabled );
	    wxLogMessage(_T ("LOGGERgpsLogEnabled: ") + gpsLogEnabled);

            pConf->Write ( _T ( "LOGGERaisLogEnabled" ), aisLogEnabled );
	    wxLogMessage(_T ("LOGGERaisLogEnabled: ") + aisLogEnabled);

            return true;
      }
      else
            return false;
}

