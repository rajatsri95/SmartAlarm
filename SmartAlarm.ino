/**************************************************************************
    Project Description:
        -  SmartAlarm find the perfect time for alarm to ring within a set 
            time range, based on body movement 
    Developers:
        - Anjali Malik (malik11@purdue.edu)
        - Rajat Srivastava (rajatsrivastava95@gmail.com)       
 
    README:
        - Loop Delay set to 0.1 second.
        - Deep Sleep defined as no movement after 15 mins (900 seconds)  
**************************************************************************/


#define PIR_MOTION_SENSOR 2     // Pin 2 is used to receive signal
#define GREEN_LED 4             // Pin 4 used to show when user is in Awake State
#define RED_LED 8               // Pin 8 used t0 show when user is in Deep Sleep

int state = -1;                  // 1 = Movement/Awake/REM, 0 = No Movement/Deep Sleep

void setup()
{
    Serial.begin(9600);
    initialize();
}

void loop()
{
    int active_timer = 0;
    int inactive_timer = 0;      // Keeps time of no continous detection (no motion)
    if (detection()) {
        inactive_timer = 0;      // Resets the timer
        active_timer = active_timer + 0.1;
    }
    else {
        active_timer = 0;
        inactive_timer = inactive_timer + 0.1;
    }

    if ((active_timer > 0) && (state != 0)) {         // This means user is active
        state = 1;
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(RED_LED, LOW);            
    }
    if (inactive_timer > 900) {     // This means user is inactive for 15 mins
        state =  0;
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW)
    }

    Serial.print(state);

    delay(100);
}

// Helper Function 1: Define Pins 
void initialize() {
    pinMode(PIR_MOTION_SENSOR, INPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
}
    
// Helper Function 2: Detect motion within range
boolean detection() {
    int pir = digitalRead(PIR_MOTION_SENSOR);
    if (pir == HIGH) return true;   // True if motion detected
    else return false;              // False if motion not detected
    }
}