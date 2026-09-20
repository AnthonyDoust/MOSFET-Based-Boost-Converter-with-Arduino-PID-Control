#include <PID_v1.h>

// pin assignments
int inputpin = A0;
int PWMoutpin = 9;

unsigned long previoustime;
unsigned long time;
unsigned long timediff;
int interval = 50;
float VoltageOut;

float targetVoltage = 10; // set to your desired voltage output
float voltage = 50; // Set to your max possible voltage input
float voltagein;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=2, Ki=10, Kd=0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {

  pinMode(PWMoutpin, OUTPUT);  // OC1A output

  // Clear Timer1 Control Registers
  TCCR1A = 0;
  TCNT1  = 0;

  // Set Fast PWM Mode 14 (WGM13=1, WGM12=1, WGM11=1, WGM10=0)
  // Set non-inverting mode for both Channel A and Channel B (COM1A1=1, COM1B1=1)
  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11);
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10); // CS10=1 sets Prescaler to 1

  // Set the TOP value for 125kHz
  ICR1 = 127;

  //Serial.begin(115200);

  //initialize the variables we're linked to
  voltagein = analogRead(inputpin);
  Input = (((voltagein)*1023)/voltage);

  Setpoint = targetVoltage; // equation to convert voltage to 1023 analog val

  myPID.SetMode(AUTOMATIC);   //turn the PID on
  myPID.SetSampleTime(50); // sample time of the PID controller
  myPID.SetOutputLimits(0, 127); // limits of the PID output

}

void loop() {

// keep track of current time and the difference between previous and current
time = millis();
timediff = time - previoustime;

// interval to check the voltage and serial print values
if (time - previoustime >= interval) {

  previoustime = time;

  VoltageOut = (analogRead(inputpin) * (voltage/1023)); // equation converting input analog value to voltage

  Input = VoltageOut;

  float DutyCycleOut = (Output/127) * 100;

  // Serial plotter outputs for troubleshooting and tuning
      //Serial.print("Target Voltage:");
      //Serial.print(targetVoltage);
      //Serial.print(",Voltage Out(V):");
      //Serial.println(VoltageOut);

      //Serial.print("Duty Cycle(%): ");
      //Serial.println((int)DutyCycleOut);

}

  // Compute and output PID output
  myPID.Compute();
  OCR1A = (int)Output;

  // if source voltage drops to 0, reset the accumulation of the integrator
  if (VoltageOut == 0) {
    myPID.SetMode(MANUAL);  
    Output = 0.0;            
    myPID.SetMode(AUTOMATIC); 
  }
}


