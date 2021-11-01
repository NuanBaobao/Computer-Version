import cv2

capture = cv2.VideoCapture('F:\\计算机视觉\\Exp4\\exp4.2.mp4')  # 打开摄像头读取视频信息（无声音）
capture.read()
success, frame = capture.read()  # #打开电脑相机读取视频信息（没有读取到图片，截取到一帧的图片）

es = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (9, 4))
background = None

while success:
    if background is None:
        background = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        background = cv2.GaussianBlur(background, (21, 21), 0)
        # 第一次循环时，background是空的，所以将第一针作为背景
        # 将背景灰度处理，平滑处理之后赋给background
        continue

    # 第二次循环开始，background已经有了，将第二帧开始的图片灰度化 + 平滑处理
    # 减小光照 震动等原因产生的噪声影响
    gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gray_frame = cv2.GaussianBlur(gray_frame, (21, 21), 0)

    diff = cv2.absdiff(background, gray_frame)  # 背景与帧做插分操作获取差分图
    ret, binary = cv2.threshold(diff, 25, 255, cv2.THRESH_BINARY)  # 通过二值化从多值的数字图像直接提取目标图像
    diff = binary  # 阈值得到黑白图
    diff = cv2.dilate(diff, es, iterations=2)  # 膨胀运算,用椭圆框来膨胀，迭代次数是2

    # 搜索轮廓 cents是轮廓 hierarchy是每条轮廓的属性
    contours, hierarchy = cv2.findContours(diff.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    for c in contours:
        if cv2.contourArea(c) < 1500:
            continue  # 如果轮廓太小了，以面积看，就不显示
        (x, y, w, h) = cv2.boundingRect(c)
        cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 255, 0), 2)

    # frame = cv2.flip(frame, 1)  # 修改视角差异（镜像变换）
    cv2.imshow('contours', frame)  # #显示每一帧的图片
    # 关闭窗口指令
    c = cv2.waitKey(20)  # #显示50ms，然后继续执行程序
    if c == 27:  # Esc的ASCII码为27
        break

    success, frame = capture.read()

cv2.destroyAllWindows()
capture.release()
