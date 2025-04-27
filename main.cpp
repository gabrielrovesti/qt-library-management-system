#include <QApplication>
#include <QStyleFactory>
#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Set application information
    QApplication::setApplicationName("Library Manager");
    QApplication::setApplicationVersion("1.0");
    QApplication::setOrganizationName("University of Padova");
    
    // Set application style
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    
    // Create main window
    MainWindow mainWindow;
    mainWindow.show();
    
    return app.exec();
}