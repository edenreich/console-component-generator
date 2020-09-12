#include "make_command.h"

#include <iostream>
#include <fstream>

#if __APPLE__
#include <filesystem>
#elif
#include <experimental/filesystem>
#endif

namespace fs = std::experimental::filesystem;

/**
 * Retrieve the name of the command.
 *
 * @return std::string
 */
std::string MakeCommand::getName() { return "make:command"; }

/**
 * Retrieve the description of the command.
 *
 * @return std::string
 */
std::string MakeCommand::getDescription() { return "Generate a command in the commands directory"; }

/**
 * Retrieve the command options.
 *
 * @return Console::Types::AvailableOptions
 */
Types::AvailableOptions MakeCommand::getOptions()
{
    Types::AvailableOptions options;

    options["-n"] = std::pair<std::string, std::string>("--name", "The name of the command (e.g todo:list)");
    options["-c"] = std::pair<std::string, std::string>("--class", "The name of the class");

    return options;
}

/**
 * Handle the command.
 *
 * @param Console::Interfaces::InputInterface* input
 * @param Console::Interfaces::OutputInterface* output
 * @return ExitCode
 */
ExitCode MakeCommand::handle(Interfaces::InputInterface* input, Interfaces::OutputInterface* output)
{
    if (input->wantsHelp())
    {
        output->printCommandHelp(this);
        return ExitCode::NeedHelp;
    }

    if (input->getOption("name").empty() || input->getOption("class").empty())
    {
        output->warning("wrong options..");
        output->printCommandHelp(this);
        return ExitCode::NeedHelp;
    }

    if (!fs::exists(fs::path("commands")))
    {
        output->info("==> Creating commands directory..");
        fs::create_directory("commands");
    }

    std::string commandName = input->getOption("name");
    std::string className = input->getOption("class");
    std::string fileName = commandName;
    fileName[commandName.find(':')] = '_';

    output->info("==> Creating new command %s in commands directory..", commandName.c_str());

    std::ofstream headerFile(fs::path("commands/" + fileName + ".h"));

    headerFile << "#pragma once\n";
    headerFile << "\n";
    headerFile << "#include <console/interfaces/command_interface.h>\n";
    headerFile << "#include <console/types/collections.h>\n";
    headerFile << "\n";
    headerFile << "namespace Interfaces = Console::Interfaces;\n";
    headerFile << "namespace Types = Console::Types;\n";
    headerFile << "\n";
    headerFile << "/**\n";
    headerFile << " * @name " << commandName << "\n";
    headerFile << " */\n";
    headerFile << "class " << className << " : public Interfaces::CommandInterface\n";
    headerFile << "{\n";
    headerFile << "\n";
    headerFile << "public:\n";
    headerFile << "\n";
    headerFile << "    /**\n";
    headerFile << "     * Retrieve the name of the command.\n";
    headerFile << "     *\n";
    headerFile << "     * @return std::string\n";
    headerFile << "     */\n";
    headerFile << "    std::string getName() override;\n";
    headerFile << "\n";
    headerFile << "    /**\n";
    headerFile << "     * Retrieve the description of the command.\n";
    headerFile << "     *\n";
    headerFile << "     * @return std::string\n";
    headerFile << "     */\n";
    headerFile << "    std::string getDescription() override;\n";
    headerFile << "\n";
    headerFile << "    /**\n";
    headerFile << "     * Retrieve the command options.\n";
    headerFile << "     *\n";
    headerFile << "     * @return Types::AvailableOptions\n";
    headerFile << "     */\n";
    headerFile << "    Types::AvailableOptions getOptions() override;\n";
    headerFile << "\n";
    headerFile << "    /**\n";
    headerFile << "     * Handle the command.\n";
    headerFile << "     *\n";
    headerFile << "     * @param InputInterface* input\n";
    headerFile << "     * @param OutputInterface* output\n";
    headerFile << "     * @return ExitCode\n";
    headerFile << "     */\n";
    headerFile << "    ExitCode handle(Interfaces::InputInterface* input, Interfaces::OutputInterface* output) override;\n";
    headerFile << "\n";
    headerFile << "};\n";

    headerFile.close();

    std::ofstream cppFile(fs::path("commands/" + fileName + ".cpp"));

    cppFile << "#include \"" << fileName << ".h\"\n";
    cppFile << "\n";
    cppFile << "/**\n";
    cppFile << " * Retrieve the name of the command.\n";
    cppFile << " *\n";
    cppFile << " * @return std::string\n";
    cppFile << " */\n";
    cppFile << "std::string " << className << "::getName()\n";
    cppFile << "{\n";
    cppFile << "    return \"" << commandName << "\";\n";
    cppFile << "}\n";
    cppFile << "\n";
    cppFile << "/**\n";
    cppFile << " * Retrieve the description of the command.\n";
    cppFile << " *\n";
    cppFile << " * @return std::string\n";
    cppFile << " */\n";
    cppFile << "std::string " << className << "::getDescription()\n";
    cppFile << "{\n";
    cppFile << "    return \"__DESCRIPTION__\";\n";
    cppFile << "}\n";
    cppFile << "\n";
    cppFile << "/**\n";
    cppFile << " * Retrieve the command options.\n";
    cppFile << " *\n";
    cppFile << " * @return Types::AvailableOptions\n";
    cppFile << " */\n";
    cppFile << "Types::AvailableOptions " << className << "::getOptions()\n";
    cppFile << "{\n";
    cppFile << "    Types::AvailableOptions options;\n\n";
    cppFile << "    return options;\n";
    cppFile << "}\n";
    cppFile << "\n";
    cppFile << "/**\n";
    cppFile << " * Handle the command.\n";
    cppFile << " *\n";
    cppFile << " * @param InputInterface* input\n";
    cppFile << " * @param OutputInterface* output\n";
    cppFile << " * @return ExitCode\n";
    cppFile << " */\n";
    cppFile << "ExitCode " << className << "::handle(Interfaces::InputInterface* input, Interfaces::OutputInterface* output)\n";
    cppFile << "{\n";
    cppFile << "    if (input->wantsHelp()) {\n";
    cppFile << "        output->printCommandHelp(this);\n";
    cppFile << "        return ExitCode::NeedHelp;\n";
    cppFile << "    }\n";
    cppFile << "\n";
    cppFile << "	// Implement something\n";
    cppFile << "\n";
    cppFile << "    return ExitCode::Ok;\n";
    cppFile << "}\n";

    headerFile.close();

    return ExitCode::Ok;
}
