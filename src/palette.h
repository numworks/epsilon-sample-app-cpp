#ifndef PALETTE_H
#define PALETTE_H

static constexpr eadk_color rgb24(uint32_t rgb) {
  return ((rgb&0xF80000)>>8)|((rgb&0x00FC00)>>5)|((rgb&0x0000F8)>>3);
}

constexpr static eadk_color Black = rgb24(0x000000);
constexpr static eadk_color Green = rgb24(0x28F52E);
constexpr static eadk_color Grey = rgb24(0xF7F7F7);
constexpr static eadk_color LightBlue = rgb24(0XC9DBFD);
constexpr static eadk_color Orange = rgb24(0xD55422);
constexpr static eadk_color Pink = rgb24(0xCB6E79);
constexpr static eadk_color Red = rgb24(0xFF0000);
constexpr static eadk_color White = rgb24(0xFFFFFF);
constexpr static eadk_color Yellow = rgb24(0xF3B443);

#endif
