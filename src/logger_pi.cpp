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
//      printf("logger_pi::SetNMEASentence\n");

	// log the sentence

  wxDateTime now = wxDateTime::Now();
  wxString dateFormatted = now.FormatISODate();
  
  // determine ais or gps
  //	wxString source = wxT("");
  //	m_launcher->GetSource(source);
  //	if (source.Contains(_T("AIS"))) {
  //		nmeaLogfileName = wxT("ais.") + dateFormatted + wxT(".nmea");
  //	} else {
  wxString nmeaLogDir = now.Format(wxT("%Y/%B"), wxDateTime::CET);
  wxString nmeaLogfileName = now.Format(wxT("%Y/%B/gps.%Y-%m-%d.nmea"), wxDateTime::CET);
  
  // todo: actually get basedir
  
  wxLogMessage(nmeaLogfileName);
  wxFileName::Mkdir(nmeaLogDir, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
  
  // nmeaLogfileName = wxT("gps.") + dateFormatted + wxT(".nmea");
//	}
  
  wxFile nmeaLogOut(nmeaLogfileName, wxFile::write_append);
  nmeaLogOut.Write(sentence);
  nmeaLogOut.Close();
}


void logger_pi::OnContextMenuItemCallback(int id)
{
    wxLogMessage(_T("logger_pi OnContextMenuCallBack()"));

         ::wxBell();


      if(NULL == m_config_dialog)
            m_config_dialog = new ConfigDialogImpl(m_parent_window);

      m_config_dialog->Show();

}

bool logger_pi::LoadConfig(void)
{
      wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

      if(pConf)
      {
/*            pConf->SetPath ( _T( "/Settings" ) );
            pConf->Read ( _T( "GRIBUseHiDef" ),  &m_bGRIBUseHiDef, 0 );
            pConf->Read ( _T( "ShowGRIBIcon" ),  &m_bGRIBShowIcon, 1 );


            m_grib_dialog_sx = pConf->Read ( _T ( "GRIBDialogSizeX" ), 300L );
            m_grib_dialog_sy = pConf->Read ( _T ( "GRIBDialogSizeY" ), 540L );
            m_grib_dialog_x =  pConf->Read ( _T ( "GRIBDialogPosX" ), 20L );
            m_grib_dialog_y =  pConf->Read ( _T ( "GRIBDialogPosY" ), 20L );

            if((m_grib_dialog_x < 0) || (m_grib_dialog_x > m_display_width))
                  m_grib_dialog_x = 5;
            if((m_grib_dialog_y < 0) || (m_grib_dialog_y > m_display_height))
                  m_grib_dialog_y = 5;

            pConf->SetPath ( _T ( "/Directories" ) );
            pConf->Read ( _T ( "GRIBDirectory" ), &m_grib_dir );
*/
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
/*            pConf->SetPath ( _T ( "/Settings" ) );
            pConf->Write ( _T ( "GRIBUseHiDef" ), m_bGRIBUseHiDef );
            pConf->Write ( _T ( "ShowGRIBIcon" ), m_bGRIBShowIcon );

            pConf->Write ( _T ( "GRIBDialogSizeX" ),  m_grib_dialog_sx );
            pConf->Write ( _T ( "GRIBDialogSizeY" ),  m_grib_dialog_sy );
            pConf->Write ( _T ( "GRIBDialogPosX" ),   m_grib_dialog_x );
            pConf->Write ( _T ( "GRIBDialogPosY" ),   m_grib_dialog_y );

            pConf->SetPath ( _T ( "/Directories" ) );
            pConf->Write ( _T ( "GRIBDirectory" ), m_grib_dir );
*/
            return true;
      }
      else
            return false;
}

