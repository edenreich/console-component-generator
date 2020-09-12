#include <console/application.h>
#include "commands/make_command.h"

int main(int argc, char* argv[])
{
    Console::Application app(argc, argv);

    app.setApplicationName("Codegen util");
    app.setApplicationUsage("console-gen <command> [options]");
    app.setApplicationDescription("Codegen util for console component");
    app.setApplicationVersion("1.0.0");
    app.setAutoPrintHelp(true);

    app.addCommand(new MakeCommand);

    return app.run();
}