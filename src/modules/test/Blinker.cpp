#include "Blinker.h"
#include <string>
#include <stdarg.h>
using std::string;
#include "SerialMessage.h"
#include "StreamOutput.h"
#include "Kernel.h"
#include "utils.h"

Blinker::Blinker(){
}

void Blinker::on_module_loaded(){
    this->register_for_event(ON_CONSOLE_LINE_RECEIVED);
}

void Blinker::on_console_line_received(void *line){
    SerialMessage new_message = *static_cast<SerialMessage *>(line);

    // Ignore comments and blank lines and if this is a G code then also ignore it
    char first_char = new_message.message[0];
    if(strchr(";( \n\rGMTN", first_char) != NULL) return;

    // Extract the first parameter
    string possible_command = new_message.message;
    string cmd = shift_parameter(possible_command);

    if( cmd == "blink" ){
        new_message.stream->printf("Blinking\n");
    }

    new_message.stream->printf("OK\n");
}
