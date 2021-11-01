import cv2
import math
import numpy as np

#哈哈镜放大效果实现
def enlarge_effect(image):
    # 获取图像的行数、列数、通道数
    width, height, channels = image.shape
    new_img = np.zeros(image.shape, dtype=image.dtype)
    for i in range(1,width-1):
        for j in range(1,height-1):
            # 中心归一化坐标
            #tempX = (i - 0.5 * width) / (0.5 * width)
            #tempY = (j - 0.5 * height) / (0.5 * height)
            # print("tempX=",tempX,"tempY=",tempY)
            #图片中心点
            cx = width / 2
            cy = height / 2
            radius = 200#直径
            r = math.floor(radius / 2)
            #图像上任意一点到中心点的相对坐标
            tx = i - cx
            ty = j - cy
            #图像变换的半径为radius
            distance = tx**2 + ty**2
            if distance < radius**2:
                x = (tx / 2.0) * (math.sqrt(distance) / r) + cx
                y = (ty / 2.0) * (math.sqrt(distance) / r) + cy

                # 还原
                #oldX = (x + 1) * 0.5 * width
                #oldY = (y + 1) * 0.5 * height
                #print("oldX = ",oldX,"oldY = ",oldY)

                # 双线性插值
                dx = x - np.uint16(x)
                dy = y - np.uint16(y)

                x = np.uint16(x)
                y = np.uint16(y)
                if x < width and y < height:
                    # 第一次水平插值
                    h1 = (1 - dx) * image[x][y] + dx * image[x + 1][y]
                    # 第二次水平插值
                    h2 = (1 - dx) * image[x][y + 1] + dx * image[x + 1][y + 1]
                    # 垂直插值
                    new_img[i][j] = h1 + dy * (h2 - h1)
    return new_img


if __name__ == "__main__":
    cap = cv2.VideoCapture(0)
    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    out = cv2.VideoWriter('testwrite.mp4',fourcc, 10.0, (640,480),True)
    while (cap.isOpened()):
        ret, frame = cap.read()
        frame=enlarge_effect(frame)
        cv2.imshow('video', frame)
        out.write(frame)
        c = cv2.waitKey(1)
        if c == 'q':
            break
    cap.release()
    cv2.destroyAllWindows()

