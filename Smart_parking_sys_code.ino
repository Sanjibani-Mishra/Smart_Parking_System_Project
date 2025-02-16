#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust for 16x2 LCD
Servo entryServo;
Servo exitServo;

#define ir_enter 2
#define ir_back  4
#define ir_car1 5
#define ir_car2 6

int S1 = 0, S2 = 0;
int flag1 = 0, flag2 = 0; 
int slot = 2;

void setup() {
    Serial.begin(9600);
    pinMode(ir_car1, INPUT);
    pinMode(ir_car2, INPUT);
    pinMode(ir_enter, INPUT);
    pinMode(ir_back, INPUT);
    
    // Pin assignments for servos (adjust as needed)
    entryServo.attach(3);
    exitServo.attach(9);

    // Initial positions for the servos (adjust as needed)
    entryServo.write(90); // Adjust for initial position
    exitServo.write(90); // Adjust for initial position

    lcd.begin(16, 2);  
    lcd.setCursor(0, 0);
    lcd.print("Car Parking System");
    delay(2000);
    lcd.clear();   
    
    Read_Sensor();
    int total = S1 + S2;
    slot = 2 - total; 
}

void loop() {
    Read_Sensor();
    
    lcd.setCursor(0, 0);
    lcd.print("Slots: "); 
    lcd.print(slot);
    lcd.print("   ");  
    
    lcd.setCursor(0, 1);
    lcd.print("S1:");
    lcd.print(S1 == 1 ? "Full " : "Empty");
    lcd.print("  S2:");
    lcd.print(S2 == 1 ? "Full " : "Empty");

    // Control the entry and exit servos based on sensor readings and user input
    // ... (Your logic for controlling servos based on IR sensors and user input)

    // Example:
    if (digitalRead(ir_enter) == LOW && slot > 0) {
        // Raise the entry barrier
        entryServo.write(0); // Adjust for the 'up' position
        delay(1000); // Delay for barrier movement
        entryServo.write(90); // Adjust for the 'down' position
    }

    // ... (Similar logic for the exit servo based on ir_back and slot availability)
}

void Read_Sensor() {
    S1 = digitalRead(ir_car1) == 0 ? 1 : 0;
    S2 = digitalRead(ir_car2) == 0 ? 1 : 0;
}
