#include "ConfigDialog.h"

class logger_pi;

class ConfigDialogImpl : public ConfigDialog {

public:
	ConfigDialogImpl(wxWindow*& parent, logger_pi* m_logger_pi_ref);
	void UpdateFromLogger();

private:
	void SaveConfig();
	void OnClose( wxCloseEvent& event );
	void OnOKButtonClicked( wxCommandEvent& event );
	void OnCancelButtonClicked( wxCommandEvent& event );

	logger_pi* m_logger_pi;
};

