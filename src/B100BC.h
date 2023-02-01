#ifndef __B100BC__
#define __B100BC__

	// Define Configuration
	#define B100BC_BUZZER
	#define B100BC_LIGHTS

	// Define Arduino Library
	#ifndef __Arduino__
		#include <Arduino.h>
	#endif

	// Include Libraries
	#ifndef __Sounds__
		#include "Sounds.h"
	#endif

	// Define LED Colors
	#define	__WHITE__		(uint8_t) 0
	#define	__RED__			(uint8_t) 1
	#define	__GREEN__		(uint8_t) 2
	#define	__BLUE__		(uint8_t) 3
	#define	__PURPLE__		(uint8_t) 4

	// Define Relay States
	#define	__START__		(uint8_t) 1
	#define	__STOP__		(uint8_t) 2
	#define	__ALARM__		(uint8_t) 3
	#define	__STOP_LOCK__	(uint8_t) 4
	#define	__STOP_UNLOCK__	(uint8_t) 5

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

	};

#endif