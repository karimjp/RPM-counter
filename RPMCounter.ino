#define IRinputDigitalPin 2 // analog input pin (Detector) 
#define numberOfinterrupt 0 
int val = 0; // variable to store the value read from input pin 
int numberOfFanBlades = 5; 
//global variable accessed by the ISR function 
volatile int rpmCount=0; 
double RPM; 

void setup() { 
attachInterrupt(0, rpm_fun, RISING); 
pinMode(IRinputDigitalPin,INPUT); 
Serial.begin(9600); 
RPM = 0.0; 
} 
//ISR Function attached to pin 2 
void rpm_fun() { 
  rpmCount++; //Serial.print("counting..."); //Just to test that it worked 
} 

double calculateRPM() { 
//delays are one seconds per loop, therefore measurements are approximately taken during one second. 
//the interrupt will break during this second to increment the counter 
int rpmcount = rpmCount/numberOfFanBlades; //get the revolutions of one blade 
int rpm = rpmcount * 60; // multiply this value by 60 seconds 
return rpm; 
}
void loop() { 
// take measurements during this second 
delay(1000); 
detachlnterrupt(0);
//this is a safety measurement, we are accessing the value at the variable of the ISR 
RPM = calculateRPM(); 
Serial.print("RPM="); 
Serial.println(RPM); 
Serial.print("bladeCount: "); 
Serial.println(rpmCount); 
rpmCount=0; //reset rpmCount to start blade revolutions count 
//Restart Interrupt Process 
attachInterrupt(0, rpm_fun, RISING); 

