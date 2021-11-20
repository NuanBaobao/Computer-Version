# Computer-Version
## Author ZhangJinhua
Artificial Intelligence Class of 2019

School of Computer Science and Technology

Shandong University

### Exp 1 (2021.9.17 -- 2021.9.24)
#### 对比度调整

>设计一个Sigmoid函数，实现对图像的对比度调节
>
>使用opencv窗口系统的哦slider控件交互改变Sigmoid函数的参数，实现不同的对比度调整

#### 背景相减

>对图像I和对应的背景图B，基于背景相减检测I中的前景区域，并输出前景的mask
>
>分析可能产生误检的情况，设法对背景相减做出改进

### Exp 2 (2021.9.24 -- 2021.9.30)
#### 图像变形
>记 [x’, y’]=f([x, y]) 为像素坐标的一个映射，实现 f 所表示的图像形变，并采用双线性插值进行重采样。f 的逆映射见ppt
>
>[x’, y’]和[x, y]都是中心归一化坐标，请先进行转换
>
>仿照实验2.1，自己设计变换函数，对输入视频进行变换，生成哈哈镜的效果。
>
>采用cv::VideoCapture读取摄像头视频，并进行实时处理和显示结果。
>
>优化代码执行效率，改善实时性（不要忘了打开编译优化，vc请用release模式编译）。
### Exp 3 (2021.10.4 -- 2021.10.12)
#### 高斯滤波
>通过调整高斯函数的标准差(sigma)来控制平滑程度
>
>滤波窗口大小取[6*sigma-1], [ ]表示取整
>
>利用二维高斯函数的行列可分性进行加速

#### 快速均值滤波
> 滤波窗口大小通过参数来指定
> 
>采用积分图进行加速，实现与滤波窗口大小无关的效率
>
>与opencv的boxFilter函数比较计算速度，分析差异
### Exp 4 (2021.10.13 -- 2021.10.19)
（目标跟踪与图像分割可二选一）

#### 基于直方图的目标跟踪
>实现基于直方图的目标跟踪：已知第t帧目标的包围矩形，计算第t+1帧目标的矩形区域。
>
>选择适当的测试视频进行测试：给定第1帧目标的矩形框，计算其它帧中的目标区域。
>
>基于颜色分布的交互图像分割
>
>基于由用户交互笔刷标记的前、背景像素（图中黄绿区域），计算前、背景的颜色分布，并用于估计未标记像素属于前景和背景的概率。
>
>颜色分布可以用直方图或者高斯混合模型（GMM）表示。如果用GMM，可以基于OpenCV的实现估计GMM参数。
### Exp 5 (2021.10.22 -- 2021.10.26)
#### 连通域
>实现一个8连通的快速连通域算法，并基于该算法对测试图像进行以下处理：
>>计算白色连通区域的个数。
>>
>>删除较小的白色连通域，只保留最大的一个。
#### 距离变换
>了解OpenCV的距离变换函数distanceTransform。
>
>使用合适的测试图像进行测试，将距离场可视化输出。
### Exp 6 (2021.10.29 -- 2021.11.2)
#### 霍夫变换
>实现基于霍夫变换的图像圆检测。

>边缘检测可以用opencv的canny函数。

>尝试对其准确率和效率进行优化实现。

### Exp7 (2021.11.5 -- 2021.11.10)
#### 实验7.1  Harris角点检测
- 实现Harris角点检测算法，并与OpenCV的cornerHarris函数的结果和计算速度进行比较。
[参考链接](https://zhuanlan.zhihu.com/p/83064609)

### Exp8 (2021.11.12 -- 2021.11.17)
#### 实验8.1  特征检测与匹配
- 测试OpenCV中的SIFT, SURF, ORB等特征检测与匹配的方法。将检测到的特征点和匹配关系进行可视化输出，比较不同方法的效率、效果等。

### Exp9 (2021.11.19 -- 2021.11.23)
#### 实验9.1  图像匹配
- 了解cv::matchTemplate函数的用法，并选择合适的测试图像进行测试，要求：

  - 理解TM_SQDIFF等相似性度量方法的含义和适用情况。
  - 针对模板与图像目标存在颜色（亮度）差异、几何形变等情况进行测试分析，可以重点对比TM_SQDIFF和TM_CCOEFF_NORMED进行对比。
