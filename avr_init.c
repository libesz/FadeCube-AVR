//{{AVR_IO_DESIGNER_INIT
	// D:\[prog]\avr_git\ledcube_3\ledcube_3.aid

	//
	// Project Options - ledcube_3
	//
	// Device Name = ATmega32
	// CPU Frequency (F_CPU) = 16,0 MHz
	// IC Package = TQFP
	// Sort Pins by = Pin Number
	// Output Code File = avr_init.c
	// Output Header File = avr_init.h
	// Assume Default State = True
	// Write Unmodified Bits = True
	// Set Unused PORT Pins = Input
	MCUCSR = 0x80;	// (1<<JTD)

	//
	// PORTA variable initializations
	//
	// PORTA0 for 1: ROW_CLK as Output - 4017 clock input
	// PORTA1 for 1: ROW_RESET as Output - 4017 reset input
	// PORTA2 for 1: COL_XLAT as Output - TLC5947 XLAT input
	// PORTA3 for 1: COL_DATA as Output - TLC5947 serial data input
	// PORTA4 for 1: COL_CLK as Output - TLC5947 clock input
	// PORTA5 for 1: COL_BLANK as Output - TLC5947 BLANK input
	DDRA = 0x3F;
	PORTB = 0x10;

	//
	// SPI
	//
	// Master/Slave Mode = Master Mode
	SPCR = 0x10;	// (1<<MSTR)

	//
	// TIMER_COUNTER_0 -  - 
	//
	// Waveform Generation Mode = Clear Timer on Compare Match TOP=OCRA
	// Clock Select = clk / 1024 (From prescaler)
	// Output Compare Register = 23
	// Output Compare Match Interrupt Enable = Enabled
	// Counter Frequency = 651,042 Hz
	// Counter Period = 1,536 msec
	// Seconds per Count = 64,0 usec
	// Counts per Second = 15,625 kHz
	// Output Compare Register Time = 1,472 msec
	TCCR0 = 0x0D;	// (0<<WGM00)|(1<<WGM01)|(1<<CS02)|(0<<CS01)|(1<<CS00)
	OCR0 = 0x17;
	TIMSK = 0x02;	// (1<<OCIE0)|(0<<TOIE0)

	//
	// JTAG
	//
	// NOTE: The following assumes that interrupts are disabled
	// Write the JTD bit twice as part of the change protocol requirements
	MCUCSR |= 0x80;	// (1<<JTD)
	MCUCSR |= 0x80;	// (1<<JTD)
//}}AVR_IO_DESIGNER_INIT
