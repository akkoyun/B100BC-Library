#ifndef __B100BC__
#define __B100BC__

	// Define Configuration
	#define B100BC_BUZZER
	#define B100BC_LIGHTS

	// Define Arduino Library
	#ifndef __Arduino__
		#include <Arduino.h>
	#endif

	// Include Definitions
	#ifndef __B100BC_Definitions__
		#include "Definitions.h"
	#endif

	// Include Sound Library
	#ifndef __Sounds__
		#include "Sounds.h"
	#endif

	// Define RTC Library
	#ifndef __RV3028__
		#include <RV3028.h>
	#endif

	// Define Statistical Library
	#ifndef __Statistical__
		#include <Statistical.h>
	#endif

	// Define Environment Library
	#ifndef __Environment__
		#include <Environment.h>
	#endif
#include <Console.h>

	// Define Console Library
	Console B100_Terminal(Serial);

	// Stream library object definition.
	Stream_Stats<float> Pressure_Stats;

	// B100BC Functions
	class B100BC {

		// Private Functions
		private:

			// PinOut Definitions
			inline void Set_Pinout(void) {

				/*  PORT A
					PA0 - Output / Pull Down [NC] 			- AD0		- [22]
					PA1 - Output / Pull Down [NC] 			- AD1		- [23]
					PA2 - Output / Pull Down [NC] 			- AD2		- [24]
					PA3 - Output / Pull Down [NC] 			- AD3		- [25]
					PA4 - Output / Pull Down [NC] 			- AD4		- [26]
					PA5 - Output / Pull Down [NC] 			- AD5		- [27]
					PA6 - Output / Pull Down [NC] 			- AD6		- [28]
					PA7 - Output / Pull Down [NC] 			- AD7		- [29]
				*/
				DDRA = 0b11111111; PORTA = 0b00000000;

				/*  PORT B
					PB0 - SS
					PB1 - SCK
					PB2 - MOSI
					PB3 - MISO
					PB4 - Input / Pull Up [RTC Interrupt] 	- PCINT4 	- [10]
					PB5 - Output / Pull Down [NC] 			- PCINT5 	- [11]
					PB6 - Output / Pull Down [NC] 			- PCINT6 	- [12]
					PB7 - Output / Pull Down [NC] 			- PCINT7 	- [13]
				*/
				DDRB |= 0b11100000; PORTB &= 0b00011111;
				DDRB &= 0b11101111; PORTB |= 0b00010000;

				/*  PORT C
					PC0 - Output / Pull Down [SD Mux Dir.]	- AD8		- [37]
					PC1 - Input / Pull Down [SD Card Det.]	- AD9		- [36]
					PC2 - Output / Pull Down [NC] 			- AD10		- [35]
					PC3 - Output / Pull Down [NC] 			- AD11		- [34]
					PC4 - Output / Pull Down [NC] 			- AD12		- [33]
					PC5 - Output / Pull Down [NC] 			- AD13		- [32]
					PC6 - Output / Pull Down [NC] 			- AD14		- [31]
					PC7 - Output / Pull Down [NC] 			- AD15		- [30]
				*/
				DDRC |= 0b00000001;	PORTC &= 0b11111110;
				DDRC &= 0b11111101;	PORTC &= 0b11111101;
				DDRC |= 0b11111100;	PORTC &= 0b00000011;

				/*  PORT D
					PD0 - SCL
					PD1 - SDA
					PD2 - RXD1
					PD3 - TXD1
					PD4 - Output / Pull Down [NC] 			- ICP1		- [85]
					PD5 - Output / Pull Down [MCU LED Blue]	- XCK1		- [84]
					PD6 - Output / Pull Down [MCU LED Green]- T1		- [83]
					PD7 - Output / Pull Down [MCU LED Red]	- T0		- [82]
				*/
				DDRD |= 0b11110000; PORTD &= 0b00001111;

				/*  PORT E
					PE0 - RXD0
					PE1 - TXD0
					PE2 - Output / Pull Down [NC]			- AIN0		- [-]
					PE3 - Output / Pull Down [Buzzer EN1]	- AIN1		- [5]
					PE4 - Output / Pull Down [Buzzer EN2]	- INT4		- [2]
					PE5 - Output / Pull Down [PWM Buzzer]	- INT5		- [3]
					PE6 - Output / Pull Down [NC]			- INT6		- [-]
					PE7 - Output / Pull Down [NC]			- INT7		- [-]
				*/
				DDRE |= 0b11111100; PORTE &= 0b11000000;

				/*  PORT F
					PF0 - Input / Pull Down [Sns 1 Sense]	- ADC0		- [A0]
					PF1 - Sensor Data 1						- ADC1		- [A1]
					PF2 - Sensor Data 2						- ADC2		- [A2]
					PF3 - Input / Pull Down [Sns 2 Sense]	- ADC3		- [A3]
					PF4 - Output / Pull Down [NC]			- ADC4		- [A4]
					PF5 - Output / Pull Down [NC]			- ADC5		- [A5]
					PF6 - Output / Pull Down [NC]			- ADC6		- [A6]
					PF7 - Output / Pull Down [NC]			- ADC7		- [A7]
				*/
				DDRF &= 0b11110000; PORTF &= 0b11110110;
				DDRF |= 0b11110000; PORTF &= 0b00001111;

				/*  PORT G
					PG0 - Output / Pull Down [FOTA Pwr En]	- WR		- [41]
					PG1 - Output / Pull Down [NC] 			- RD		- [40]
					PG2 - Output / Pull Down [NC] 			- ALE		- [39]
					PG3 - Output / Pull Down [NC] 			- TOSC2		- [-]
					PG4 - Output / Pull Down [NC] 			- TOSC1		- [-]
					PG5 - Output / Pull Down [NC] 			- OC0B		- [4]
				*/
				DDRG |= 0b00111111; PORTG &= 0b11000000;

				/*  PORT J
					PJ0 - RXD3
					PJ1 - TXD3
					PJ2 - Input / Pull Down [GSM Ring]		- PCINT11	- [-]
					PJ3 - Input / Pull Down [GSM PwrMon]	- PCINT12	- [-]
					PJ4 - Output / Pull Down [GSM Communication Enable]	- PCINT13	- [-]
					PJ5 - Output / Pull Down [GSM ShtDwn]	- PCINT14	- [-]
					PJ6 - Output / Pull Down [GSM On Off]	- PCINT15	- [-]
					PJ7 - Output / Pull Down [NC]			-  			- [-]
				*/
				DDRJ &= 0b11110011; PORTJ |= 0b00000100;
				DDRJ |= 0b11110000; PORTJ &= 0b00000111;

				/*  PORT K
					PK0 - Input / Pull Down [220V Sense 1]  - PCINT16	- [89]
					PK1 - Input / Pull Down [220V Sense 2]  - PCINT17	- [88]
					PK2 - Input / Pull Down [220V Sense 3]  - PCINT18	- [87]
					PK3 - Input / Pull Down [220V Sense 4]  - PCINT19	- [86]
					PK4 - Input / Pull Down [220V Sense 5]  - PCINT20	- [85]
					PK5 - Input / Pull Down [220V Sense 6]  - PCINT21	- [84]
					PK6 - Input / Pull Down [220V Sense 7]  - PCINT22	- [83]
					PK7 - Input / Pull Down [220V Sense 8]  - PCINT23	- [82]
				*/
				DDRK = 0b00000000; PORTK = 0b00000000;

				/*  PORT L
					PL0 - Output / Pull Down [Start Relay]	- ICP4		- [49]
					PL1 - Output / Pull Down [Stop Relay]	- ICP5		- [48]
					PL2 - Output / Pull Down [Alarm Relay]	- T5		- [47]
					PL3 - Output / Pull Down [Res. Relay]	- OC5A		- [46]
					PL4 - Output / Pull Down [NC]			- OC5B		- [45]
					PL5 - Output / Pull Down [NC]			- OC5C		- [44]
					PL6 - Output / Pull Down [NC]			- 			- [43]
					PL7 - Output / Pull Down [NC]			- 			- [42]
				*/
				DDRL |= 0b11111111; PORTL &= 0b00000000;

			}

			// AVR Timer Functions
			inline void AVR_Timer_1sn(void) {

				// Clear Registers
				TCCR5A = 0x00;
				TCCR5B = 0x00;

				// Clear Counter
				TCNT5 = 0;

				// Set Counter Value
				OCR5A = (F_CPU / (1024)) - 1;

				// Set CTC Mod
				TCCR5B |= (1 << WGM52);

				// Set Rescale (1024)
				TCCR5B |= (1 << CS52) | (1 << CS50);

				// Start Timer
				TIMSK5 |= (1 << OCIE5A);

			}

			// AVR Interrupt
			void AVR_Pin_Interrupt(const uint8_t _Interrupt_Type, const bool _State) {

				/*

					PCICR Register
					--------------

					8   7   6   5   4   3     2     1     0
					-   -   -   -   -   -   PCIE2 PCIE1 PCIE0
					
					PCINT0  - PCINT7   : PCIE0 Mask
					PCINT8  - PCINT15  : PCIE1 Mask
					PCINT16 - PCINT23  : PCIE2 Mask

				*/

				switch (_Interrupt_Type) {

					// RTC Alarm Interrupt Mask
					case 1: {

						// Set State
						if (_State) PCICR |= (1 << PCIE0);
						if (!_State) PCICR &= ~(1 << PCIE0);

						// Set Pin Change Interrupt Mask 0
						PCMSK0 |= (1 << PCINT4);

						// End Case
						break;

					}

					// GSM Ring and Power Mon Interrupt Mask
					case 2: {

						// Set State
						if (_State) PCICR |= (1 << PCIE1);
						if (!_State) PCICR &= ~(1 << PCIE1);

						// Set Pin Change Interrupt Mask 1
						PCMSK1 |= (1 << PCINT11) | (1 << PCINT12);	// GSM Ring and Power Mon Interrupt

						// End Case
						break;

					}

					// Input Pins Interrupt Mask
					case 3: {

						// Set State
						if (_State) PCICR |= (1 << PCIE2);
						if (!_State) PCICR &= ~(1 << PCIE2);

						// Set Pin Change Interrupt Mask 2
						PCMSK2 |= (1 << PCINT16) | (1 << PCINT17) | (1 << PCINT18) | (1 << PCINT19) | (1 << PCINT20) | (1 << PCINT21) | (1 << PCINT22) | (1 << PCINT23);

						// End Case
						break;

					}

				}

			}

			// FOTA Functions
			void FOTA_Power(const bool _State) {

				// Turn FOTA Power Enable HIGH
				if (_State) PORTG |= 0b00000001;

				// Turn FOTA Power Enable LOW
				if (!_State) PORTG &= 0b11111110;

			}

			// Buzzer Functions
			inline void Sound_Level(void) {

				// Set Buzzer Sound Level to High
				PORTE &= 0b11100111;
				PORTE |= 0b00011000;

			}
			void Bend_Tones(float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration) {

				if(silentDuration==0) silentDuration=1;

				if(initFrequency < finalFrequency) {

					for (size_t i = initFrequency; i < finalFrequency; i = i * prop) this->Tone(i, noteDuration, silentDuration);

				} else {

					for (size_t i = initFrequency; i > finalFrequency; i = i / prop) this->Tone(i, noteDuration, silentDuration);

				}

			}
			void Tone(float noteFrequency, long noteDuration, int silentDuration) {

				if (silentDuration == 0) silentDuration = 1;

				// Play Tone
				tone(3, noteFrequency, noteDuration);

				// Delay Note
				delay(noteDuration);

				// Delay Silent
				delay(silentDuration);

			}

			// Terminal Functions



			// Set Cursor Position Function.
			void Terminal_Set_Cursor(const uint8_t _X, const uint8_t _Y) {

				// Set Cursor Position
				Serial.print(F("\e["));
				Serial.print(_X);
				Serial.print(F(";"));
				Serial.print(_Y);
				Serial.print(F("H"));

			}

			// Set Text Color Function.
			void Terminal_Text_Color(const uint8_t _Color) {

				// Set Text Color.
				Serial.print(F("\e["));
				Serial.print(_Color);
				Serial.print('m');

			}

			// Set Back Ground Color Function.
			void Terminal_Background_Color(const uint8_t _Color) {

				// Set Back Ground Color.
				Serial.print(F("\e["));
				Serial.print(_Color + 10);
				Serial.print('m');

			}

			// Set Text Format Function
			void Terminal_Text_Format(const uint8_t _Format) {

				// Set Text Format
				Serial.print(F("\e["));
				Serial.print(_Format);
				Serial.write('m');

			}

			// Dot Print Function.
			void Terminal_Dot(const uint8_t _X, const uint8_t _Y, const uint8_t _Count) {

				// Set Text Color
				this->Terminal_Text_Color(Terminal_GRAY);

				// Set Cursor Position
				this->Terminal_Set_Cursor(_X, _Y);

				// Print Dot
				for (uint8_t i = 0; i < _Count; i++) Serial.print(".");

			}

			// Bracket Place Holder Function.
			void Terminal_Bracket(const uint8_t _X, const uint8_t _Y, const uint8_t _Space) {

				// Set Text Color
				this->Terminal_Text_Color(Terminal_WHITE);

				// Set Cursor Position
				this->Terminal_Set_Cursor(_X, _Y);

				// Print Bracket Start
				Serial.print("[");

				// Set Cursor Position
				this->Terminal_Set_Cursor(_X, _Y + _Space + 1);

				// Print Bracket Start
				Serial.print("]");

			}

			// Draw Box Function.
			void Terminal_Box(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2, const String _Text, const uint8_t _Number, const bool _Header, const bool _Footer) {

				// Set Text Color (White)
				this->Terminal_Text_Color(Terminal_WHITE);

				// Set Text Format
				this->Terminal_Text_Format(Terminal_DIM);

				// Print Corners
				this->Terminal_Set_Cursor(_X1, _Y1); Serial.print(F("┌"));
				this->Terminal_Set_Cursor(_X2, _Y1); Serial.print(F("└"));
				this->Terminal_Set_Cursor(_X1, _Y2); Serial.print(F("┐"));
				this->Terminal_Set_Cursor(_X2, _Y2); Serial.print(F("┘"));

				// Print Lines
				for (uint8_t i = _X1 + 1; i <= _X2 - 1; i++) {this->Terminal_Set_Cursor(i, _Y1); Serial.print(F("│")); this->Terminal_Set_Cursor(i, _Y2); Serial.print(F("│"));}
				for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {this->Terminal_Set_Cursor(_X1, i); Serial.print(F("─")); this->Terminal_Set_Cursor(_X2, i); Serial.print(F("─"));}

				// Draw Header
				if (_Header) {

					// Print Corners
					this->Terminal_Set_Cursor(_X1 + 2, _Y1); Serial.print(F("├"));
					this->Terminal_Set_Cursor(_X1 + 2, _Y2); Serial.print(F("┤"));

					// Print Lines
					for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {this->Terminal_Set_Cursor(_X1 + 2, i); Serial.print(F("─"));}

				}
				
				// Draw Footer			
				if (_Footer) {

					// Print Corners
					this->Terminal_Set_Cursor(_X2 - 2, _Y1); Serial.print(F("├"));
					this->Terminal_Set_Cursor(_X2 - 2, _Y2); Serial.print(F("┤"));

					// Print Lines
					for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {this->Terminal_Set_Cursor(_X2 - 2, i); Serial.print(F("─"));}

				}

				// Set Text Color (White)
				this->Terminal_Text_Color(Terminal_YELLOW);

				// Print Header
				this->Terminal_Set_Cursor(_X1, _Y1 + 2); Serial.print(_Text);

				// Print Header Number
				if (_Number != 0) {this->Terminal_Bracket(_X1, _Y2 - 4, 1); this->Terminal_Set_Cursor(_X1, _Y2 - 3); this->Terminal_Text_Color(Terminal_GRAY); Serial.print(_Number);}

				// Set Text Color (White)
				this->Terminal_Text_Color(Terminal_WHITE);

			}

			// Hardware Diagnostic Box
			void Terminal_Hardware_Diagnostic(void) {

				// Draw Hardware Diagnostic
				this->Terminal_Box(4, 2, 12, 41, "Hardware Diagnostic", 1, false, false);

				// Print Texts
				this->Terminal_Set_Cursor(5, 4); Serial.print(F("I2C Multiplexer (0x70)")); this->Terminal_Dot(5, 26, 8); this->Terminal_Bracket(5, 34, 4);
				this->Terminal_Set_Cursor(6, 4); Serial.print(F("I2C RTC (0x52)")); this->Terminal_Dot(6, 18, 16); this->Terminal_Bracket(6, 34, 4);
				this->Terminal_Set_Cursor(7, 4); Serial.print(F("I2C Serial ID (0x50)")); this->Terminal_Dot(7, 24, 10); this->Terminal_Bracket(7, 34, 4);
				this->Terminal_Set_Cursor(8, 4); Serial.print(F("I2C Temperature (0x40)")); this->Terminal_Dot(8, 26, 8); this->Terminal_Bracket(8, 34, 4);
				this->Terminal_Set_Cursor(9, 4); Serial.print(F("I2C Battery Gauge (0x36)")); this->Terminal_Dot(9, 28, 6); this->Terminal_Bracket(9, 34, 4);
				this->Terminal_Set_Cursor(10, 4); Serial.print(F("I2C Battery Charger (0x6B)")); this->Terminal_Dot(10, 30, 4); this->Terminal_Bracket(10, 34, 4);
				this->Terminal_Set_Cursor(11, 4); Serial.print(F("SD Card Connection")); this->Terminal_Dot(11, 22, 12); this->Terminal_Bracket(11, 34, 4);

			}

			// Hardware Detail Box
			void Terminal_Hardware_Detail(void) {

				// Draw Hardware Diagnostic
				this->Terminal_Box(4, 42, 12, 81, "Hardware Detail", 2, false, false);

				// Print Texts
				this->Terminal_Set_Cursor(5, 44); Serial.print(F("Serial ID")); this->Terminal_Dot(5, 53, 9); this->Terminal_Bracket(5, 62, 16);
				this->Terminal_Set_Cursor(6, 44); Serial.print(F("Firmware Version")); this->Terminal_Dot(6, 60, 10); this->Terminal_Bracket(6, 70, 8);
				this->Terminal_Set_Cursor(7, 44); Serial.print(F("Hardware Version")); this->Terminal_Dot(7, 60, 10); this->Terminal_Bracket(7, 70, 8);
				this->Terminal_Set_Cursor(8, 44); Serial.print(F("Module Temperature")); this->Terminal_Dot(8, 62, 9); this->Terminal_Bracket(8, 71, 7); this->Terminal_Set_Cursor(8, 78); Serial.print(F("C"));
				this->Terminal_Set_Cursor(9, 44); Serial.print(F("Module Humidity")); this->Terminal_Dot(9, 59, 12); this->Terminal_Bracket(9, 71, 7); this->Terminal_Set_Cursor(9, 78); Serial.print(F("%"));
				this->Terminal_Set_Cursor(10, 44); Serial.print(F("Online Send Interval")); this->Terminal_Dot(10, 64, 7); this->Terminal_Bracket(10, 71, 7); this->Terminal_Set_Cursor(10, 76); Serial.print(F("Min"));
				this->Terminal_Set_Cursor(11, 44); Serial.print(F("Offline Send Interval")); this->Terminal_Dot(11, 65, 6); this->Terminal_Bracket(11, 71, 7); this->Terminal_Set_Cursor(11, 76); Serial.print(F("Min"));

			}

			// Hardware Battery Box
			void Terminal_Battery_Detail(void) {

				// Draw Hardware Diagnostic
				this->Terminal_Box(4, 82, 12, 121, "Battery", 3, false, false);

				// Print Texts
				this->Terminal_Set_Cursor(5, 84); Serial.print(F("Instant Voltage")); this->Terminal_Dot(5, 99, 13); this->Terminal_Bracket(5, 112, 6); this->Terminal_Set_Cursor(5, 118); Serial.print(F("V"));
				this->Terminal_Set_Cursor(6, 84); Serial.print(F("Temperature")); this->Terminal_Dot(6, 95, 16); this->Terminal_Bracket(6, 111, 7); this->Terminal_Set_Cursor(6, 118); Serial.print(F("C"));
				this->Terminal_Set_Cursor(7, 84); Serial.print(F("Average Current")); this->Terminal_Dot(7, 99, 10); this->Terminal_Bracket(7, 109, 9); this->Terminal_Set_Cursor(7, 117); Serial.print(F("mA"));
				this->Terminal_Set_Cursor(8, 84); Serial.print(F("State of Charge")); this->Terminal_Dot(8, 99, 12); this->Terminal_Bracket(8, 111, 7); this->Terminal_Set_Cursor(8, 118); Serial.print(F("%"));
				this->Terminal_Set_Cursor(9, 84); Serial.print(F("Full Battery Capacity")); this->Terminal_Dot(9, 105, 6); this->Terminal_Bracket(9, 111, 7); this->Terminal_Set_Cursor(9, 117); Serial.print(F("mA"));
				this->Terminal_Set_Cursor(10, 84); Serial.print(F("Instant Battery Capacity")); this->Terminal_Dot(10, 108, 3); this->Terminal_Bracket(10, 111, 7); this->Terminal_Set_Cursor(10, 117); Serial.print(F("mA"));
				this->Terminal_Set_Cursor(11, 84); Serial.print(F("Charge State")); this->Terminal_Dot(11, 96, 10); this->Terminal_Bracket(11, 106, 12);

			}

			// GSM Initialize Detail
			void Terminal_GSM_Init_Detail(void) {

				// Draw Hardware Diagnostic
				this->Terminal_Box(16, 2, 23, 41, "GSM Initialize", 4, false, false);

				// Print Texts
				this->Terminal_Set_Cursor(17, 4); Serial.print(F("Manufacturer")); this->Terminal_Dot(17, 16, 21); this->Terminal_Bracket(17, 37, 1);
				this->Terminal_Set_Cursor(18, 4); Serial.print(F("Model")); this->Terminal_Dot(18, 9, 28); this->Terminal_Bracket(18, 37, 1);
				this->Terminal_Set_Cursor(19, 4); Serial.print(F("Firmware")); this->Terminal_Dot(19, 12, 17); this->Terminal_Bracket(19, 29, 9);
				this->Terminal_Set_Cursor(20, 4); Serial.print(F("IMEI")); this->Terminal_Dot(20, 8, 15); this->Terminal_Bracket(20, 23, 15);
				this->Terminal_Set_Cursor(21, 4); Serial.print(F("Serial ID")); this->Terminal_Dot(21, 13, 15); this->Terminal_Bracket(21, 28, 10);
				this->Terminal_Set_Cursor(22, 4); Serial.print(F("ICCID")); this->Terminal_Dot(22, 9, 10); this->Terminal_Bracket(22, 19, 19);

			}

			// GSM Connection Detail
			void Terminal_GSM_Connection_Detail(void) {

				// Draw Hardware Diagnostic
				this->Terminal_Box(16, 42, 23, 81, "GSM Connection", 5, false, false);

				// Print Texts
				this->Terminal_Set_Cursor(17, 44); Serial.print(F("GSM Connection Time")); this->Terminal_Dot(17, 63, 11); this->Terminal_Bracket(17, 74, 4);
				this->Terminal_Set_Cursor(18, 44); Serial.print(F("Signal Level")); this->Terminal_Dot(18, 56, 17); this->Terminal_Bracket(18, 73, 5);
				this->Terminal_Set_Cursor(19, 44); Serial.print(F("GSM Operator")); this->Terminal_Dot(19, 56, 17); this->Terminal_Bracket(19, 73, 5);
				this->Terminal_Set_Cursor(20, 44); Serial.print(F("IP Address")); this->Terminal_Dot(20, 54, 9); this->Terminal_Bracket(20, 63, 15);
				this->Terminal_Set_Cursor(21, 44); Serial.print(F("LAC")); this->Terminal_Dot(21, 47, 27); this->Terminal_Bracket(21, 74, 4);
				this->Terminal_Set_Cursor(22, 44); Serial.print(F("Cell ID")); this->Terminal_Dot(22, 51, 23); this->Terminal_Bracket(22, 74, 4);

			}

			// GSM FOTA Detail
			void Terminal_FOTA_Detail(void) {

				// Draw Hardware Diagnostic
				this->Terminal_Box(16, 82, 23, 121, "FOTA", 6, false, false);

				// Print Texts
				this->Terminal_Set_Cursor(17, 84); Serial.print(F("File ID")); this->Terminal_Dot(17, 91, 21); this->Terminal_Bracket(17, 112, 6);
				this->Terminal_Set_Cursor(18, 84); Serial.print(F("Download Status")); this->Terminal_Dot(18, 99, 15); this->Terminal_Bracket(18, 114, 4);
				this->Terminal_Set_Cursor(19, 84); Serial.print(F("FTP File Size")); this->Terminal_Dot(19, 97, 14); this->Terminal_Bracket(19, 111, 7);
				this->Terminal_Set_Cursor(20, 84); Serial.print(F("SD File Size")); this->Terminal_Dot(20, 96, 15); this->Terminal_Bracket(20, 111, 7);
				this->Terminal_Set_Cursor(21, 84); Serial.print(F("Download Percent")); this->Terminal_Dot(21, 100, 13); this->Terminal_Bracket(21, 113, 5); this->Terminal_Set_Cursor(21, 118); Serial.print(F("%"));
				this->Terminal_Set_Cursor(22, 84); Serial.print(F("Download Time")); this->Terminal_Dot(22, 97, 13); this->Terminal_Bracket(22, 110, 8); this->Terminal_Set_Cursor(22, 116); Serial.print(F("Sec"));

			}

			// GSM Pressure Detail
			void Terminal_Pressure_Detail(void) {

				// Draw Hardware Diagnostic
				this->Terminal_Box(24, 82, 32, 121, "Pressure", 7, false, false);

				// Print Texts
				this->Terminal_Set_Cursor(25, 84); Serial.print(F("Instant")); this->Terminal_Dot(25, 91, 18); this->Terminal_Bracket(25, 109, 9); this->Terminal_Set_Cursor(25, 116); Serial.print(F("Bar"));
				this->Terminal_Set_Cursor(26, 84); Serial.print(F("Min")); this->Terminal_Dot(26, 87, 22); this->Terminal_Bracket(26, 109, 9); this->Terminal_Set_Cursor(26, 116); Serial.print(F("Bar"));
				this->Terminal_Set_Cursor(27, 84); Serial.print(F("Max")); this->Terminal_Dot(27, 87, 22); this->Terminal_Bracket(27, 109, 9); this->Terminal_Set_Cursor(27, 116); Serial.print(F("Bar"));
				this->Terminal_Set_Cursor(28, 84); Serial.print(F("Avarage")); this->Terminal_Dot(28, 91, 18); this->Terminal_Bracket(28, 109, 9); this->Terminal_Set_Cursor(28, 116); Serial.print(F("Bar"));
				this->Terminal_Set_Cursor(29, 84); Serial.print(F("Deviation")); this->Terminal_Dot(29, 93, 16); this->Terminal_Bracket(29, 109, 9); this->Terminal_Set_Cursor(29, 116); Serial.print(F("Bar"));
				this->Terminal_Set_Cursor(30, 84); Serial.print(F("Slope")); this->Terminal_Dot(30, 89, 20); this->Terminal_Bracket(30, 109, 9); this->Terminal_Set_Cursor(30, 116); Serial.print(F("Bar"));
				this->Terminal_Set_Cursor(31, 84); Serial.print(F("Data Count")); this->Terminal_Dot(31, 94, 21); this->Terminal_Bracket(31, 115, 3);

			}

			// PowerStat Terminal 
			void Terminal_PowerStat(void) {

				// Start Console
				this->Terminal_Start();

				// Draw Main Box
				this->Terminal_Box(1, 1, 41, 122, "", 0, true,true);
				this->Terminal_Text(2, 3, Terminal_WHITE, "Up Time");
				this->Terminal_Text(2, 55, Terminal_WHITE, "PowerStat V4");

				// Hardware Diagnostic
				this->Terminal_Hardware_Diagnostic();

				// Hardware Detail
				this->Terminal_Hardware_Detail();

				// Battery Detail
				this->Terminal_Battery_Detail();

				// Draw GSM Terminal Box
				this->Terminal_Box(13, 2, 15, 41, "", 0, false, false);

				// Draw Info Box
				this->Terminal_Box(13, 42, 15, 81, "", 0, false, false);

				// Draw State Box
				this->Terminal_Box(13, 82, 15, 121, "", 0, false, false);
				this->Terminal_Text(14, 84, Terminal_WHITE, "Device"); this->Terminal_Dot(14, 90, 6); this->Terminal_Bracket(14, 96, 3);
				this->Terminal_Text(14, 104, Terminal_WHITE, "Fault"); this->Terminal_Dot(14, 109, 6); this->Terminal_Bracket(14, 115, 3);
				this->Terminal_Text(13, 102, Terminal_WHITE, "┬");
				this->Terminal_Text(14, 102, Terminal_WHITE, "│");
				this->Terminal_Text(15, 102, Terminal_WHITE, "┴");

				// Draw GSM Initialize Box
				this->Terminal_GSM_Init_Detail();

				// Draw GSM Connection Box
				this->Terminal_GSM_Connection_Detail();

				// FOTA Box
				this->Terminal_FOTA_Detail();

				// Pressure Box
				this->Terminal_Pressure_Detail();







				// Draw JSON Box
				this->Terminal_Box(24, 2, 32, 79, "JSON", 0, false, false);

				// Draw Voltage Box
				this->Terminal_Box(33, 2, 38, 39, "Voltage", 0, false, false);

				// Draw Current Box
				this->Terminal_Box(33, 40, 38, 79, "Current", 0, false, false);

				// Draw Power Box
				this->Terminal_Box(33, 80, 38, 119, "Power", 0, false, false);

			}

			// Begin Serial VT100 Console.
			void Terminal_Start(void) {

				// Start Terminal
				Serial.begin(115200);

				// Cursor Off
				Serial.print(F("\e[?25l"));

				// Clear Screen
				Serial.print(F("\e[2J"));

				// Reset Delay
				delay(5);

			}

		// Public Functions
		public:

			// Module DataSet Definitions
			struct B100BC_Struct {

				// AVR Timer Variable
				uint32_t Timer_Counter = 0;

				// PowerStat Input Variables
				struct Struct_Sense {
					bool SD_Card = false;
					bool Pressure_Sensor_1 = false;
					bool Pressure_Sensor_2 = false;
				} Sense;

				// Data Send Interval Variables
				struct Struct_Interval {
					uint32_t Online;
					uint32_t Offline;
					uint32_t Alarm;
				} Interval;

				// Pressure Variables
				struct Struct_Pressure {
					uint16_t Data_Count;
					float Value;
					float Min;
					float Max;
					float Average;
					float Median;
					float Deviation;
				} Pressure;

			} Variables;

			// Construct a new Hardware object
			B100BC(void) {

				// Set Module Pinout
				this->Set_Pinout();

				// Set Buzzer Sound Level
				this->Sound_Level();

				// Control Pressure Sensor
				this->Variables.Sense.Pressure_Sensor_1 = bitRead(PINF, 0);
				this->Variables.Sense.Pressure_Sensor_2 = bitRead(PINF, 3);

				// Control SD Card
				this->Variables.Sense.SD_Card = bitRead(PINC, 1);
				
			}

			// Hardware boot function
			void Begin(void) {

				// Boot Delay
				delay(50);

				// Play Sound
				this->Buzzer(Boot);

				// Turn FOTA Power Off
				this->FOTA_Power(false);

				// Timer Interrupt Definitions
				this->AVR_Timer_1sn();

				// Start GSM Serial
				Serial3.begin(115200);

				// Start Console
				this->Terminal_PowerStat();

				// Get Interval Constants
				this->Variables.Interval.Online = this->Get_EEPROM(EEPROM_Online_Interval);
				this->Variables.Interval.Offline = this->Get_EEPROM(EEPROM_Offline_Interval);
				this->Variables.Interval.Alarm = this->Get_EEPROM(EEPROM_Alarm_Duration);

				// Detect Multiplexer
				I2C_Functions I2C_Multiplexer(__I2C_Addr_TCA9548__);
				if (I2C_Multiplexer.Detect()) {this->Terminal_Text(5,35, Terminal_GREEN, F(" OK "));} else {this->Terminal_Text(5,35, Terminal_RED, F("FAIL"));}

				// Detect RTC
				I2C_Functions I2C_RTC(__I2C_Addr_RV3028C7__, true, 1);
				if (I2C_RTC.Detect()) {this->Terminal_Text(6,35, Terminal_GREEN, F(" OK "));} else {this->Terminal_Text(6,35, Terminal_RED, F("FAIL"));}

				// Detect Serial
				I2C_Functions I2C_DS28C(__I2C_Addr_DS28C__, true, 2);
				if (I2C_DS28C.Detect()) {this->Terminal_Text(7,35, Terminal_GREEN, F(" OK "));} else {this->Terminal_Text(7,35, Terminal_RED, F("FAIL"));}

				// Detect HDC2010
				I2C_Functions I2C_HDC2010(__I2C_Addr_HDC2010__, true, 3);
				if (I2C_HDC2010.Detect()) {this->Terminal_Text(8,35, Terminal_GREEN, F(" OK "));} else {this->Terminal_Text(8,35, Terminal_RED, F("FAIL"));}

				// Detect MAX17055
				I2C_Functions I2C_MAX17055(__I2C_Addr_MAX17055__, true, 4);
				if (I2C_MAX17055.Detect()) {this->Terminal_Text(9,35, Terminal_GREEN, F(" OK "));} else {this->Terminal_Text(9,35, Terminal_RED, F("FAIL"));}

				// Detect BQ24298
				I2C_Functions I2C_BQ24298(__I2C_Addr_BQ24298__, true, 5);
				if (I2C_BQ24298.Detect()) {this->Terminal_Text(10,35, Terminal_GREEN, F(" OK "));} else {this->Terminal_Text(10,35, Terminal_RED, F("FAIL"));}

				// Detect SD
				if (this->Variables.Sense.SD_Card) {this->Terminal_Text(11,35, Terminal_GREEN, F(" OK "));} else {this->Terminal_Text(11,35, Terminal_RED, F("FAIL"));}

			}

			// Enable Interrupts
			void AVR_Enable_Interrupt(void) {

				// Set RTC Interrupt PCINT4
				this->AVR_Pin_Interrupt(1, true);

				// Set GSM Ring and PwrMon Interrupt PCINT11, PCINT12
				this->AVR_Pin_Interrupt(2, true);

				// Set Port K Interrupt PCINT16, PCINT17, PCINT18, PCINT19, PCINT20, PCINT21, PCINT22, PCINT23
				this->AVR_Pin_Interrupt(3, true);

				// Start Interrupts
				sei();

			}

			// Buzzer control function
			void Buzzer(uint8_t _Sound) {
			
				// If Buzzer is Active
				#ifdef B100BC_BUZZER
					
					switch(_Sound) {

						// Sound
						case Boot: {

							// Play Sound
							this->Tone(NOTE_E5, 50, 30);
							this->Tone(NOTE_E6, 55, 25);
							this->Tone(NOTE_A6, 60, 10);

							// End Case
							break;

						}

						// Sound
						case S_DISCONNECTION: {

							// Play Sound
							this->Tone(NOTE_E5, 50, 30);
							this->Tone(NOTE_A6, 55, 25);
							this->Tone(NOTE_E6, 50, 60);

							// End Case
							break;

						}

						// Sound
						case S_BUTTON_PUSHED: {

							// Play Sound
							this->Bend_Tones(NOTE_E6, NOTE_G6, 1.03, 20, 2);
							delay(30);
							this->Bend_Tones(NOTE_E6, NOTE_D7, 1.04, 10, 2);

							// End Case
							break;

						}

						// Sound
						case S_MODE1: {

							// Play Sound
							this->Bend_Tones(NOTE_E6, NOTE_A6, 1.02, 30, 10);    //1318.51 to 1760

							// End Case
							break;

						}

						// Sound
						case S_MODE2: {

							// Play Sound
							this->Bend_Tones(NOTE_G6, NOTE_D7, 1.03, 30, 10);    //1567.98 to 2349.32

							// End Case
							break;

						}

						// Sound
						case S_MODE3: {

							// Play Sound
							this->Tone(NOTE_E6,50,100);   //D6
							this->Tone(NOTE_G6,50,80);    //E6
							this->Tone(NOTE_D7,300,0);    //G6

							// End Case
							break;

						}

						// Sound
						case S_SURPRISE: {

							// Play Sound
							this->Bend_Tones(800, 2150, 1.02, 10, 1);
							this->Bend_Tones(2149, 800, 1.03, 7, 1);

							// End Case
							break;

						}

						// Sound
						case S_JUMP: {

							// Play Sound
							this->Bend_Tones(880, 2000, 1.04, 8, 3);   //A5 = 880
							delay(200);

							// End Case
							break;

						}

						// Sound
						case S_OHOOH: {

							// Play Sound
							this->Bend_Tones(880, 2000, 1.04, 8, 3);   //A5 = 880
							delay(200);
							for (int i=880; i<2000; i=i*1.04) this->Tone(NOTE_B5,5,10);

							// End Case
							break;

						}

						// Sound
						case S_OHOOH2: {

							// Play Sound
							this->Bend_Tones(1880, 3000, 1.03, 8, 3);
							delay(200);
							for (int i=1880; i<3000; i=i*1.03) this->Tone(NOTE_C6,10,10);

							// End Case
							break;

						}

						// Sound
						case S_CUDDLY: {

							// Play Sound
							this->Bend_Tones(700, 900, 1.03, 16, 4);
							this->Bend_Tones(899, 650, 1.01, 18, 7);

							// End Case
							break;

						}

						// Sound
						case S_SLEEPING: {

							// Play Sound
							this->Bend_Tones(100, 500, 1.04, 10, 10);
							delay(500);
							this->Bend_Tones(400, 100, 1.04, 10, 1);

							// End Case
							break;

						}

						// Sound
						case S_HAPPY: {

							// Play Sound
							this->Bend_Tones(1500, 2500, 1.05, 20, 8);
							this->Bend_Tones(2499, 1500, 1.05, 25, 8);

							// End Case
							break;

						}

						// Sound
						case S_SUPER_HAPPY: {

							// Play Sound
							this->Bend_Tones(2000, 6000, 1.05, 8, 3);
							delay(50);
							this->Bend_Tones(5999, 2000, 1.05, 13, 2);

							// End Case
							break;

						}

						// Sound
						case S_HAPPY_SHORT: {

							// Play Sound
							this->Bend_Tones(1500, 2000, 1.05, 15, 8);
							delay(100);
							this->Bend_Tones(1900, 2500, 1.05, 10, 8);

							// End Case
							break;

						}

						// Sound
						case S_SAD: {

							// Play Sound
							this->Bend_Tones(880, 669, 1.02, 20, 200);

							// End Case
							break;

						}

						// Sound
						case S_CONFUSED: {

							// Play Sound
							this->Bend_Tones(1000, 1700, 1.03, 8, 2);
							this->Bend_Tones(1699, 500, 1.04, 8, 3);
							this->Bend_Tones(1000, 1700, 1.05, 9, 10);

							// End Case
							break;

						}

						// Sound
						case S_FART1: {

							// Play Sound
							this->Bend_Tones(1600, 3000, 1.02, 2, 15);

							// End Case
							break;

						}

						// Sound
						case S_FART2: {

							// Play Sound
							this->Bend_Tones(2000, 6000, 1.02, 2, 20);

							// End Case
							break;

						}

						// Sound
						case S_FART3: {

							// Play Sound
							this->Bend_Tones(1600, 4000, 1.02, 2, 20);
							this->Bend_Tones(4000, 3000, 1.02, 2, 20);

							// End Case
							break;

						}
							
					}
					
				#endif

			}

			// Print Text to Specified Position and Color.
			void Terminal_Text(const uint8_t _X, const uint8_t _Y, const uint8_t _Color, const String _Value) {

				// Set Text Cursor Position
				this->Terminal_Set_Cursor(_X, _Y);

				// Set Text Color
				this->Terminal_Text_Color(_Color);

				// Print Text			
				Serial.print(String(_Value));

			}

			// LED Functions
			void LED(const uint8_t _Color, const uint8_t _Blink, const uint16_t _Interval) {

				// If Lights are active
				#ifdef B100BC_LIGHTS

					switch (_Color)	{

						// Red Color
						case __RED__: {

							// Blink
							for (size_t i = 0; i < _Blink; i++) {

								// Turn ON Red LED
								PORTD |= 0b10000000;

								// Delay
								delay(_Interval);

								// Turn OFF Red LED
								PORTD &= 0b01111111;

								// Delay
								delay(_Interval);

							}

							// End Case
							break;

						}

						// Green Color
						case __GREEN__: {

							// Blink
							for (size_t i = 0; i < _Blink; i++) {

								// Turn ON Green LED
								PORTD |= 0b01000000;

								// Delay
								delay(_Interval);

								// Turn OFF Green LED
								PORTD &= 0b10111111;

								// Delay
								delay(_Interval);

							}

							// End Case
							break;

						}

						// Blue Color
						case __BLUE__: {

							// Blink
							for (size_t i = 0; i < _Blink; i++) {

								// Turn ON Blue LED
								PORTD |= 0b00100000;

								// Delay
								delay(_Interval);

								// Turn OFF Blue LED
								PORTD &= 0b11011111;

								// Delay
								delay(_Interval);

							}

							// End Case
							break;

						}

						// Purple Color
						case __PURPLE__: {

							// Blink
							for (size_t i = 0; i < _Blink; i++) {

								// Turn ON Purple LED
								PORTD |= 0b10100000;

								// Delay
								delay(_Interval);

								// Turn OFF Purple LED
								PORTD &= 0b01011111;

								// Delay
								delay(_Interval);

							}

							// End Case
							break;

						}

						// White Color
						case __WHITE__: {

							// Blink
							for (size_t i = 0; i < _Blink; i++) {

								// Turn ON White LED
								PORTD |= 0b11100000;

								// Delay
								delay(_Interval);

								// Turn OFF White LED
								PORTD &= 0b01111111;

								// Delay
								delay(_Interval);

							}

							// End Case
							break;

						}

						default: {

							// Turn OFF all LED
							PORTD &= 0b00011111;

							// End Case
							break;

						}

					}

				#endif

			}

			// Timer Functions
			void Timer_Count(void) {

				// Set Timer Counter
				this->Variables.Timer_Counter += 1;

				// Handle Max
				if (this->Variables.Timer_Counter == 0xFFFFFFFF) this->Variables.Timer_Counter = 0;

			}
			bool Timer_Control(const uint16_t _Interval) {

				// Timer Counter
				if (this->Variables.Timer_Counter % _Interval == 0) return(true);

				// End Function
				return(false);

			}

			// Relay Functions
			inline void Relay(uint8_t _RelayType, uint8_t _Delay = 1) {

				// Select Relay Type
				switch (_RelayType)	{

					// Start Relay
					case __START__: {

						// Turn On Relay 1
						PORTL |= 0b00000001;
						
						// Time Delay
						delay(500);

						// Turn Off Relay 1
						PORTL &= 0b11111110;

						// End Case
						break;

					}
				
					// Stop Relay
					case __STOP__: {

						// Turn On Relay 2
						PORTL |= 0b00000010;
						
						// Time Delay
						delay(500);

						// Turn Off Relay 2
						PORTL &= 0b11111101;

						// End Case
						break;

					}

					// Alarm Relay
					case __ALARM__: {

						// Turn On Relay 3
						PORTL |= 0b00000100;
						
						// Time Delay
						delay(_Delay * 1000);

						// Turn Off Relay 3
						PORTL &= 0b11111011;

						// End Case
						break;

					}

					// Lock Stop Relay
					case __STOP_LOCK__: {

						// Turn On Relay 2
						PORTL |= 0b00000010;

						// End Case
						break;

					}

					// Lock Stop Relay
					case __STOP_UNLOCK__: {

						// Turn Off Relay 2
						PORTL &= 0b11111101;

						// End Case
						break;

					}

				}

			}

			// Read EEPROM Function
			uint16_t Get_EEPROM(uint8_t _Address) {

				// RTC Object Definitions	
				I2C_Functions I2C_RTC(__I2C_Addr_RV3028C7__, true, 1);
				RV3028 RTC(true, 1);

				// Read Registers
				uint8_t _High_Byte = (RTC.Read_EEPROM(_Address));
				uint8_t _Low_Byte = (RTC.Read_EEPROM(_Address + 0x01));

				// Combine Bytes
				uint16_t _Byte = (_High_Byte << 8) | _Low_Byte;

				// End Function
				return(_Byte);

			}

			// RTC Functions
			void Set_Timer(uint16_t Interval) {

				// RTC Object Definitions	
				I2C_Functions I2C_RTC(__I2C_Addr_RV3028C7__, true, 1);
				RV3028 RTC(true, 1);

				// Set Timer
				RTC.Set_Timer(false, 1, Interval, true, true, true);

			}

			// Measure Pressure
			void Measure_Pressure(void) {

				// Set Object
				Analog _Pressure_Sensor(0x01, 50, true, 1.5777, -1.1925);

				// Pressure Stats
				Pressure_Stats.Add(_Pressure_Sensor.Read());

				// Set Variables
				this->Variables.Pressure.Data_Count = Pressure_Stats.Variable.Data_Count;
				this->Variables.Pressure.Average = Pressure_Stats.Variable.Average;
				this->Variables.Pressure.Min = Pressure_Stats.Variable.Min;
				this->Variables.Pressure.Max = Pressure_Stats.Variable.Max;
				this->Variables.Pressure.Value = Pressure_Stats.Variable.Last;
				this->Variables.Pressure.Median = Pressure_Stats.Variable.Median;
				this->Variables.Pressure.Deviation = Pressure_Stats.Variable.Deviation;

			}

	};

#endif