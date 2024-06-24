#include <reg52.h>
#define ADC PORT P1
// Define the stepper motor pins
#define STEPPER_DIR P0^0
#define STEPPER_PULSE P0^1
// Define the ADC channel for the LDRs
#define LDR_CHANNEL 0
// Define the delay time between stepper motor steps
#define DELAY_TIME 10
// Initialize the stepper motor direction 
void stepper_init() { 
		STEPPER_DIR==0; }
// Rotate the stepper motor in the specified direction 
void stepper_rotate(int direction) {
// Set the stepper motor direction 
	STEPPER_DIR == direction;

// Pulse the stepper motor pulse pin 
	STEPPER_PULSE ==1; 
	delay(DELAY_TIME); 
	STEPPER_PULSE ==0; }
// Read the ADC value from the specified channel 
	int adc_read(int channel) {
// Set the ADC channel 
	int ADC_PORT = channel;
// Start the ADC conversion 
	ADCC0N1 |= 0x80 ;
// Wait for the ADC conversion to finish 
		while (ADCC0N1 & 0x80);
// Read the ADC value 
		return ADCBUF;
}
// Calculate the stepper motor rotation angle based on the ADC value 
int calculate_rotation_angle(int adc_value) {
// The ADC value is proportional to the amount of light falling on t
// The higher the ADC value, the more light is falling on the LDRs. // The stepper motor should be rotated towards the LDR with the high
// Calculate the difference between the ADC values of the two LDRs. 
	int adc_difference = adc_read(LDR_CHANNEL_1) - adc_read(LDR_CHANNEL_2);
// If the ADC difference is positive, rotate the stepper motor clock.
// If the ADC difference is negative, rotate the stepper motor count
	int rotation_angle = adc_difference > 0 ? 1 : -1 ;
// Return the rotation angle. 
	return rotation_angle;
}
void track_sun(){
	int adc_value = adc_read(LDR_CHANNEL);
	int rotation_angle = calculate_rotational_angle(adc_value);
	stepper_rotate(rotation_angle);
}
void main(){
stepper_init();

while(1){
track_sun()}}