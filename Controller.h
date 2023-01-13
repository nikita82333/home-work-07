#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <list>
#include <memory>
#include <ctime>
#include <string>

#include "Command.h"

/// <summary>
/// Class Controller - controller (invoker) in the implementation of the Command pattern.
/// </summary>
/// <param name="block_size">Command block size.</param>
class Controller {
public:
    explicit Controller(unsigned int block_size) :
        _block_size(block_size), _command_count(0), _brackets_count(0) {}

    void parse_command(std::unique_ptr<Command> command);
    void add_command(std::unique_ptr<Command> command);

private:
    void worker();
    void output_commands(std::ostream& out);
    void execute_commands();
    void clear_commands();
    static std::string time_to_string(std::time_t* time);

    std::list<std::unique_ptr<Command>> _commands;
    unsigned int _block_size;
    unsigned int _command_count;
    unsigned int _brackets_count;
    std::string _log_file_name;

};


#endif //CONTROLLER_H
