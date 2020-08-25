// clears buffer to stop reading commands from socket client
void clearEspSerial() {
    while (ESPserial.available()) {
        ESPserial.read();
    }
} 