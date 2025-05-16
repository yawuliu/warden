#include <iostream>
#include "Event/Event.h"
#include "Storm/StormInit.h"
#include "Game/Client.h"
//#include <QGuiApplication>

int WardenMain(int argc, char **argv) {
//    QGuiApplication app(argc, argv);
    StormInitialize();

    // TODO
    // - error log setup
    // - misc other setup

    if (InitializeGlobal()) {
        EventDoMessageLoop();

        // TODO
        // sub_406B70();
    }
    // TODO
    // - misc cleanup
//    return app.exec();
}

int main(int argc, char **argv) {
    WardenMain(argc, argv);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
