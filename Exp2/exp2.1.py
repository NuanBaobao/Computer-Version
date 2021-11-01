# import library
import numpy as np
import cv2 as cv
import math

# 读入图像
image = cv.imread("exp2.jpg")
# 获取图像的行数、列数、通道数
width, height, channels = image.shape

# 创建一个空图像
outputImage = np.zeros(image.shape, dtype=image.dtype)
print(outputImage.shape)


def BilinearInterpolation(oldX, oldY):
    # 双线性插值
    global image, outputImage
    dx = oldX - np.uint16(oldX)
    dy = oldY - np.uint16(oldY)

    oldX = np.uint16(oldX)
    oldY = np.uint16(oldY)
    # 第一次水平插值
    h1 = (1 - dx) * image[oldX][oldY] + dx * image[oldX + 1][oldY]
    # 第二次水平插值
    h2 = (1 - dx) * image[oldX][oldY + 1] + dx * image[oldX + 1][oldY + 1]
    # 垂直插值
    outputImage[i][j] = h1 + dy * (h2 - h1)


# 图像变形
for i in range(1, width - 1):
    for j in range(1, height - 1):
        # 中心归一化坐标
        tempX = (i - 0.5 * width) / (0.5 * width)
        tempY = (j - 0.5 * height) / (0.5 * height)
        # print("tempX=",tempX,"tempY=",tempY)
        # 获取r和theta
        r = math.sqrt(tempX ** 2 + tempY ** 2) 
        theta = (1 - r) ** 2
        # print("theta=",theta)
        if r >= 1:
            x = tempX
            y = tempY
        else:
            x = math.cos(theta) * tempX - math.sin(theta) * tempY
            y = math.sin(theta) * tempX + math.cos(theta) * tempY
        # 还原
        oldX = (x + 1) * 0.5 * width
        oldY = (y + 1) * 0.5 * height
        #print("oldX = ",oldX,"oldY = ",oldY)

        # 双线性插值
        BilinearInterpolation(oldX,oldY)

cv.imshow("Original Image", image)
cv.imshow("Vertical wave", outputImage)
cv.waitKey()
