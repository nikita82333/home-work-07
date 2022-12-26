#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>

#include "Controller.h"

void Controller::parse_command(std::unique_ptr<Command> command) {
    if (_command_count == 0) {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        _log_file_name = "bulk" + std::to_string(time) + ".log"; //as specified in the task
        //_log_file_name = "bulk" + time_to_string(&time) + ".log";  //human-readable log file name
    }

    if (command->get_text() == "EOF") {
        if (_brackets_count == 0) {
            worker();
        }
    } else if (command->get_text() == "{") {
        if (_brackets_count == 0) {
            worker();
        }
        ++_brackets_count;
    } else if (command->get_text() == "}") {
        if (_brackets_count > 0) {
            --_brackets_count;
        }
        if (_brackets_count == 0) {
            worker();
        }
    } else {
        add_command(std::move(command));
        ++_command_count;
        if (_command_count == _block_size && _brackets_count == 0) {
            worker();
        }
    }
}

void Controller::add_command(std::unique_ptr<Command> command) {
    _commands.emplace_back(std::move(command));
}

void Controller::worker() {
    if (_command_count != 0) {
        std::ofstream log_file(_log_file_name);
        if (log_file.is_open()) {
            output_commands(log_file);
            log_file.close();
        } else {
            std::cerr << "Error opening log file!" << std::endl;
        }
        output_commands(std::cout);
        execute_commands();//obviously not need
        clear_commands();
    }
}

void Controller::output_commands(std::ostream &out) {
    out << "bulk: ";
    for (auto it = _commands.cbegin(); it != _commands.cend(); ++it) {
        if (it != _commands.cbegin()) {
            out << ", ";
        }
        out << (*it)->get_text();
    }
    out << std::endl;
}

void Controller::execute_commands() {
    for (const auto& command : _commands) {
        command->execute();
    }
}

void Controller::clear_commands() {
    _commands.clear();
    _command_count = 0;
}

std::string Controller::time_to_string(std::time_t *time) {
    std::stringstream ss;
    std::tm* tm = localtime(time);
    ss << tm->tm_year + 1900 << "-" << std::setw(2) << std::setfill('0') << tm->tm_mon + 1 << "-"
       << std::setw(2) << std::setfill('0') << tm->tm_mday << "_"
       << std::setw(2) << std::setfill('0') << tm->tm_hour << "-"
       << std::setw(2) << std::setfill('0') << tm->tm_min << "-"
       << std::setw(2) << std::setfill('0') << tm->tm_sec;
    return ss.str();
}
