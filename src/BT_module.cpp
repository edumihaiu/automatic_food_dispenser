#include "../inc/BT_module.h"
#include "../inc/Stepper_module.h"
#include "../inc/HX711_driver.h"
#include "../inc/RTC_module.h"
#include "../inc/pins.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(BT_RX, BT_TX); // RX, TX
extern HX711_t cantar;

void BT_init() {
    BT.begin(9600); // Viteza standard la modulele astea
    BT.println(">>> connected <<<");
    BT.println("h=feed, i=Info, t=Tare");
}

void BT_checkCommand() {
if (BT.available()) {
        char c = BT.read();
        
        if (c == '\n' || c == '\r' || c == ' ') return;

        Serial.print("bt command recieved: ");
        Serial.println(c);

        switch (c) {
            case 'h': // FEED
                BT.println("feed 50g");
                int res = Stepper_dispense(50.0);
                if (res == 1) BT.println("sucessful");
                else BT.println("error: check level or mechanism"); 
                break;

            case 'i': // INFO
                {
                    // time
                    RTC_printBTTime();

                    // weight
                    float g = HX711_get_weight(&cantar);
                    BT.print("Bol: ");
                    BT.print(g);
                    BT.println(" g");
                }
                break;
            
            case 't': // tare
                BT.println("tare in process");
                HX711_tare(&cantar);
                BT.println("Scale is now 0.");
                break;

            default:
                BT.println("Unknown command. Try h, i, or t.");
                break;
        }
    }
}