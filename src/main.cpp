#include "SingleInstanceManager/SingleInstanceManager.hpp"

#include <QApplication>
#include <iostream>
#include <optional>
#include <string>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    std::optional<std::string> parameters = std::nullopt;
    for (int i = 1; i < argc; i++) {
        if (!parameters.has_value()) { parameters = std::make_optional<std::string>(""); }
        parameters.value().append(argv[i]).append(" ");
    }

    SingleInstanceManager singleInstanceManager(
        [&](std::optional<std::string> data) {
            /*
                We can do something interesting here with our data since we have access to our main function's scope.
                Since this function is a public member of the class we can also just replace it with something else later on.
                For this example, we just print the data to stdout.
            */ 
            std::cout << (data.has_value() ? data.value() : "A new instance was started but no parameters were passed.") << std::endl;
        },
        parameters
    );

    return app.exec();
}
