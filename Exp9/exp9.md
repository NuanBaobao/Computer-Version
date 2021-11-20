# 姓名学号

- 张进华 201900150221
# 实验日期
- 2021.11.19
# 实验题目

- 图像匹配

# 实验内容
- 了解cv::matchTemplate函数的用法，并选择合适的测试图像进行测试，要求：
  - 理解TM_SQDIFF等相似性度量方法的含义和适用情况。
  - 针对模板与图像目标存在颜色（亮度）差异、几何形变等情况进行测试分析，可以重点对比TM_SQDIFF和TM_CCOEFF_NORMED进行对比。

# 实验步骤
## 步骤一 了解实验原理

- cv::matchTemplate()的具体调用方法如下：

  ```c++
  	void cv::matchTemplate(
  		cv::InputArray image, // 用于搜索的输入图像, 8U 或 32F, 大小 W-H
  		cv::InputArray templ, // 用于匹配的模板，和image类型相同， 大小 w-h
  		cv::OutputArray result, // 匹配结果图像, 类型 32F, 大小 (W-w+1)-(H-h+1)
  		int method // 用于比较的方法
  	);
  ```

- 该函数第一个参数是源图像，第二个参数是模板图像，第三个参数是匹配的结果图像，第四个参数是用于指定比较的方法,opencv中支持的比较方法有六种，分别如下：

  - 1、cv::TM_SQDIFF：该方法使用**平方差**进行匹配，因此最佳的匹配结果在结果为0处，值越大匹配结果越差。

    ![](https://img-blog.csdn.net/20170406104155042?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvZ3VkdXJ1eXU=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

  - 2、cv::TM_SQDIFF_NORMED：该方法使用**归一化的平方差**进行匹配，最佳匹配也在结果为0处。
  
    ![](https://img-blog.csdn.net/20170406104426686?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvZ3VkdXJ1eXU=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)
    
  - 3、cv::TM_CCORR：**相关性匹配**方法，该方法使用源图像与模板图像的卷积结果进行匹配，因此，最佳匹配位置在值最大处，值越小匹配结果越差。
  
    ![](https://img-blog.csdn.net/20170406104959193?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvZ3VkdXJ1eXU=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

  - 4、cv::TM_CCORR_NORMED：**归一化的相关性匹配**方法，与相关性匹配方法类似，最佳匹配位置也是在值最大处。
  
    ![](https://img-blog.csdn.net/20170406105251647?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvZ3VkdXJ1eXU=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

  - 5、cv::TM_CCOEFF：**相关性系数匹配**方法，该方法使用源图像与其均值的差、模板与其均值的差二者之间的相关性进行匹配，最佳匹配结果在值等于1处，最差匹配结果在值等于-1处，值等于0直接表示二者不相关。
  
    ![](https://img-blog.csdn.net/20170406105847993?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvZ3VkdXJ1eXU=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

  - 6、cv::TM_CCOEFF_NORMED：**归一化的相关性系数**匹配方法，正值表示匹配的结果较好，负值则表示匹配的效果较差，也是值越大，匹配效果也好。
  
    ![](https://img-blog.csdn.net/20170406110236761?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvZ3VkdXJ1eXU=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)



## 步骤二 采用cv::TM_CCOEFF_NORMED进行匹配

- 这里解释一下为什么要进行转化为灰度图？

  - 识别物体，最关键的因素是梯度，梯度意味着边缘，这是最本质的部分，而计算梯度，自然就用到灰度图像了，可以把灰度理解为图像的强度。颜色，易受光照影响，难以提供关键信息，故将图像进行灰度化，同时也可以加快特征提取的速度。


- 然后归一化的相关性系数匹配方法正值表示匹配的结果较好，负值则表示匹配的效果较差，也是值越大，匹配效果也好，所以在绘制时我们采用最大值

  - ```c++
            //模板匹配
            cv::matchTemplate(gray_image_source, gray_image_template, image_matched, cv::TM_CCOEFF_NORMED);
            //寻找最佳匹配位置
            cv::minMaxLoc(image_matched, &minVal, &maxVal, &minLoc, &maxLoc);
          
            cv::circle(image_color,
                       cv::Point(maxLoc.x + image_template.cols/2, maxLoc.y + image_template.rows/2),
                       30,
                       cv::Scalar(0, 0, 255),
                       2,
                       8,
                       0);
    ```

    


#### 1.采用裁剪后的图像作为模板，结果显示如下

- 可以看到在模板未做任何改变的情况下匹配效果还是很好的

  ![](F:\computer-vision\Exp9\images\1.png)

#### 2.采用几何形状改变后的图像作为模板，结果显示如下

- 在模板几何形状改变后我们发现匹配的效果变差了，说明颜色几何形状变化对cv::TM_CCOEFF_NORMED影响很大

  ![](F:\computer-vision\Exp9\images\2.png)
  
- 测试这张图，发现检测出的位置不对，效果不太理想

  ![](F:\computer-vision\Exp9\images\7.png)

#### 3.采用光照变换后的图像作为模板，结果显示如下

- 当模板图片光照发生改变时，我们可以看到匹配的效果仍然是很好的，说明颜色光照变化对cv::TM_CCOEFF_NORMED影响不大

  ![](F:\computer-vision\Exp9\images\3.png)

#### 4 总结

- TM_CCOEFF_NORMED（归一化相关系数法）对光照变化有非常好的稳定性，相比于光照变换而言尺寸变化对结果的影响更大。


## 步骤三 采用cv::TM_SQDIFF进行匹配

- 使用**平方差**进行匹配，因此最佳的匹配结果在结果为0处，值越大匹配结果越差，所以在绘制时我们采用最小值

  - ```c++
            //模板匹配
            cv::matchTemplate(gray_image_source, gray_image_template, image_matched, cv::TM_SQDIFF);
            //寻找最佳匹配位置
            cv::minMaxLoc(image_matched, &minVal, &maxVal, &minLoc, &maxLoc);
          
            cv::circle(image_color,
                       cv::Point(minLoc.x + image_template.cols/2, minLoc.y + image_template.rows/2),
                       30,
                       cv::Scalar(0, 0, 255),
                       2,
                       8,
                       0);
          
    ```

    

#### 1.采用裁剪后的图像作为模板，结果显示如下
- 可以看到在未做任何改变的情况下匹配效果还是很好的

  ![](F:\computer-vision\Exp9\images\4.png)

#### 2.采用几何形状改变后的图像作为模板，结果显示如下
- 在模板几何形状改变后我们发现匹配的效果变差了，说明颜色几何形状变化对cv::TM_SQDIFF方法影响很大

  ![](F:\computer-vision\Exp9\images\5.png)

## 3.采用光照变换后的图像作为模板，结果显示如下
- 当模板图片光照发生改变时，我们可以看到匹配的效果仍然是很好的，说明颜色光照变化对cv::TM_SQDIFF方法影响不是很大

  ![](F:\computer-vision\Exp9\images\6.png)
#### 4.总结
- TM_SQDIFF（平方差匹配法）（归一化相关系数法）对光照变化有非常好的稳定性，相比于光照变换而言尺寸变化对结果的影响更大




# 实验结果分析
- 本次试验中，通过了解cv::matchTemplate函数的用法，掌握了六种相似性度量的方法原理，重点对比了TM_SQDIFF和TM_CCOEFF_NORMED这两种相似性度量的计算方法的效果差异，对尺寸变化和光照变化的稳定性。
- 如果不对模板图像进行任何变换，TM_SQDIFF（平方差匹配法）的效果TM_CCOEFF_NORMED
（归一化相关系数法）的计算更准确，因为根据match result图，利用TM_SQDIFF的基本上只检测出了一个点，而TM_CCOEFF_NORMED除了真正的点上有高亮之外，其他不匹配的地方也有一定的相关性
- TM_SQDIFF（平方差匹配法）和 TM_CCOEFF_NORMED（归一化相关系数法）的对于尺寸变化和光照变化的稳定性很好