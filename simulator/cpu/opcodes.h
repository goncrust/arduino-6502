/*
 * arduino-6502 (https://github.com/goncrust/arduino-6502)
 * 
 * Mapping opcodes to corresponding instructions
 *
 * Copyright (c) 2022 by goncrust
 * Released under the GPL v3.0
 * https://github.com/goncrust/arduino-6502/blob/main/LICENSE
 */

// ADC
// a
#define ADCa 0x6D
// a,x
#define ADCax 0x7D
// a,y
#define ADCay 0x79
// #
#define ADChash 0x69
// zp
#define ADCzp 0x65
// (zp,x)
#define ADC_zpx 0x61
// zp,x
#define ADCzpx 0x75
// (zp)
#define ADC_zp 0x72
// (zp),y
#define ADC_zp_y 0x71

// AND
// a
#define ANDa 0x2D
// a,x
#define ANDax 0x3D
// a,y
#define ANDay 0x39
// #
#define ANDhash 0x29
// zp
#define ANDzp 0x25
// (zp,x)
#define AND_zpx 0x21
// zp,x
#define ANDzpx 0x35
// (zp)
#define AND_zp 0x32
// (zp),y
#define AND_zp_y 0x31

// ASL
// a
#define ASLa 0x0E
// a,x
#define ASLax 0x1E
// A
#define ASLA 0x0A
// zp
#define ASLzp 0x06
// zp,x
#define ASLzpx 0x16

// BBR0
// r
#define BBR0r 0x0F

// BBR1
// r
#define BBR1r 0x1F

// BBR2
// r
#define BBR2r 0x2F

// BBR3
// r
#define BBR3r 0x3F

// BBR4
// r
#define BBR4r 0x4F

// BBR5
// r
#define BBR5r 0x5F

// BBR6
// r
#define BBR6r 0x6F

// BBR7
// r
#define BBR7r 0x7F

// BBS0
// r
#define BBS0r 0x8F

// BBS1
// r
#define BBS1r 0x9F

// BBS2
// r
#define BBS2r 0xAF

// BBS3
// r
#define BBS3r 0xBF

// BBS4
// r
#define BBS4r 0xCF

// BBS5
// r
#define BBS5r 0xDF

// BBS6
// r
#define BBS6r 0xEF

// BBS7
// r
#define BBS7r 0xFF

// BCC
// r
#define BCCr 0x90

// BCS
// r
#define BCSr 0xB0

// BEQ
// r
#define BEQr 0xF0

// BIT
// a
#define BITa 0x2C
// a,x
#define BITax 0x3C
// #
#define BIThash 0x89
// zp
#define BITzp 0x24
// zp,x
#define BITzpx 0x34

// BMI
// r
#define BMIr 0x30

// BNE
// r
#define BNEr 0xD0

// BPL
// r
#define BPLr 0x10

// BRA
// r
#define BRAr 0x80

// BRK
// s
#define BRKs 0x00

// BVC
// r
#define BVCr 0x50

// BVS
// r
#define BVSr 0x70

// CLC
// i
#define CLCi 0x18

// CLD
// i
#define CLDi 0xD8

// CLI
// i
#define CLIi 0x58

// CLV
// i
#define CLVi 0xB8

// CMP
// a
#define CMPa 0xCD
// a,x
#define CMPax 0xDD
// a,y
#define CMPay 0xD9
// #
#define CMPhash 0xC9
// zp
#define CMPzp 0xC5
// (zp,x)
#define CMP_zpx 0xC1
// zp,x
#define CMPzpx 0xD5
// (zp)
#define CMP_zp 0xD2
// (zp),y
#define CMP_zp_y 0xD1

// CPX
// a
#define CPXa 0xEC
// #
#define CPXhash 0xE0
// zp
#define CPXzp 0xE4

// CPY
// a
#define CPYa 0xCC
// #
#define CPYhash 0xC0
// zp
#define CPYzp 0xC4

// DEC
// a
#define DECa 0xCE
// a,x
#define DECax 0xDE
// A
#define DECA 0x3A
// zp
#define DECzp 0xC6
// zp,x
#define DECzpx 0xD6

// DEX
// i
#define DEXi 0xCA

// DEY
// i
#define DEYi 0x88

// EOR
// a
#define EORa 0x4D
// a,x
#define EORax 0x5D
// a,y
#define EORay 0x59
// #
#define EORhash 0x49
// zp
#define EORzp 0x45
// (zp,x)
#define EOR_zpx 0x41
// zp,x
#define EORzpx 0x55
// (zp)
#define EOR_zp 0x52
// (zp),y
#define EOR_zp_y 0x51

// INC
// a
#define INCa 0xEE
// a,x
#define INCax 0xFE
// A
#define INCA 0x1A
// zp
#define INCzp 0xE6
// zp,x
#define INCzpx 0xF6

// INX
// i
#define INXi 0xE8

// INY
// i
#define INYi 0xC8

// JMP
// a
#define JMPa 0x4C
// (a,x)
#define JMP_ax 0x7C
// (a)
#define JMP_a 0x6C

// JSR
// a
#define JSRa 0x20

// LDA
// a
#define LDAa 0xAD
// a,x
#define LDAax 0xBD
// a,y
#define LDAay 0xB9
// #
#define LDAhash 0xA9
// zp
#define LDAzp 0xA5
// (zp,x)
#define LDA_zpx 0xA1
// zp,x
#define LDAzpx 0xB5
// (zp)
#define LDA_zp 0xB2
// (zp),y
#define LDA_zp_y 0xB1

// LDX
// a
#define LDXa 0xAE
// a,y
#define LDXay 0xBE
// #
#define LDXhash 0xA2
// zp
#define LDXzp 0xA6
// zp,y
#define LDXzpy 0xB6

// LDY
// a
#define LDYa 0xAC
// a,x
#define LDYax 0xBC
// #
#define LDYhash 0xA0
// zp
#define LDYzp 0xA4
// zp,x
#define LDYzpx 0xB4

// LSR
// a
#define LSRa 0x4E
// a,x
#define LSRax 0x5E
// A
#define LSRA 0x4A
// zp
#define LSRzp 0x46
// zp,x
#define LSRzpx 0x56

// NOP
// i
#define NOPi 0xEA

// ORA
// a
#define ORAa 0x0D
// a,x
#define ORAax 0x1D
// a,y
#define ORAay 0x19
// #
#define ORAhash 0x09
// zp
#define ORAzp 0x05
// (zp,x)
#define ORA_zpx 0x01
// zp,x
#define ORAzpx 0x15
// (zp)
#define ORA_zp 0x12
// (zp),y
#define ORA_zp_y 0x11

// PHA
// s
#define PHAs 0x48

// PHP
// s
#define PHPs 0x08

// PHX
// s
#define PHXs 0xDA

// PHY
// s
#define PHYs 0x5A

// PLA
// s
#define PLAs 0x68

// PLP
// s
#define PLPs 0x28

// PLX
// s
#define PLXs 0xFA

// PLY
// s
#define PLYs 0x7A

// RMB0
// zp
#define RMB0zp 0x07

// RMB1
// zp
#define RMB1zp 0x17

// RMB2
// zp
#define RMB2zp 0x27

// RMB3
// zp
#define RMB3zp 0x37

// RMB4
// zp
#define RMB4zp 0x47

// RMB5
// zp
#define RMB5zp 0x57

// RMB6
// zp
#define RMB6zp 0x67

// RMB7
// zp
#define RMB7zp 0x77

// ROL
// a
#define ROLa 0x2E
// a,x
#define ROLax 0x3E
// A
#define ROLA 0x2A
// zp
#define ROLzp 0x26
// zp,x
#define ROLzpx 0x36

// ROR
// a
#define RORa 0x2E
// a,x
#define RORax 0x3E
// A
#define RORA 0x2A
// zp
#define RORzp 0x66
// zp,x
#define RORzpx 0x76

// RTI
// s
#define RTIs 0x40

// RTS
// s
#define RTSs 0x60

// SBC
// a
#define SBCa 0xED
// a,x
#define SBCax 0xFD
// a,y
#define SBCay 0xF9
// #
#define SBChash 0xE9
// zp
#define SBCzp 0xE5
// (zp,x)
#define SBC_zpx 0xE1
// zp,x
#define SBCzpx 0xF5
// (zp)
#define SBC_zp 0xF2
// (zp),y
#define SBC_zp_y 0xF1

// SEC
// i
#define SECi 0x38

// SED
// i
#define SEDi 0xF8

// SEI
// i
#define SEIi 0x78

// SMB0
// zp
#define SMB0zp 0x87

// SMB1
// zp
#define SMB1zp 0x97

// SMB2
// zp
#define SMB2zp 0xA7

// SMB3
// zp
#define SMB3zp 0xB7

// SMB4
// zp
#define SMB4zp 0xC7

// SMB5
// zp
#define SMB5zp 0xD7

// SMB6
// zp
#define SMB6zp 0xE7

// SMB7
// zp
#define SMB7zp 0xF7

// STA
// a
#define STAa 0x8D
// a,x
#define STAax 0x9D
// a,y
#define STAay 0x99
// zp
#define STAzp 0x85
// (zp,x)
#define STA_zpx 0x81
// zp,x
#define STAzpx 0x95
// (zp)
#define STA_zp 0x92
// (zp),y
#define STA_zp_y 0x91

// STP
// i
#define STPi 0xDB

// STX
// a
#define STXa 0x8E
// zp
#define STXzp 0x86
// zp,y
#define STXzpy 0x96

// STY
// a
#define STYa 0x8C
// zp
#define STYzp 0x84
// zp,x
#define STYzpx 0x94

// STZ
// a
#define STZa 0x9C
// a,x
#define STZax 0x9E
// zp
#define STZzp 0x64
// zp,x
#define STZzpx 0x74

// TAX
// i
#define TAXi 0xAA

// TAY
// i
#define TAYi 0xA8

// TRB
// a
#define TRBa 0x1C
// zp
#define TRBzp 0x14

// TSB
// a
#define TSBa 0x0C
// zp
#define TSBzp 0x04

// TSX
// i
#define TSXi 0xBA

// TXA
// i
#define TXAi 0x8A

// TXS
// i
#define TXSi 0x9A

// TYA
// i
#define TYAi 0x98

// WAI
// i
#define WAIi 0xCB

