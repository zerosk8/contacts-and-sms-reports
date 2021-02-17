#include "gui_contacts_and_sms_reports.hpp"

GUIContactsAndSmsReports::GUIContactsAndSmsReports(){}

GUIContactsAndSmsReports::GUIContactsAndSmsReports(const Glib::ustring & applicationId)
{
    application = Gtk::Application::create(applicationId);
    builder = Gtk::Builder::create_from_file(GLADE_FILE_PATH);
    builder->get_widget(GLADE_ID_MAIN_WINDOW,mainWindow);
    builder->get_widget(GLADE_ID_CONTACTS_FILE_PATH_BUTTON,contactsFilePathButton);
    builder->get_widget(GLADE_ID_SMS_FILE_PATH_BUTTON,smsFilePathButton);
    builder->get_widget(GLADE_ID_DESTINATION_PATH_BUTTON,destinationPathButton);
    builder->get_widget(GLADE_ID_EXECUTE_BUTTON,executeButton);
    builder->get_widget(GLADE_ID_QUIT_BUTTON,quitButton);
    builder->get_widget(GLADE_ID_MESSAGE_DIALOG,messageDialog);
    builder->get_widget(GLADE_ID_MESSAGE_DIALOG_OK_BUTTON,messageDialogOkButton);
    ConnectWidgetsEventSignalsToFunctions();
}

int GUIContactsAndSmsReports::Run()
{
    return application->run(*mainWindow);
}

GUIContactsAndSmsReports::~GUIContactsAndSmsReports(){}

/**************************************/

void GUIContactsAndSmsReports::ConnectWidgetsEventSignalsToFunctions()
{
    contactsFilePathButton->signal_file_set().connect(sigc::mem_fun(*this,
    &GUIContactsAndSmsReports::OnGUIContactsFilePathButtonFileSetEvent));
    smsFilePathButton->signal_file_set().connect(sigc::mem_fun(*this,
    &GUIContactsAndSmsReports::OnGUISmsFilePathButtonFileSetEvent));
    destinationPathButton->signal_file_set().connect(sigc::mem_fun(*this,
    &GUIContactsAndSmsReports::OnGUIDestinationPathButtonFileSetEvent));
    executeButton->signal_clicked().connect(sigc::mem_fun(*this,
    &GUIContactsAndSmsReports::OnGUIExecuteButton));
    quitButton->signal_clicked().connect(sigc::mem_fun(*this,
    &GUIContactsAndSmsReports::OnGUIQuitButton));
    messageDialogOkButton->signal_clicked().connect(sigc::mem_fun(*this,
    &GUIContactsAndSmsReports::OnMessageDialogOkButton));
}

void GUIContactsAndSmsReports::displayInformationMessageDialog(const std::string & informationMessage, 
const std::string & informationText)
{
    messageDialog->set_message(informationMessage);
    messageDialog->set_secondary_text(informationText);
    Glib::PropertyProxy<Gtk::MessageType> dialogMessageType
    (messageDialog->property_message_type());
    dialogMessageType.set_value(Gtk::MessageType::MESSAGE_INFO);
    messageDialog->run();
}

void GUIContactsAndSmsReports::displaySuccessMessageDialog(const std::string & successText)
{
    messageDialog->set_message(MESSAGE_DIALOG_SUCCESS_MESSAGE);
    messageDialog->set_secondary_text(successText);
    Glib::PropertyProxy<Gtk::MessageType> dialogMessageType
    (messageDialog->property_message_type());
    dialogMessageType.set_value(Gtk::MessageType::MESSAGE_INFO);
    messageDialog->run();
}

void GUIContactsAndSmsReports::displayErrorMessageDialog(const std::string & errorText)
{
    size_t positionOfSeparator = errorText.find_first_of(MESSAGE_DIALOG_ERROR_TEXT_SEPARATOR_CHAR);
    std::string message = UtilsString::TrimWhiteSpacesFromEndOfString
    (UtilsString::TrimWhiteSpacesFromStartOfString(errorText.substr(0,positionOfSeparator)));
    std::string secondaryText = UtilsString::TrimWhiteSpacesFromEndOfString
    (UtilsString::TrimWhiteSpacesFromStartOfString(errorText.substr(positionOfSeparator + 1)));
    messageDialog->set_message(message);
    messageDialog->set_secondary_text(secondaryText);
    Glib::PropertyProxy<Gtk::MessageType> dialogMessageType
    (messageDialog->property_message_type());
    dialogMessageType.set_value(Gtk::MessageType::MESSAGE_ERROR);
    messageDialog->run();
}

void GUIContactsAndSmsReports::OnGUIContactsFilePathButtonFileSetEvent(){}

void GUIContactsAndSmsReports::OnGUISmsFilePathButtonFileSetEvent(){}

void GUIContactsAndSmsReports::OnGUIDestinationPathButtonFileSetEvent(){}

void GUIContactsAndSmsReports::OnGUIExecuteButton()
{
    if(contactsFilePathButton->get_filename().empty() && smsFilePathButton->get_filename().empty())
    {
        displayInformationMessageDialog(MESSAGE_DIALOG_MISSING_INPUT_MESSAGE,
        MESSAGE_DIALOG_MISSING_INPUT_FILE_TEXT);
        return;
    }
    if(destinationPathButton->get_filename().empty())
    {
        displayInformationMessageDialog(MESSAGE_DIALOG_MISSING_OUTPUT_MESSAGE,
        MESSAGE_DIALOG_MISSING_OUTPUT_PATH_TEXT);
        return;
    }
    std::pair<bool,std::string> applicationExecResult;
    applicationExec = ExecContactsAndSmsReports(contactsFilePathButton->get_filename(),
        smsFilePathButton->get_filename(),UtilsFileSystem::
        GetFileOrDirectoryPathString(destinationPathButton->get_filename(),
        DIR_NAME_FOR_REPORT_RESULTS));
    applicationExecResult = applicationExec.Run();
    if(!applicationExecResult.first)
    {
        std::cerr << applicationExecResult.second << std::endl;
        displayErrorMessageDialog(applicationExecResult.second);
    }
    else
    {
        displaySuccessMessageDialog(MESSAGE_DIALOG_SUCCESS_TEXT + 
        destinationPathButton->get_filename());   
    }
}

void GUIContactsAndSmsReports::OnGUIQuitButton()
{
    mainWindow->close();
}

void GUIContactsAndSmsReports::OnMessageDialogOkButton()
{
    messageDialog->hide();
}