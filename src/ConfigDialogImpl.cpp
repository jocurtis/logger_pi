/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  Logger Plugin
 * Author:   Joseph Curtis
 *
 ***************************************************************************
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

#include <wx/wx.h>
#include <wx/string.h>
#include <wx/utils.h>

#include "ConfigDialogImpl.h"
#include "logger_pi.h"

ConfigDialogImpl::ConfigDialogImpl(wxWindow*& parent, logger_pi* m_logger_pi_ref) : ConfigDialog(parent) {
  m_logger_pi = m_logger_pi_ref;
  
  // populate GUI fields with config info
  UpdateFromLogger();
}

void ConfigDialogImpl::UpdateFromLogger() {
  m_gps_log_location_picker->SetPath(m_logger_pi->gpsLogfileFullPath);
  m_ais_log_location_picker->SetPath(m_logger_pi->aisLogfileFullPath);
  m_combined_log_location_picker->SetPath(m_logger_pi->combinedLogfileFullPath);
  m_gps_log_enabled->SetValue(m_logger_pi->gpsLogEnabled);
  m_ais_log_enabled->SetValue(m_logger_pi->aisLogEnabled);
  m_combined_log_enabled->SetValue(m_logger_pi->combinedLogEnabled);
}

void ConfigDialogImpl::SaveConfig() {
  m_logger_pi->gpsLogfileFullPath = m_gps_log_location_picker->GetPath();
  m_logger_pi->aisLogfileFullPath = m_ais_log_location_picker->GetPath();
  m_logger_pi->combinedLogfileFullPath = m_combined_log_location_picker->GetPath();
  m_logger_pi->gpsLogEnabled = m_gps_log_enabled->GetValue();
  m_logger_pi->aisLogEnabled = m_ais_log_enabled->GetValue();
  m_logger_pi->combinedLogEnabled = m_combined_log_enabled->GetValue();

  m_logger_pi->SaveConfig();
}

void ConfigDialogImpl::OnClose( wxCloseEvent& event ) {
  event.Skip();
}

void ConfigDialogImpl::OnOKButtonClicked( wxCommandEvent& event ) {
  event.Skip();
  SaveConfig();
}

void ConfigDialogImpl::OnCancelButtonClicked( wxCommandEvent& event ) {
  event.Skip();
}
