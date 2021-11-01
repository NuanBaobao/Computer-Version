import cv2

# 调用摄像头
cameraCapture = cv2.VideoCapture(0)
cv2.namedWindow('test_camera')
success, frame = cameraCapture.read()
last_frame = None
while success:
    if last_frame is None:
        last_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        continue

    gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    diff = cv2.absdiff(last_frame, gray_frame)  # 背景与帧做插分操作获取差分图

    # 搜索轮廓 cents是轮廓 hierarchy是每条轮廓的属性
    contours, hierarchy = cv2.findContours(diff.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    for c in contours:
        if cv2.contourArea(c) < 1500:
            continue  # 如果轮廓太小了，以面积看，就不显示
        (x, y, w, h) = cv2.boundingRect(c)
        cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 255, 0), 2)

    if cv2.waitKey(1) == 27:  # Esc的ASCII码为27
        break
    cv2.imshow('test_camera', frame)
    # last_frame = gray_frame
    success, frame = cameraCapture.read()

cv2.destroyAllWindows()
cameraCapture.release()
