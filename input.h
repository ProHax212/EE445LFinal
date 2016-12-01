// Struct to hold the x/y values of the ADC result from the Joystick
typedef struct{
	int X, Y;
} Movement;

// Initialize the ADC Converter and the Switch input
void Input_Init(void);

// Get the current X/Y position of the joystick
Movement Get_XY(void);

// Get the current state of the switches
// 0x00 (neither pressed), 0x01 (SW1 Pressed), 0x10 (SW2 Pressed), 0x11 (both pressed)
int Get_SW(void);
