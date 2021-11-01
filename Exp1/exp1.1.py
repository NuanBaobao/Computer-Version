#引入opencv模块
import cv2 as cv
#引入numpy模块
import numpy as np
#引入sys模块
import sys
 
#对比度范围：0 ~ 0.3
alpha = 0.3
#亮度范围0 ~ 100
beta = 100
img = cv.imread('F:/ComputerVision/Exp1/exp1.1/code1.png')
print(img)
img2 = cv.imread('F:/ComputerVision/Exp1/exp1.1/code1.png')
 
def updateAlpha(x):
    global alpha, img, img2
    #获取当前滑块的位置
    alpha = cv.getTrackbarPos('Alpha', 'image')#trackbarname：轨迹条的名字,winname：轨迹条所在窗口的名字
    alpha = alpha * 0.01
    #img = np.uint8(np.clip((alpha * img2 + beta), 0, 255))
    
    #将img的所有数字使用sigmod等比例的放大或缩小到0–255范围的数组中
    img = cv.normalize(1./(1. + np.exp(-alpha)) * img2 + beta,img, 0, 255, cv.NORM_MINMAX)
    img = np.array(img,dtype='uint8')
 
 
def updateBeta(x):
    global beta, img, img2
    #获取当前滑块的位置
    beta = cv.getTrackbarPos('Beta', 'image')
    #img = np.uint8(np.clip((alpha * img2 + beta), 0, 255))
    
    #将img的所有数字使用sigmod等比例的放大或缩小到0–255范围的数组中
    img = cv.normalize(1./(1. + np.exp(-alpha)) * img2 + beta,img, 0, 255, cv.NORM_MINMAX)
    img = np.array(img,dtype='uint8')
    
 
 
def img_test():
    global beta, img, img2
    #判断是否读取成功
    if img is None:
        print("Could not read the image,may be path error")
        return
 
    # 创建窗口
    cv.namedWindow('image',cv.WINDOW_NORMAL)
    cv.createTrackbar('Alpha', 'image', 0, 300, updateAlpha)
    cv.createTrackbar('Beta', 'image', 0, 255, updateBeta)
    cv.setTrackbarPos('Alpha', 'image', 100)
    cv.setTrackbarPos('Beta', 'image', 10)
    while (True):
        cv.imshow('image', img)
        if cv.waitKey(1) == ord('q'):
            break
    cv.destroyAllWindows()
 
if __name__ == '__main__':
    sys.exit(img_test() or 0)