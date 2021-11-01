import cv2

img = cv2.imread("cat.png")
# print(img.shape)
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)  # BGR 格式数据格式在 0~255
# print("gray = ", gray.shape)
ret, binary = cv2.threshold(gray, 128, 255, cv2.THRESH_BINARY)  # 通过二值化从多值的数字图像直接提取目标图像
# print("ret = ", ret, "binary = ", binary)

# cv2.findContours()函数返回两个值，一个是轮廓本身，还有一个是每条轮廓对应的属性。
contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)  # 查找检测物体的轮廓

cv2.drawContours(img, contours, -1, (0, 0, 255), 3)

cv2.imshow("img", img)
cv2.waitKey(0)
