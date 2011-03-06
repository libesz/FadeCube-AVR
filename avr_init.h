//{{AVR_IO_DESIGNER_HDR
// D:\[prog]\avr_git\ledcube_3\ledcube_3.aid

//
// PORTA variable definitions
//
typedef struct
{
	unsigned char	_ROW_CLK         : 1;	// 4017 clock input
	unsigned char	_ROW_RESET       : 1;	// 4017 reset input
	unsigned char	_COL_XLAT        : 1;	// TLC5947 XLAT input
	unsigned char	_COL_DATA        : 1;	// TLC5947 serial data input
	unsigned char	_COL_CLK         : 1;	// TLC5947 clock input
	unsigned char	_COL_BLANK       : 1;	// TLC5947 BLANK input
	unsigned char	_Unused6         : 1;	// 
	unsigned char	_Unused7         : 1;	// 
} PORTA_STRUCT;

// PORTA0 for 1: ROW_CLK as Output - 4017 clock input
#define	ROW_CLK_PORT            ((volatile PORTA_STRUCT*)&PORTA)        // PORT register
#define	ROW_CLK_PIN             ((volatile PORTA_STRUCT*)&PINA)         // PIN register
#define	ROW_CLK_DDR             ((volatile PORTA_STRUCT*)&DDRA)         // DDR register
#define	ROW_CLK                 ROW_CLK_PORT->_ROW_CLK                  // output
#define	ROW_CLK_TOGGLE          ROW_CLK_PIN->_ROW_CLK                   // output toggle
#define	ROW_CLK_DIR             ROW_CLK_DDR->_ROW_CLK                   // direction control
#define	ROW_CLK_MASK            0x01                                    // mask
#define	ROW_CLK_SHIFT           0x00                                    // shift count

// PORTA1 for 1: ROW_RESET as Output - 4017 reset input
#define	ROW_RESET_PORT          ((volatile PORTA_STRUCT*)&PORTA)        // PORT register
#define	ROW_RESET_PIN           ((volatile PORTA_STRUCT*)&PINA)         // PIN register
#define	ROW_RESET_DDR           ((volatile PORTA_STRUCT*)&DDRA)         // DDR register
#define	ROW_RESET               ROW_RESET_PORT->_ROW_RESET              // output
#define	ROW_RESET_TOGGLE        ROW_RESET_PIN->_ROW_RESET               // output toggle
#define	ROW_RESET_DIR           ROW_RESET_DDR->_ROW_RESET               // direction control
#define	ROW_RESET_MASK          0x02                                    // mask
#define	ROW_RESET_SHIFT         0x01                                    // shift count

// PORTA2 for 1: COL_XLAT as Output - TLC5947 XLAT input
#define	COL_XLAT_PORT           ((volatile PORTA_STRUCT*)&PORTA)        // PORT register
#define	COL_XLAT_PIN            ((volatile PORTA_STRUCT*)&PINA)         // PIN register
#define	COL_XLAT_DDR            ((volatile PORTA_STRUCT*)&DDRA)         // DDR register
#define	COL_XLAT                COL_XLAT_PORT->_COL_XLAT                // output
#define	COL_XLAT_TOGGLE         COL_XLAT_PIN->_COL_XLAT                 // output toggle
#define	COL_XLAT_DIR            COL_XLAT_DDR->_COL_XLAT                 // direction control
#define	COL_XLAT_MASK           0x04                                    // mask
#define	COL_XLAT_SHIFT          0x02                                    // shift count

// PORTA3 for 1: COL_DATA as Output - TLC5947 serial data input
#define	COL_DATA_PORT           ((volatile PORTA_STRUCT*)&PORTA)        // PORT register
#define	COL_DATA_PIN            ((volatile PORTA_STRUCT*)&PINA)         // PIN register
#define	COL_DATA_DDR            ((volatile PORTA_STRUCT*)&DDRA)         // DDR register
#define	COL_DATA                COL_DATA_PORT->_COL_DATA                // output
#define	COL_DATA_TOGGLE         COL_DATA_PIN->_COL_DATA                 // output toggle
#define	COL_DATA_DIR            COL_DATA_DDR->_COL_DATA                 // direction control
#define	COL_DATA_MASK           0x08                                    // mask
#define	COL_DATA_SHIFT          0x03                                    // shift count

// PORTA4 for 1: COL_CLK as Output - TLC5947 clock input
#define	COL_CLK_PORT            ((volatile PORTA_STRUCT*)&PORTA)        // PORT register
#define	COL_CLK_PIN             ((volatile PORTA_STRUCT*)&PINA)         // PIN register
#define	COL_CLK_DDR             ((volatile PORTA_STRUCT*)&DDRA)         // DDR register
#define	COL_CLK                 COL_CLK_PORT->_COL_CLK                  // output
#define	COL_CLK_TOGGLE          COL_CLK_PIN->_COL_CLK                   // output toggle
#define	COL_CLK_DIR             COL_CLK_DDR->_COL_CLK                   // direction control
#define	COL_CLK_MASK            0x10                                    // mask
#define	COL_CLK_SHIFT           0x04                                    // shift count

// PORTA5 for 1: COL_BLANK as Output - TLC5947 BLANK input
#define	COL_BLANK_PORT          ((volatile PORTA_STRUCT*)&PORTA)        // PORT register
#define	COL_BLANK_PIN           ((volatile PORTA_STRUCT*)&PINA)         // PIN register
#define	COL_BLANK_DDR           ((volatile PORTA_STRUCT*)&DDRA)         // DDR register
#define	COL_BLANK               COL_BLANK_PORT->_COL_BLANK              // output
#define	COL_BLANK_TOGGLE        COL_BLANK_PIN->_COL_BLANK               // output toggle
#define	COL_BLANK_DIR           COL_BLANK_DDR->_COL_BLANK               // direction control
#define	COL_BLANK_MASK          0x20                                    // mask
#define	COL_BLANK_SHIFT         0x05                                    // shift count

// TIMER_COUNTER_0 -  - 
#define	TIMER_COUNTER_0_Divisor	1024
#define	TIMER_COUNTER_0_CountsPerSecond	15625
#define	TIMER_COUNTER_0_usPerCount	64              // (64)
#define	TIMER_COUNTER_0_nsPerCount	64000           // (64000)
#define	TIMER_COUNTER_0_msPeriod	2               // (1,536)
#define	TIMER_COUNTER_0_usPeriod	1536            // (1536)
#define	TIMER_COUNTER_0_nsPeriod	1536000         // (1536000)
//}}AVR_IO_DESIGNER_HDR
