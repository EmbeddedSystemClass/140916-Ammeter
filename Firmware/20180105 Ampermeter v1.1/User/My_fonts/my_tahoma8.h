

/*
 *
 * Tahoma7
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : tahoma7.h
 * Date                : 11.10.2015
 * Font size in bytes  : 3174
 * Font width          : 5
 * Font height         : 8
 * Font first char     : 32
 * Font last char      : 128
 * Font used chars     : 96
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>

#ifndef TAHOMA8_H
#define TAHOMA8_H

static uint8_t Tahoma8Cyrillic[]= {
    0x12, 0xF5, // size
    0x09, // width
    0x0A, // height
    0x20, // first char
    0x61, // char count
    
    // char widths
    0x05, 0x01, 0x03, 0x05, 0x05, 0x05, 0x06, 0x01, 0x03, 0x03, 
    0x05, 0x05, 0x02, 0x05, 0x02, 0x03, 0x05, 0x03, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x02, 0x02, 0x04, 0x05, 
    0x04, 0x05, 0x09, 0x06, 0x05, 0x05, 0x05, 0x06, 0x05, 0x07, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x07, 0x05, 0x05, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x07, 0x05, 0x05, 0x05, 0x07, 0x07, 0x06, 
    0x07, 0x05, 0x05, 0x07, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x07, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x07, 0x05, 0x05, 0x05, 0x07, 
    0x07, 0x06, 0x06, 0x05, 0x05, 0x06, 0x05, 
    
    // font data
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 32
    0x7E, 0x40, // 33
    0x07, 0x00, 0x07, 0x00, 0x00, 0x00, // 34
    0x48, 0xFE, 0x48, 0xFE, 0x48, 0x00, 0x40, 0x00, 0x40, 0x00, // 35
    0x0C, 0x12, 0xFF, 0x12, 0xE2, 0x40, 0x40, 0xC0, 0x40, 0x00, // 36
    0x06, 0xC6, 0x30, 0x88, 0x86, 0x40, 0x00, 0x00, 0x40, 0x40, // 37
    0xEC, 0x12, 0x12, 0x2C, 0xC0, 0xA0, 0x00, 0x40, 0x40, 0x40, 0x00, 0x00, // 38
    0x07, 0x00, // 39
    0x78, 0x86, 0x01, 0x00, 0x40, 0x80, // 40
    0x01, 0x86, 0x78, 0x80, 0x40, 0x00, // 41
    0x0A, 0x04, 0x1F, 0x04, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, // 42
    0x20, 0x20, 0xF8, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, // 43
    0x80, 0x80, 0x80, 0x40, // 44
    0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, // 45
    0x80, 0x80, 0x40, 0x40, // 46
    0x80, 0x78, 0x07, 0xC0, 0x00, 0x00, // 47
    0xFC, 0x02, 0x02, 0x02, 0xFC, 0x00, 0x40, 0x40, 0x40, 0x00, // 48
    0x04, 0xFE, 0x00, 0x40, 0x40, 0x40, // 49
    0x84, 0x42, 0x22, 0x12, 0x0C, 0x40, 0x40, 0x40, 0x40, 0x40, // 50
    0x84, 0x02, 0x12, 0x12, 0xEC, 0x00, 0x40, 0x40, 0x40, 0x00, // 51
    0x30, 0x28, 0x24, 0xFE, 0x20, 0x00, 0x00, 0x00, 0x40, 0x00, // 52
    0x1E, 0x12, 0x12, 0x12, 0xE2, 0x40, 0x40, 0x40, 0x40, 0x00, // 53
    0xF8, 0x14, 0x12, 0x12, 0xE0, 0x00, 0x40, 0x40, 0x40, 0x00, // 54
    0x02, 0x82, 0x62, 0x1A, 0x06, 0x00, 0x40, 0x00, 0x00, 0x00, // 55
    0xEC, 0x12, 0x12, 0x12, 0xEC, 0x00, 0x40, 0x40, 0x40, 0x00, // 56
    0x1C, 0x22, 0x22, 0xA2, 0x7C, 0x00, 0x40, 0x40, 0x00, 0x00, // 57
    0xD8, 0xD8, 0x00, 0x00, // 58
    0x58, 0xD8, 0x40, 0x00, // 59
    0x20, 0x50, 0x88, 0x04, 0x00, 0x00, 0x00, 0x40, // 60
    0x20, 0x20, 0xF8, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, // 61
    0x04, 0x88, 0x50, 0x20, 0x40, 0x00, 0x00, 0x00, // 62
    0x02, 0x01, 0x61, 0x11, 0x0E, 0x00, 0x00, 0x40, 0x00, 0x00, // 63
    0xFC, 0x02, 0x79, 0x85, 0x85, 0xFD, 0x81, 0x82, 0x7C, 0x00, 0x40, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, // 64
    0xF8, 0x24, 0x22, 0x22, 0x24, 0xF8, 0x40, 0x00, 0x00, 0x00, 0x00, 0x40, // 65	A
    0xFE, 0x12, 0x12, 0x12, 0xE0, 0x40, 0x40, 0x40, 0x40, 0x00, // 66
    0xFE, 0x12, 0x12, 0x12, 0xEC, 0x40, 0x40, 0x40, 0x40, 0x00, // 67
    0xFE, 0x02, 0x02, 0x02, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, // 68
    0x00, 0xC2, 0x3E, 0x02, 0xFE, 0x00, 0xC0, 0x40, 0x40, 0x40, 0x40, 0xC0, // 69
    0xFE, 0x12, 0x12, 0x12, 0x02, 0x40, 0x40, 0x40, 0x40, 0x40, // 70
    0xC6, 0x38, 0x10, 0xFE, 0x10, 0x38, 0xC6, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, // 71
    0x02, 0x12, 0x12, 0x12, 0xEC, 0x40, 0x40, 0x40, 0x40, 0x00, // 72
    0xFE, 0x40, 0x20, 0x10, 0xFE, 0x40, 0x00, 0x00, 0x00, 0x40, // 73
    0xFC, 0x41, 0x22, 0x11, 0xFC, 0x40, 0x00, 0x00, 0x00, 0x40, // 74
    0xFE, 0x10, 0x28, 0x44, 0x82, 0x40, 0x00, 0x00, 0x00, 0x40, // 75
    0x80, 0x02, 0xFE, 0x02, 0xFE, 0x00, 0x40, 0x00, 0x00, 0x40, // 76
    0xFE, 0x04, 0x08, 0x10, 0x08, 0x04, 0xFE, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, // 77
    0xFE, 0x10, 0x10, 0x10, 0xFE, 0x40, 0x00, 0x00, 0x00, 0x40, // 78
    0xFC, 0x02, 0x02, 0x02, 0xFC, 0x00, 0x40, 0x40, 0x40, 0x00, // 79
    0xFE, 0x02, 0x02, 0x02, 0xFE, 0x40, 0x00, 0x00, 0x00, 0x40, // 80
    0xFE, 0x22, 0x22, 0x22, 0x1C, 0x40, 0x00, 0x00, 0x00, 0x00, // 81
    0xFC, 0x02, 0x02, 0x02, 0x84, 0x00, 0x40, 0x40, 0x40, 0x00, // 82
    0x02, 0x02, 0xFE, 0x02, 0x02, 0x00, 0x00, 0x40, 0x00, 0x00, // 83
    0x1E, 0xA0, 0x40, 0x20, 0x1E, 0x40, 0x00, 0x00, 0x00, 0x00, // 84
    0x1C, 0x22, 0x22, 0xFE, 0x22, 0x22, 0x1C, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, // 85
    0xC6, 0x28, 0x10, 0x28, 0xC6, 0x40, 0x00, 0x00, 0x00, 0x40, // 86
    0xFE, 0x00, 0x00, 0x00, 0xFE, 0x40, 0x40, 0x40, 0x40, 0xC0, // 87
    0x1E, 0x20, 0x20, 0x20, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x40, // 88
    0xFE, 0x00, 0x00, 0xFE, 0x00, 0x00, 0xFE, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, // 89
    0xFE, 0x00, 0x00, 0xFE, 0x00, 0x00, 0xFE, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xC0, // 90
    0x02, 0xFE, 0x20, 0x20, 0x20, 0xC0, 0x00, 0x40, 0x40, 0x40, 0x40, 0x00, // 91
    0xFE, 0x20, 0x20, 0x20, 0xC0, 0x00, 0xFE, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00, 0x40, // 92
    0xFE, 0x20, 0x20, 0x20, 0xC0, 0x40, 0x40, 0x40, 0x40, 0x00, // 93
    0x84, 0x02, 0x12, 0x12, 0xFC, 0x00, 0x40, 0x40, 0x40, 0x00, // 94
    0xFE, 0x30, 0xFC, 0x02, 0x02, 0x02, 0xFC, 0x40, 0x00, 0x00, 0x40, 0x40, 0x40, 0x00, // 95
    0x1C, 0xA2, 0x62, 0x22, 0xFE, 0x40, 0x00, 0x00, 0x00, 0x40, // 96
    0xC0, 0x28, 0x28, 0x28, 0xF0, 0x00, 0x40, 0x40, 0x40, 0x40, // 97
    0xF8, 0x14, 0x14, 0x12, 0xE0, 0x00, 0x40, 0x40, 0x40, 0x00, // 98
    0xF8, 0x28, 0x28, 0x28, 0xD0, 0x40, 0x40, 0x40, 0x40, 0x00, // 99
    0xF8, 0x08, 0x08, 0x08, 0x08, 0x40, 0x00, 0x00, 0x00, 0x00, // 100
    0x80, 0x48, 0x38, 0x08, 0xF8, 0x40, 0x40, 0x40, 0x40, 0x40, // 101
    0xF0, 0x28, 0x28, 0x28, 0x30, 0x00, 0x40, 0x40, 0x40, 0x00, // 102
    0xD8, 0x20, 0xF8, 0x20, 0xD8, 0x40, 0x00, 0x40, 0x00, 0x40, // 103
    0x08, 0x28, 0x28, 0x28, 0xD0, 0x40, 0x40, 0x40, 0x40, 0x00, // 104
    0xF8, 0x80, 0x40, 0x20, 0xF8, 0x40, 0x00, 0x00, 0x00, 0x40, // 105
    0xF8, 0x82, 0x44, 0x22, 0xF8, 0x40, 0x00, 0x00, 0x00, 0x40, // 106
    0xF8, 0x20, 0x50, 0x88, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40, // 107
    0x80, 0x08, 0xF8, 0x08, 0xF8, 0x00, 0x40, 0x00, 0x00, 0x40, // 108
    0xF8, 0x10, 0x20, 0x40, 0x20, 0x10, 0xF8, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, // 109
    0xF8, 0x20, 0x20, 0x20, 0xF8, 0x40, 0x00, 0x00, 0x00, 0x40, // 110
    0xF0, 0x08, 0x08, 0x08, 0xF0, 0x00, 0x40, 0x40, 0x40, 0x00, // 111
    0xF8, 0x08, 0x08, 0x08, 0xF8, 0x40, 0x00, 0x00, 0x00, 0x40, // 112
    0xF8, 0x48, 0x48, 0x48, 0x30, 0x40, 0x00, 0x00, 0x00, 0x00, // 113
    0xF0, 0x08, 0x08, 0x08, 0x90, 0x00, 0x40, 0x40, 0x40, 0x00, // 114
    0x08, 0x08, 0xF8, 0x08, 0x08, 0x00, 0x00, 0x40, 0x00, 0x00, // 115
    0x38, 0x40, 0x40, 0x40, 0xF8, 0x00, 0x40, 0x40, 0x40, 0x00, // 116
    0x30, 0x48, 0x48, 0xF8, 0x48, 0x48, 0x30, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, // 117
    0x88, 0x50, 0x20, 0x50, 0x88, 0x40, 0x00, 0x00, 0x00, 0x40, // 118
    0xF8, 0x00, 0x00, 0x00, 0xF8, 0x40, 0x40, 0x40, 0x40, 0xC0, // 119
    0x38, 0x40, 0x40, 0x40, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x40, // 120
    0xF8, 0x00, 0x00, 0xF8, 0x00, 0x00, 0xF8, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, // 121
    0xF8, 0x00, 0x00, 0xF8, 0x00, 0x00, 0xF8, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xC0, // 122
    0x08, 0xF8, 0x20, 0x20, 0x20, 0xC0, 0x00, 0x40, 0x40, 0x40, 0x40, 0x00, // 123
    0xF8, 0x20, 0x20, 0xC0, 0x00, 0xF8, 0x40, 0x40, 0x40, 0x00, 0x00, 0x40, // 124
    0xF8, 0x20, 0x20, 0x20, 0xC0, 0x40, 0x40, 0x40, 0x40, 0x00, // 125
    0x08, 0x28, 0x28, 0x28, 0xF0, 0x40, 0x40, 0x40, 0x40, 0x00, // 126
    0xF8, 0x40, 0xF0, 0x08, 0x08, 0xF0, 0x40, 0x00, 0x00, 0x40, 0x40, 0x00, // 127
    0x30, 0x48, 0xC8, 0x48, 0xF8, 0x40, 0x40, 0x00, 0x00, 0x40 // 128
};

 
 
 
#endif






