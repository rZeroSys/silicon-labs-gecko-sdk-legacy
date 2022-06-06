/*****************************************************************************/
/**
 * Copyright 2017 Silicon Laboratories, Inc.
 *
 *****************************************************************************/

#ifndef SILABS_DMP_BITMAPS_H
#define SILABS_DMP_BITMAPS_H

#define SILICONLABS_BITMAP_WIDTH        128
#define SILICONLABS_BITMAP_HEIGHT       45
#define SILICONLABS_X_POSITION          ((glibContext.pDisplayGeometry->xSize - SILICONLABS_BITMAP_WIDTH) / 2)
#define SILICONLABS_Y_POSITION          0
#define LIGHT_BITMAP_WIDTH              64
#define LIGHT_BITMAP_HEIGHT             64
#define LIGHT_X_POSITION                ((glibContext.pDisplayGeometry->xSize - LIGHT_BITMAP_WIDTH) / 2)
#define LIGHT_Y_POSITION                (glibContext.pDisplayGeometry->ySize - LIGHT_BITMAP_HEIGHT - 5)
#define PROT1_ID_X_POSITION         1
#define PROT2_ID_X_POSITION         79
#ifdef PROT_ZIGBEE
#if (PROT1 == PROT_ZIGBEE)
#define PROT1_BITMAP_WIDTH          16
#define PROT1_BITMAP_HEIGHT         16
#define PROT1_X_POSITION            8
#define PROT1_Y_POSITION            (LIGHT_Y_POSITION + (LIGHT_Y_POSITION / 2)) + 2
#elif (PROT2 == PROT_ZIGBEE)
#define PROT2_BITMAP_WIDTH          16
#define PROT2_BITMAP_HEIGHT         16
#define PROT2_X_POSITION            104
#define PROT2_Y_POSITION            (LIGHT_Y_POSITION + (LIGHT_Y_POSITION / 2)) + 2
#endif // PROT1 | PROT2
#endif // PROT_ZIGBEE
#ifdef PROT_RAIL
#if (PROT1 == PROT_RAIL)
#define PROT1_BITMAP_WIDTH          16
#define PROT1_BITMAP_HEIGHT         16
#define PROT1_X_POSITION            8
#define PROT1_Y_POSITION            (LIGHT_Y_POSITION + (LIGHT_Y_POSITION / 2)) + 2
#elif (PROT2 == PROT_RAIL)
#define PROT2_BITMAP_WIDTH          16
#define PROT2_BITMAP_HEIGHT         16
#define PROT2_X_POSITION            104
#define PROT2_Y_POSITION            (LIGHT_Y_POSITION + (LIGHT_Y_POSITION / 2)) + 2
#endif // PROT1 | PROT2
#endif // PROT_RAIL
#ifdef PROT_CONNECT
#if (PROT1 == PROT_CONNECT)
#define PROT1_BITMAP_WIDTH          16
#define PROT1_BITMAP_HEIGHT         16
#define PROT1_X_POSITION            8
#define PROT1_Y_POSITION            (LIGHT_Y_POSITION + (LIGHT_Y_POSITION / 2)) + 2
#elif (PROT2 == PROT_CONNECT)
#define PROT2_BITMAP_WIDTH          16
#define PROT2_BITMAP_HEIGHT         16
#define PROT2_X_POSITION            104
#define PROT2_Y_POSITION            (LIGHT_Y_POSITION + (LIGHT_Y_POSITION / 2)) + 2
#endif // PROT1 | PROT2
#endif // PROT_CONNECTS
#ifdef PROT_BLUETOOTH
#if (PROT1 == PROT_BLUETOOTH)
#define PROT1_BITMAP_WIDTH          16
#define PROT1_BITMAP_HEIGHT         18
#define PROT1_X_POSITION            8
#define PROT1_Y_POSITION            (LIGHT_Y_POSITION + (LIGHT_Y_POSITION / 2))
#elif (PROT2 == PROT_BLUETOOTH)
#define PROT2_BITMAP_WIDTH          16
#define PROT2_BITMAP_HEIGHT         18
#define PROT2_X_POSITION            104
#define PROT2_Y_POSITION            (LIGHT_Y_POSITION + (LIGHT_Y_POSITION / 2))
#endif // PROT1 | PROT2
#endif // PROT_BLUETOOTH
#ifdef PROT_THREAD
#if (PROT1 == PROT_THREAD)
#define PROT1_BITMAP_WIDTH          16
#define PROT1_BITMAP_HEIGHT         18
#define PROT1_X_POSITION            8
#define PROT1_Y_POSITION            (LIGHT_Y_POSITION + (LIGHT_Y_POSITION / 2))
#elif (PROT2 == PROT_THREAD)
#define PROT2_BITMAP_WIDTH          16
#define PROT2_BITMAP_HEIGHT         18
#define PROT2_X_POSITION            104
#define PROT2_Y_POSITION            (LIGHT_Y_POSITION + (LIGHT_Y_POSITION / 2))
#endif // PROT1 | PROT2
#endif // PROT_THREAD

static const uint8_t siliconlabsBitmap[] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0x0f, 0xf0, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xcf, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0x01, 0x00, 0x00, 0xc0,
  0xff, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0xff, 0xff, 0x3f,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x1f, 0xfc, 0xff, 0xff, 0xff, 0xff,
  0xf3, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x1f, 0xf8,
  0xff, 0xff, 0xff, 0x7f, 0xfc, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00,
  0xfc, 0xff, 0x1f, 0xf0, 0xff, 0xff, 0xff, 0x1f, 0xff, 0xff, 0x7f, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0x1f, 0xe0, 0xff, 0xff, 0xff, 0xc3,
  0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0x0f, 0xc0,
  0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0xff, 0x07, 0xc0, 0xff, 0xff, 0x1f, 0xf8, 0xff, 0xff, 0x03, 0x00,
  0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0x01, 0xc0, 0xff, 0xff, 0x07, 0xfc,
  0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x7f, 0x00, 0x80,
  0xff, 0xff, 0x01, 0xfe, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xf8, 0x0f, 0x00, 0x80, 0xff, 0x7f, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x3f, 0x80, 0xff,
  0xff, 0xff, 0x00, 0x00, 0xf0, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0xc0,
  0xff, 0x0f, 0x80, 0xff, 0xff, 0xff, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff,
  0x01, 0x00, 0x00, 0xc0, 0xff, 0x03, 0xc0, 0xff, 0xff, 0xff, 0xe0, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0xe0, 0xff, 0x01, 0xc0, 0xff,
  0xff, 0xff, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xe0,
  0xff, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0x01, 0x00, 0xf0, 0x7f, 0x00, 0x80, 0xff, 0xff, 0xff, 0x0f, 0xfc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0xf8, 0x3f, 0x00, 0x80, 0xff,
  0xff, 0xff, 0x3f, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0x0f, 0x00, 0xfc,
  0x1f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xc0, 0xff, 0xff,
  0xff, 0x0f, 0x00, 0xfe, 0x0f, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff,
  0xff, 0x0f, 0xff, 0xff, 0xff, 0x1f, 0x00, 0xff, 0x07, 0x00, 0x00, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xfc, 0xff, 0xff, 0x1f, 0x80, 0xff,
  0x07, 0x00, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xf8, 0xff,
  0xff, 0x1f, 0xc0, 0xff, 0x03, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff,
  0xff, 0x00, 0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0x03, 0x00, 0x00, 0x00,
  0x00, 0xfe, 0xff, 0x3f, 0x00, 0x00, 0xf0, 0xff, 0xff, 0x0f, 0xfc, 0xff,
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff,
  0xff, 0x07, 0xfe, 0xff, 0x01, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xf8, 0xff, 0xff, 0x83, 0xff, 0xff, 0x01, 0x00, 0xc0, 0xff,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xe1, 0xff, 0xff,
  0x03, 0x00, 0xf0, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff,
  0xff, 0xf8, 0xff, 0xff, 0x03, 0x00, 0xf8, 0xff, 0x07, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0x03, 0x00, 0xfe, 0xff,
  0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff,
  0x07, 0x00, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x0f, 0x80, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00,
  0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xc0, 0xff, 0xff,
  0x07, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x3f, 0xc0, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0x00, 0x00, 0x80,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0xff,
  0xff, 0x1f, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

static unsigned char lightOnBitMap[] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfc, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x7f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f,
  0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfc, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x7f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f,
  0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfc, 0xff, 0xff, 0xff,
  0xff, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0x8f, 0xff, 0xff,
  0xff, 0xff, 0xf1, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff,
  0xff, 0x1f, 0xfe, 0x07, 0xe0, 0x7f, 0xf8, 0xff, 0xff, 0x3f, 0xfc, 0x00,
  0x00, 0x3f, 0xfc, 0xff, 0xff, 0x7f, 0x3c, 0xe0, 0x07, 0x3c, 0xfe, 0xff,
  0xff, 0xff, 0x1f, 0xfe, 0x7f, 0xf8, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xff,
  0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xe3, 0xff, 0xff,
  0xff, 0xff, 0xe3, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xff,
  0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xff, 0xff, 0x8f, 0xff, 0xff,
  0xff, 0xff, 0xf8, 0xff, 0xff, 0x1f, 0xff, 0xff, 0xff, 0x7f, 0xfc, 0xff,
  0xff, 0x3f, 0xfe, 0xff, 0xff, 0x7f, 0xfc, 0xff, 0xff, 0x3f, 0xfe, 0xff,
  0xff, 0x7f, 0xfc, 0xff, 0xff, 0x3f, 0xfe, 0xff, 0xff, 0x7f, 0xfe, 0xff,
  0xff, 0x7f, 0xfe, 0xff, 0xff, 0x3f, 0xfe, 0xff, 0xff, 0x7f, 0xfc, 0xff,
  0xff, 0x3f, 0xfe, 0xff, 0xff, 0x7f, 0xfc, 0xff, 0x0f, 0x38, 0xfe, 0xff,
  0xff, 0x7f, 0x1c, 0xf0, 0x0f, 0x38, 0xfe, 0x03, 0xc0, 0x7f, 0x1c, 0xf0,
  0x0f, 0x38, 0xfe, 0x27, 0xe9, 0x7f, 0x1c, 0xf0, 0xff, 0x3f, 0xfe, 0xff,
  0xff, 0x7f, 0xfc, 0xff, 0xff, 0x3f, 0xfe, 0xff, 0xff, 0x7f, 0xfc, 0xff,
  0xff, 0x3f, 0xfe, 0xe7, 0xe7, 0x7f, 0xfc, 0xff, 0xff, 0x7f, 0xfe, 0xef,
  0xf7, 0x7f, 0xfe, 0xff, 0xff, 0x7f, 0xfc, 0xef, 0xf7, 0x3f, 0xfe, 0xff,
  0xff, 0xff, 0xfc, 0xef, 0xf3, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xcf,
  0xf3, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xdf, 0xfb, 0x1f, 0xff, 0xff,
  0xff, 0xff, 0xf1, 0xdf, 0xfb, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xe3, 0x9f,
  0xf9, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xc3, 0x9f, 0xf9, 0xc3, 0xff, 0xff,
  0xff, 0xff, 0xc7, 0x9f, 0xfd, 0xe3, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xbf,
  0xfd, 0xf1, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x3f, 0xfc, 0xf8, 0xff, 0xff,
  0xff, 0xff, 0x3f, 0x3e, 0x7c, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfc,
  0x3f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfc, 0x3f, 0xfe, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,
  0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xf1, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01,
  0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xc0, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x3f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

static unsigned char lightOffBitMap[] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x07, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xe0, 0x07, 0xfc, 0xff, 0xff,
  0xff, 0xff, 0x1f, 0xfe, 0x7f, 0xf8, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xff,
  0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xe3, 0xff, 0xff,
  0xff, 0xff, 0xe3, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xff,
  0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xff, 0xff, 0x8f, 0xff, 0xff,
  0xff, 0xff, 0xf8, 0xff, 0xff, 0x1f, 0xff, 0xff, 0xff, 0x7f, 0xfc, 0xff,
  0xff, 0x3f, 0xfe, 0xff, 0xff, 0x7f, 0xfc, 0xff, 0xff, 0x3f, 0xfe, 0xff,
  0xff, 0x7f, 0xfc, 0xff, 0xff, 0x3f, 0xfe, 0xff, 0xff, 0x7f, 0xfe, 0xff,
  0xff, 0x7f, 0xfe, 0xff, 0xff, 0x3f, 0xfe, 0xff, 0xff, 0x7f, 0xfc, 0xff,
  0xff, 0x3f, 0xfe, 0xff, 0xff, 0x7f, 0xfc, 0xff, 0xff, 0x3f, 0xfe, 0xff,
  0xff, 0x7f, 0xfc, 0xff, 0xff, 0x3f, 0xfe, 0xff, 0xff, 0x7f, 0xfc, 0xff,
  0xff, 0x3f, 0xfe, 0xff, 0xff, 0x7f, 0xfc, 0xff, 0xff, 0x3f, 0xfe, 0xff,
  0xff, 0x7f, 0xfc, 0xff, 0xff, 0x3f, 0xfe, 0xff, 0xff, 0x7f, 0xfc, 0xff,
  0xff, 0x3f, 0xfe, 0xff, 0xff, 0x7f, 0xfc, 0xff, 0xff, 0x7f, 0xfe, 0xff,
  0xff, 0x7f, 0xfe, 0xff, 0xff, 0x7f, 0xfc, 0xff, 0xff, 0x3f, 0xfe, 0xff,
  0xff, 0xff, 0xfc, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff,
  0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0x1f, 0xff, 0xff,
  0xff, 0xff, 0xf1, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xff,
  0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xc3, 0xff, 0xff,
  0xff, 0xff, 0xc7, 0xff, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff,
  0xff, 0xf1, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xff, 0xff, 0xf8, 0xff, 0xff,
  0xff, 0xff, 0x3f, 0xfe, 0x7f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfc,
  0x3f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfc, 0x3f, 0xfe, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,
  0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xf1, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01,
  0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xc0, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x3f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

#ifdef PROT_ZIGBEE
#if (PROT1 == PROT_ZIGBEE)
#define PROT1_BITMAP      (zigbeeBitmap)
#define PROT1_BITMAP_CONN (zigbeeConnectBitmap)
#elif (PROT2 == PROT_ZIGBEE)
#define PROT2_BITMAP      (zigbeeBitmap)
#define PROT2_BITMAP_CONN (zigbeeConnectedBitmap)
#endif // PROT1 | PROT2
static unsigned char zigbeeBitmap[] = {
  0x3f, 0xfc, 0x07, 0xf0, 0xff, 0xc7, 0xff, 0x9f, 0x01, 0x9c, 0x00, 0x0e,
  0x00, 0x07, 0x80, 0x03, 0xc0, 0x01, 0xe0, 0x00, 0x70, 0x80, 0x39, 0x80,
  0xf9, 0xff, 0xfb, 0xff, 0x07, 0xe0, 0x1f, 0xfc
};

static unsigned char zigbeeConnectedBitmap[] = {
  0x3f, 0xfc, 0x07, 0xf0, 0xff, 0xc7, 0xff, 0x9f, 0x01, 0x9c, 0x00, 0x0e,
  0x00, 0x07, 0x80, 0x03, 0xc0, 0x01, 0xe0, 0x00, 0x70, 0x80, 0x39, 0x80,
  0xf9, 0xff, 0xfb, 0xff, 0x07, 0xe0, 0x1f, 0xfc
};
#endif // PROT_ZIGBEE

#ifdef PROT_RAIL
#if (PROT1 == PROT_RAIL)
#define PROT1_BITMAP      (railBitmap)
#define PROT1_BITMAP_CONN (railConnectedBitmap)
#elif (PROT2 == PROT_RAIL)
#define PROT2_BITMAP      (railBitmap)
#define PROT2_BITMAP_CONN (railConnectedBitmap)
#endif // PROT1 | PROT2
static unsigned char railBitmap[] = {
  0xFF, 0xE3, 0xFF, 0xDF, 0xFF, 0xB3, 0xFF, 0x6F, 0xFF, 0x5B, 0x07, 0x57,
  0xDB, 0xFE, 0x89, 0xFC, 0x56, 0xFB, 0x56, 0xFB, 0x00, 0xF8, 0x56, 0xFB,
  0x56, 0xFB, 0x89, 0xFC, 0xDB, 0xFE, 0x07, 0xFF
};

static unsigned char railConnectedBitmap[] = {
  0xFF, 0xE3, 0xFF, 0xDF, 0xFF, 0xB3, 0xFF, 0x6F, 0xFF, 0x5B, 0x07, 0x57,
  0xDB, 0xFE, 0x89, 0xFC, 0x56, 0xFB, 0x56, 0xFB, 0x00, 0xF8, 0x56, 0xFB,
  0x56, 0xFB, 0x89, 0xFC, 0xDB, 0xFE, 0x07, 0xFF
};
#endif // PROT_RAIL

#ifdef PROT_CONNECT
#if (PROT1 == PROT_CONNECT)
#define PROT1_BITMAP      (connectBitmap)
#define PROT1_BITMAP_CONN (connectConnectedBitmap)
#elif (PROT2 == PROT_CONNECT)
#define PROT2_BITMAP      (connectBitmap)
#define PROT2_BITMAP_CONN (connectConnectedBitmap)
#endif // PROT1 | PROT2
static unsigned char connectBitmap[] = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xEF, 0xDB, 0xDB, 0xED, 0xB7,
  0xB5, 0xAD, 0x55, 0xAA, 0x55, 0xAA, 0xB5, 0xAD, 0xED, 0xB7, 0xDB, 0xDB,
  0xF7, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

static unsigned char connectConnectedBitmap[] = {
  0x1F, 0xF8, 0x07, 0xE0, 0x03, 0xC0, 0x21, 0x84, 0x11, 0x88, 0x48, 0x12,
  0x28, 0x14, 0xA8, 0x15, 0xA8, 0x15, 0x28, 0x14, 0x48, 0x12, 0x11, 0x88,
  0x21, 0x84, 0x03, 0xC0, 0x07, 0xE0, 0x1F, 0xF8
};
#endif // PROT_CONNECT

#ifdef PROT_BLUETOOTH
#if (PROT1 == PROT_BLUETOOTH)
#define PROT1_BITMAP      (bluetoothBitmap)
#define PROT1_BITMAP_CONN (bluetoothConnectedBitmap)
#elif (PROT2 == PROT_BLUETOOTH)
#define PROT2_BITMAP      (bluetoothBitmap)
#define PROT2_BITMAP_CONN (bluetoothConnectedBitmap)
#endif // PROT1 | PROT2
static unsigned char bluetoothBitmap[] = {
  0xff, 0xff, 0x7f, 0xff, 0x7f, 0xfe, 0x7f, 0xf8, 0x7f, 0xf2, 0x73, 0xe6,
  0x67, 0xf2, 0x4f, 0xf8, 0x1f, 0xfe, 0x1f, 0xfe, 0x4f, 0xf8, 0x67, 0xf2,
  0x73, 0xe6, 0x7f, 0xf2, 0x7f, 0xf8, 0x7f, 0xfe, 0x7f, 0xff, 0xff, 0xff
};

static unsigned char bluetoothConnectedBitmap[] = {
  0xff, 0xff, 0x7f, 0xff, 0x7f, 0xfe, 0x7f, 0xf8, 0x7f, 0xf2, 0x73, 0xe6,
  0x67, 0xf2, 0x4d, 0xd8, 0x18, 0x8e, 0x18, 0x8e, 0x4d, 0xd8, 0x67, 0xf2,
  0x73, 0xe6, 0x7f, 0xf2, 0x7f, 0xf8, 0x7f, 0xfe, 0x7f, 0xff, 0xff, 0xff
};
#endif // PROT_BLUETOOTH

#ifdef PROT_THREAD
#if (PROT1 == PROT_THREAD)
#define PROT1_BITMAP      (threadBitmap)
#define PROT1_BITMAP_CONN (threadBitmap)
#elif (PROT2 == PROT_THREAD)
#define PROT2_BITMAP      (threadBitmap)
#define PROT2_BITMAP_CONN (threadBitmap)
#endif // PROT1 | PROT2
static unsigned char threadBitmap[] = {
  0x1F, 0xF8, 0x07, 0xE0, 0x03, 0xCE, 0x01, 0x9F, 0x01, 0xB3, 0x00, 0x33,
  0xF0, 0x3F, 0xF8, 0x1F, 0x0C, 0x03, 0x0C, 0x03, 0x18, 0x03, 0x11, 0x83,
  0x01, 0x83, 0x03, 0xC3, 0x07, 0xE3, 0x1F, 0xFB, 0x7f, 0xff, 0xff, 0xff
};
#endif // PROT_THREAD
#endif // __DMP_BITMAPS_H__
