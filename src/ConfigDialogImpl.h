#include "ConfigDialog.h"

class ConfigDialogImpl : public ConfigDialog {

public:
	ConfigDialogImpl(wxWindow*& parent);

private:
	void SaveConfig();
	void OnClose( wxCloseEvent& event );
	void OnOKButtonClicked( wxCommandEvent& event );
	void OnCancelButtonClicked( wxCommandEvent& event );
};

