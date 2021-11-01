import cv2
import math
import numpy as np

#哈哈镜放大效果实现
def enlarge_effect(image):
    # 获取图像的行数、列数、通道数
    width, height, channels = image.shape
    new_img = np.zeros(image.shape, dtype=image.dtype)
    print(new_img.shape)
    for i in range(1,width-2):
        for j in range(1,height-2):
            # 中心归一化坐标
            tempX = (i - 0.5 * width) / (0.5 * width)
            tempY = (j - 0.5 * height) / (0.5 * height)
            # print("tempX=",tempX,"tempY=",tempY)
            #图片中心点
            #cx = width / 2
            #cy = height / 2
            radius = 0.8#直径
            #r = math.floor(radius / 2)
            #图像上任意一点到中心点的相对坐标
            #tx = i - cx
            #ty = j - cy
            #图像变换的半径为radius
            #distance = tx**2 + ty**2
            #if distance < radius**2:
            tempX = (tempX/2) * (math.sqrt(tempX**2 + tempY**2)/radius)
            tempY = (tempY/2) * (math.sqrt(tempX**2 + tempY**2)/radius)
            # 还原
            oldX = (tempX + 1) * 0.5 * width
            oldY = (tempY + 1) * 0.5 * height
            
            
                #print("oldX = ",oldX,"oldY = ",oldY)

            # 双线性插值
            dx = oldX - np.uint16(oldX)
            dy = oldY - np.uint16(oldY)

            oldX = np.uint16(oldY)
            oldY = np.uint16(oldY)

            if oldX < 0:
                oldX = 0
            if oldX >= width - 1:
                oldX = width -2
            if oldY < 0:
                oldY = 0
            if oldY >= height - 1:
                oldY = height - 2
                #if x < width and y < height:
            # 第一次水平插值
            h1 = (1 - dx) * image[oldX][oldY] + dx * image[oldX + 1][oldY]
            # 第二次水平插值
            h2 = (1 - dx) * image[oldX][oldY + 1] + dx * image[oldX + 1][oldY + 1]
            # 垂直插值
            new_img[i][j] = h1 + dy * (h2 - h1)
    return new_img


if __name__ == "__main__":
    cap = cv2.VideoCapture(0)
    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    out = cv2.VideoWriter('testwrite.mp4',fourcc, 20.0, (1920,1080),True)
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

