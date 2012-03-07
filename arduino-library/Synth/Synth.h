/*!
 *  @file		  Synth.h
 *  Project		Synth Library
 *	@brief		Synth Library for the Arduino
 *	Version		1.0
 *  @author		Davey Taylor
 *	@date		  2012-03-06 (YYYY-MM-DD)
 *  License		GPL Forty Seven Effects - 2011
 */

#ifndef LIB_SYNTH_H_
#define LIB_SYNTH_H_

#include <inttypes.h> 

#define MIDI_QUEUE_SIZE 8

// High performance digitalWrite
#define pinPort( P ) ( ( P ) <= 7 ? &PORTD : ( ( P ) <= 13 ? &PORTB : &PORTC ) )
#define pinBit( P ) ( ( P ) <= 7 ? ( P ) : ( ( P ) <= 13 ? ( P ) - 8 : ( P ) - 14 ) )
#define fastWrite( P, V ) bitWrite( *pinPort( P ), pinBit( P ), ( V ) );

// Pin declarations
#define PCM_LCH 10 // Shift register latch
#define PCM_SDA A3 // Shift register data
#define PCM_CLK 13 // Shift register clock (PCM)
#define FLT_CLK A5 // Shift register clock (Filter select)
#define FLT_WR  12 // Filter write
#define FLT_D0   8 // Filter data 0
#define FLT_D1   9 // Filter data 1
#define FLT_A0  A2 // Filter address 0
#define FLT_A1  A4 // Filter address 1
#define FLT_A2   5 // Filter address 2
#define FLT_A3   7 // Filter address 3
#define FLT_F0   6 // Filter clock 0
#define FLT_F1  11 // Filter clock 1

enum filter_e {
  FILTER_LP = 0x01,
  FILTER_BP = 0x02,
  FILTER_HP = 0x04
};

enum midi_e {
	NoteOff	             = 0x80, // Channel - Note Off
	NoteOn               = 0x90, // Channel - Note On
	AfterTouchPoly       = 0xA0, // Channel - Polyphonic AfterTouch
	ControlChange        = 0xB0, // Channel - Control Change / Channel Mode
	ProgramChange        = 0xC0, // Channel - Program Change
	AfterTouchChannel    = 0xD0, // Channel - Monophonic AfterTouch
	PitchBend            = 0xE0, // Channel - Pitch Bend
	TimeCodeQuarterFrame = 0xF1, // System - Time Code
	SongPosition         = 0xF2, // System - Song Position
	SongSelect           = 0xF3, // System - Song Select
	TuneRequest          = 0xF6, // System - Tune Request
	Clock                = 0xF8, // Real Time - Clock
	Start                = 0xFA, // Real Time - Start
	Continue             = 0xFB, // Real Time - Continue
	Stop                 = 0xFC, // Real Time - Stop
	ActiveSensing        = 0xFE, // Real Time - Sensing
	SystemReset          = 0xFF, // Real Time - Reset
};

typedef struct {
  uint8_t message;
  uint8_t channel;
  uint8_t data1;
  uint8_t data2;
} midi_t;

extern const float noteTable[];

class Synth_Class {

public:
	Synth_Class();
	~Synth_Class();

  // Initialize synth hardware to use sample rate specified in hz
	void begin( uint16_t sample_rate = 8000 );
  
  // Reads a MIDI message from synth
	midi_t* readMidi( void );
	
  // **********************************************************************
  // Refer to the datasheet for detailed information on the filter settings
  // **********************************************************************
  
	// Sets the filter FILTER_LP/FILTER_BP/FILTER_HP for filter 0...1
	// This refers to which output pin of the filter is connected
  void setFilter( uint8_t filter, uint8_t type );
  
  // Sets F-value 4...40000hz for filter 0...1
  // This value refers to the center/cut-off frequency of the filter
  void setCutoff( uint8_t filter, float freq );
  
  // Sets mode-value 0...3 for filter 0...1
  // This value refers to different operating modes for the filter
  // Not all combinations of setFilter and setMode are intended to be used
  void setMode( uint8_t filter, uint8_t mode );
  
  // Sets f0-value to 0...3F for filter 0...1
  // This refers to a shift/offset from the value set by setCutOff
  void setShift( uint8_t filter, uint8_t mode );
  
  // Sets q-value of filter 0...1 to 0...3F
  // This refers to the filters resonance
  void setResonance( uint8_t filter, uint8_t q );

};

extern Synth_Class Synth;

#endif // LIB_SYNTH_H_