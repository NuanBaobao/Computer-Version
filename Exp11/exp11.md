# 学号姓名
- 201900150221 张进华

# 班级
- 19人工智能

# 实验E11：基于学习的局部特征

- 设计实验，对比SIFT和R2D2特征匹配的效果，并重点对比分析特征的旋转不变性、尺度不变性。

- R2D2代码和预训练模型可以从github下载（https://github.com/naver/r2d2，不需要自己重新训练）

- 实验数据可以自己构建，也可以用公开数据集

# 了解r2d2

- r2d2全称为**可靠且可重复的检测器和描述符 (Reliable and Repeatable Detector and Descriptor)**，我了解的大概意思就是说在抽取一个图像特征的时候，对于图像特征的检测和描述是联系密切的，当我们选择一个关键点时，应该选择同时具有重复性和区分度的，但这个确实是一个矛盾。所以，r2d2将特征的检测和描述过程运用神经网络联合在一起，在共同训练的过程中提高描述子的可靠性，最终的网络结构如下

  ![](F:\computer-vision\Exp11\r2d2-master\imgs\1.png)
  
  
  
- 网络在输出每个像素的描述子的同时，也输出两个相关的可重复性和可靠性的maps,前者用来估计关键点是可重复的，后者用来估计描述子是可区别的，而最终关键点取自两张图响应最大化的位置。

# 实验步骤

## 利用r2d2模型提取图像特征
- 首先我为本次实验准备了三张图片，分别为原图，尺度变换后的图以及旋转变换后的图，然后用如下命令利用r2d2提取图像特征，将提取出的描述子和关键点信息存储

  ```python
  python extract.py --model models/r2d2_WASF_N16.pt --images imgs/wechat1.jpg --top-k 5000
  python extract.py --model models/r2d2_WASF_N16.pt --images imgs/wechat2.png --top-k 5000
  python extract.py --model models/r2d2_WASF_N16.pt --images imgs/wechat2_1.png --top-k 5000
  ```

- 提取过程如图所示

  ![](F:\computer-vision\Exp11\r2d2-master\imgs\2.png)

- 接下来开始读取三张图片的关键点以及描述子的信息，并将读取出的特征点**<KeyPoint 000001957DAA31E0>**数据结构转为普通的点类型

  ```python
  key1 = [cv2.KeyPoint(key1[i][0], key1[i][1], 1) for i in range(key1.shape[0])]
  ```

- 最终提取出的特征如图,然后进行特征匹配，根据特征匹配子和描述子信息建立match，选择匹配度最高的进行绘制



- 对于**尺度变化**的，最后的匹配效果如下，可以发现检测出很多重复性的特征，而在匹配的时候，大多数都匹配错误

  ![](F:\computer-vision\Exp11\r2d2-master\imgs\4.png)
  
- 而对于**旋转变换**的，效果如下，发现效果比上面要好一点

  ![](F:\computer-vision\Exp11\r2d2-master\imgs\5.png)



## 利用sift模型提取图像特征

- 利用SIFT提取特征并绘制之前实验做过，这里直接调用之前的代码，实现效果如下

- 对于**尺度变换**后的图，匹配效果如下，可以发现有很多匹配错误的点，但是大体上匹配到了我们的特征点

  ![](F:\computer-vision\Exp11\r2d2-master\imgs\7.png)

- 对于**旋转变换**后的图，匹配效果如下，同样可以发现有很多匹配错误的点，但是大体上也匹配到了我们的特征点

  
  
  ![](F:\computer-vision\Exp11\r2d2-master\imgs\6.png)
  
# 实验结果
- R2D2对于**尺度变化**的，可以发现检测出很多重复性的特征，而在匹配的时候，大多数都匹配错误,而对于**旋转变换**的,发现效果比尺度变换要好一点
- 利用SIFT提取特征，对于**尺度变换**后的图，可以发现有很多匹配错误的点，但是大体上匹配到了我们的特征点，对于**旋转变换**后的图，同样可以发现有很多匹配错误的点，但是大体上也匹配到了我们的特征点
