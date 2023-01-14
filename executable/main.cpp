#include <iostream>
#include "Application.hpp"

int main(int argc, char **argv) {
    FE::Application app{argc, argv};

    try {
        return app.Run();
    } catch (const FE::Exception &ex) {
        LOG(ERROR) << "Unexpected error has occurred: " << ex.what();
        return 1;
    }
}

