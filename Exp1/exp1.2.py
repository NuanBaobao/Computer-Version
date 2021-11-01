import cv2
import numpy as np
import matplotlib.pyplot as plt
import sys
 
img1 = cv2.imread('F:/ComputerVision/bgs-data/02_bg.jpg')
img2 = cv2.imread('F:/ComputerVision/bgs-data/02.jpg')
size = 512
#首先非局部平均去噪，使用彩色图像
img1 = cv2.fastNlMeansDenoisingColored(img1,None,10,10,7,21)
img2 = cv2.fastNlMeansDenoisingColored(img2,None,10,10,7,21)
#h : 决定过滤器强度。h 值高可以很好的去除噪声,但也会把图像的细节抹去
#hForColorComponents : 与 h 相同,但使用与彩色图像
#templateWindowSize : 奇数
#searchWindowSize : 奇数

#调整大小
img1 = cv2.resize(img1, (size, size)) 
img2 = cv2.resize(img2, (size, size)) 
 
 
#利用Sobel算子进行图像梯度计算
x = cv2.Sobel(img1,cv2.CV_16S,1,0)
y = cv2.Sobel(img1,cv2.CV_16S,0,1)
absX = cv2.convertScaleAbs(x)  
absY = cv2.convertScaleAbs(y)
#图片融合
img1 = cv2.addWeighted(absX,0.5,absY,0.5,0)
 
x = cv2.Sobel(img2,cv2.CV_16S,1,0)
y = cv2.Sobel(img2,cv2.CV_16S,0,1)
#使用了函数cv2.convertScaleAbs()将图像深度为CV_64F的梯度图像重新转化为CV_8U,这是由于函数cv2.imshow()的默认显示为8位无符号数，即[0,255]。
absX = cv2.convertScaleAbs(x)  
absY = cv2.convertScaleAbs(y)
#图片融合
img2 = cv2.addWeighted(absX,0.5,absY,0.5,0)
 
print('img1', img1.shape[1],img1.shape[0])
print('img2', img2.shape[1],img2.shape[0])
 
err = cv2.absdiff(img1,img2) 
 
fig = plt.figure('result')
plt.axis('off')  #关闭坐标轴
 
plt.subplot(2,2,1)     #将窗口分为两行两列四个子图，则可显示四幅图片
plt.title('img1')   #第一幅图片标题
plt.imshow(img1)  
 
plt.subplot(2,2,2)     
plt.title('img2')   
plt.imshow(img2)  
 
plt.subplot(2,2,4)     
plt.title('diff')   
plt.imshow(err)
 
fig.tight_layout()#调整整体空白
plt.subplots_adjust(wspace =0)#调整子图间距
plt.show()   #显示  