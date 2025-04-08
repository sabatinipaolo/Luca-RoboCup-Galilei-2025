import sensor, image, time, math, pyb
from pyb import UART

uart = UART(3,19200)

# ROLLER
# CAMPO SX
# Y: (57, 92, 4, 28, 27, 127)
# B: (44, 74, -17, 0, -54, -21)


# RICK
# CAMPO SX
# Y: (83, 100, -26, 31, 24, 127)
# B: (46, 76, -19, 2, -53, -17)

# ROCK
# Y: (66, 100, -15, 3, 17, 127)
# B: (39, 62, -8, 24, -128, -19)

# ROLL
# Y: (64, 100, -23, 21, 17, 127)
# B: (39, 62, -8, 24, -128, -19)

thresholds = [(79, 96, -15, 16, 27, 66),   #Yellow
              (47, 56, -8, 15, -44, -24)] #Blue

#cx = 160-blob.cx()
#cy = 120-blob.cy()

camcx = 178
camcy = 130

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()

while(True):
    clock.tick()

    yellowFound = False
    blueFound = False

    img = sensor.snapshot()

    blobYellow = [(0, 0, 0)]
    blobBlue = [(0, 0, 0)]

    for blob in img.find_blobs(thresholds, pixels_threshold=200, area_threshold=200, merge=True):
        img.draw_rectangle(blob.rect(), (255, 0, 0))
        img.draw_cross(blob.cx(),blob.cy())
        img.draw_cross(camcx,camcy);
        img.draw_line(camcx,camcy,blob.cx(),blob.cy())
        if (blob.code() == 1):
            blobYellow += [(blob.area(), blob.cx(), blob.cy())]
            yellowFound = True

        if (blob.code() == 2):
            blobBlue += [(blob.area(), blob.cx(), blob.cy())]
            blueFound = True

    blobYellow.sort(reverse = True)
    blobBlue.sort(reverse = True)

    if (yellowFound):
        area = blobYellow[0][0]
        cx = camcx-blobYellow[0][1]
        cy = camcy-blobYellow[0][2]
        ang = int((math.atan2(cx, cy) * 180 / math.pi) - 90)
        if (ang < 0):
            ang += 360
        data = "Y" + str(ang) + "-" + str(area) + "y"
    else:
        data = "Y999-999y"

    uart.write(data)
    print(data)

    if (blueFound):
        area = blobBlue[0][0]
        cx = 160-blobBlue[0][1]
        cy = 120-blobBlue[0][2]
        ang = int((math.atan2(cx, cy) * 180 / math.pi) - 90)
        if (ang < 0):
            ang += 360
        data = "B" + str(ang) + "-" + str(area) + "b"
    else:
        data = "B999-999b"

    uart.write(data)
    print(data)



