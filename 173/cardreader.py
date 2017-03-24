import PIL.Image
import PIL.JpegImagePlugin
import os

import sys

OFFSET_X = 141
OFFSET_Y = 131
BLOCK_WIDTH = 52
BLOCK_HEIGHT = 150


def is_slot(img, x, y):
    base_x = OFFSET_X + (x - 1) * BLOCK_WIDTH
    base_y = OFFSET_Y + (y + 2) * BLOCK_HEIGHT

    count = 0
    for i in range(0, 20):
        check_x = base_x + i
        check_y = base_y + i
        color = img.getpixel((check_x, check_y))
        if color[0] ** 2 + color[1] ** 2 + color[2] ** 2 < 30000:
            # print("Black: %d,%d" % (check_x, check_y))
            count += 1
            # else:
            #    print("Color: (%d,%d,%d) %d,%d" % (color[0], color[1], color[2], check_x, check_y))

    # print("valid:%s, count: %d, point:(%d,%d), xy: (%d,%d), rgb: %s" % (
    #    count > 15, count,
    #    x, y,
    #    base_x, base_y,
    #    img.getpixel((base_x + 1, base_y + 1))
    # ))
    # for ix in range(0, BLOCK_WIDTH):
    #    for iy in range(0, BLOCK_HEIGHT):
    #        img.putpixel((base_x + ix, base_y + iy), (255, 0, 0))
    #
    # img.save("tmp.jpg")
    # sys.exit(1)
    return count >= 5


to_char = {
    "X": "&",
    "Y": "-",
    "0": "0",
    "1": "1",
    "2": "2",
    "3": "3",
    "4": "4",
    "5": "5",
    "6": "6",
    "7": "7",
    "8": "8",
    "9": "9",
    "X1": "A",
    "X2": "B",
    "X3": "C",
    "X4": "D",
    "X5": "E",
    "X6": "F",
    "X7": "G",
    "X8": "H",
    "X9": "I",
    "Y1": "J",
    "Y2": "K",
    "Y3": "L",
    "Y4": "M",
    "Y5": "N",
    "Y6": "O",
    "Y7": "P",
    "Y8": "Q",
    "Y9": "R",
    "01": "/",
    "02": "S",
    "03": "T",
    "04": "U",
    "05": "V",
    "06": "W",
    "07": "X",
    "08": "Y",
    "09": "Z",
    "28": ":",
    "38": "#",
    "48": "@",
    "58": "'",
    "68": "=",
    "78": "\"",
    "X28": "¢",
    "X38": ".",
    "X48": "<",
    "X58": "(",
    "X68": "+",
    "X78": "|",
    "Y28": "!",
    "Y38": "$",
    "Y48": "*",
    "Y58": ")",
    "Y68": ";",
    "Y78": "¬",
    "028": " ",
    "038": ",",
    "048": "%",
    "058": "_",
    "068": ">",
    "078": "?",
}


def translate(seq):
    if len(seq) == 0:
        return " "
    code = ""
    for i in seq:
        if i == -2:
            code += "X"
        elif i == -1:
            code += "Y"
        else:
            code += str(i)

    return to_char[code]


def parse(filename):
    #print(filename)
    img = PIL.Image.open(filename)
    img.load()
    text = ""
    for x in range(1, 81):
        seq = []
        for y in range(-2, 10):
            if is_slot(img, x, y):
                seq.append(y)

        text += translate(seq)
    print(text)


# x -> 122, y -> 73

all_files = [
    "programming.jpg",
    "punch.jpg",
    "yolo.jpg",
    "my.jpg",
    "card.jpg",
    "grandpa.jpg",
]
for file in all_files:
    parse(file)
