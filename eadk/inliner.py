#!/usr/bin/env python3
import argparse
import lz4.block
import png


def alpha_blending(intensity, alpha):
    intensity_double = intensity / 255.0
    # Assume a white background (1.0, 1.0, 1.0) in the blending
    intensity_double = intensity_double * alpha + (1.0 - alpha) * 1.0
    return int(intensity_double * 255.0)


def rgba8882rgb565(red, green, blue, alpha):
    alpha = alpha/255.0
    r, g, b = (alpha_blending(color, alpha) for color in (red, green, blue))
    return (r >> 3) << 11 | (g >> 2) << 5 | (b >> 3)


def generate_linker_script(png_file, linker_script_file_name):
    png_reader = png.Reader(filename = png_file)
    width,height,data,info = png_reader.asRGBA8()

    # Convert RGBA888 to RGB565
    dataRGB565 = []
    for row in data:
        for i in range(0, len(row), 4):
            r, g, b, a = row[i:i+4]
            dataRGB565.extend(rgba8882rgb565(r, g, b, a).to_bytes(2, 'little'))

    # Compress data
    compressed_data = lz4.block.compress(bytes(dataRGB565),
                                         compression=12,
                                         mode='high_compression',
                                         store_size=False)
    compressed_data_len = len(compressed_data)

    # Generate header file
    with open(linker_script_file_name, "w") as linker_script:
        linker_script.write("/* This file is auto-generated by inliner.py. Do not edit manually.\n"
                            + "/* Compressed "
                            + str(width*height)
                            + " 16-bit pixels into "
                            + str(compressed_data_len)
                            + " bytes ("
                            + "%.2f"%(100.0*(1.0-compressed_data_len/len(dataRGB565)))
                            + "% compression ratio) */\n\n")
        
        linker_script.write("_eadk_app_icon_start = .;\n")
        for b in compressed_data:
            linker_script.write(f"BYTE({hex(b)});\n")
        linker_script.write("_eadk_app_icon_end = .;\n")


parser = argparse.ArgumentParser(description=("Extract data from png, inline"
                                              "them in linker script as LZ4-compressed"
                                              "RGB565 data."))
parser.add_argument('png', metavar='icon.png', help='input PNG file')
parser.add_argument('ld', metavar='script.ld', help='output linker script')

args = parser.parse_args()
generate_linker_script(args.png, args.ld)
