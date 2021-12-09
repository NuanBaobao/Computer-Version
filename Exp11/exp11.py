# -*- coding: utf-8 -*-

import cv2

def sift(filename):
    img = cv2.imread(filename)  # 读取文件
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)  # 转化为灰度图
    sift = cv2.xfeatures2d_SIFT.create()
    keyPoint, descriptor = sift.detectAndCompute(img, None)  # 特征提取得到关键点以及对应的描述符（特征向量）

    return img, keyPoint, descriptor


def match(filename1, filename2):
    img1, kp1, des1 = sift(filename1)
    img2, kp2, des2 = sift(filename2)
    bf = cv2.BFMatcher(cv2.NORM_L2, crossCheck=True)  # sift的normType应该使用NORM_L2或者NORM_L1

    matches = bf.match(des1, des2)
    matches = sorted(matches, key=lambda x: x.distance)
    knnMatches = bf.knnMatch(des1, des2, k=1)  # drawMatchesKnn

    print('Sift size of keyPoint: %d, Number of points after matching: %d' % (len(des1), len(matches)))
    img = cv2.drawMatches(img1, kp1, img2, kp2, matches[:50], img2, flags=2)
    cv2.imshow("Sift_Image", img)
    


def main():
    filename = 'r2d2-master/imgs/doraemon1.jpg'
    img = cv2.imread(filename)
    cv2.imshow("Original image", img)

    img, key, des = sift(filename)
    img = cv2.drawKeypoints(img, key, None, flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
    print("Number of points extracted by sift: %d, size of des: %d" % (len(des), len(des[0])))
    cv2.imshow("Sift_Keypoints", img)
   
    match('r2d2-master/imgs/doraemon1.jpg', 'r2d2-master/imgs/doraemon2.jpg')
    cv2.waitKey()
    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()
