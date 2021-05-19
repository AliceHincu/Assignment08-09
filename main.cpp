#include <iostream>
#include "GUI.h"
#include <QtWidgets/QApplication>
#include <ConsoleUI.h>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    RepositoryShelter repoShelter;
    ServiceAdmin serviceAdmin(repoShelter);
    ServiceUser serviceUser(repoShelter);
/*
    ConsoleUI console(serviceAdmin, serviceUser);
    console.run();
    return 0;*/
    GUI gui(serviceAdmin, serviceUser);
    gui.show();

    return app.exec();
}
