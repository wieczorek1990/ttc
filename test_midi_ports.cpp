#include <libremidi/libremidi.hpp>
#include <iostream>

int main() {
    libremidi::observer observer;
    
    auto inputPorts = observer.get_input_ports();
    auto outputPorts = observer.get_output_ports();
    
    std::cout << "Input ports: " << inputPorts.size() << std::endl;
    for (const auto& port : inputPorts) {
        std::cout << "  - " << port.display_name << std::endl;
    }
    
    std::cout << "Output ports: " << outputPorts.size() << std::endl;
    for (const auto& port : outputPorts) {
        std::cout << "  - " << port.display_name << std::endl;
    }
    
    return 0;
}
