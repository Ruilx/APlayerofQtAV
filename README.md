# Tiny QtAV Player

原名: A Player of QtAV

[QtAV](https://github.com/wang-bin/QtAV)是一个基于Qt和FFmpeg实现的多平台多媒体播放框架, 可以后端通过FFmpeg对多媒体素材进行转码, 并通过Qt组件的窗口/平台播放素材内容. 

QtAV的官方网站在[http://www.qtav.org/](http://www.qtav.org/)

QtAV最新的1.12.0版本于2017年6月21日发布, 已长时间未更新, 开发版本还在1.13

QtAV组件的使用方法请参考项目wiki

## 问题

QtAV视频Renderer组件QtAVWidgets中QPainterRenderer组件类在debug环境执行时会出现例如

``` text
QPixmap: Must construct a QGuiApplication before a QPixmap
```

导致进程直接会退出, 经多方查询, 需要将项目编译方式从debug变更为release, 根据工程项目配置, release方式会链接QtAVWidgets.dll后, 程序即可用, 具体策略暂未知.

这种方案在开发模式下肯定不是一个优选的办法

又由于直接操作FFmpeg比较麻烦, 先尝试实现一个simple player, 解决问题

## 环境

由于以解决问题为主, 所以该项目并未考虑QtAVWidgets在复杂场景下的实现, 在这里公开源码, 可供参考解决问题, 可根据自己的环境可自行编写合适的实现.

* 测试平台: Windows 8.1 x86_64  self-customized
* QtSDK: Qt 5.12.12 MinGW 730_64
* QtAV: QtAV 1.13.0
* 目标: 使用QtAVWidgets实现一个QGraphicsItem渲染
* 先不使用OpenGL

## 问题探索

Qt报告既然是QPixmap产生的问题, 即依照QPixmap实例向下寻找, 在QPainterRender所属类组的私有类QPainterRenderPrivate(QPainterRenderer_p.h)中类成员实现了一个QPixmap pixmap, 查看pixmap上下文大概是在实现类中的preparePixmap, 将VideoFrame中的数据预先刷入Qt的某绘图容器中, 以便在drawBackground/drawFrame中通过QPainter绘入窗口中

这里的QPixmap就是导致Qt报告问题的原因

在我调试的stack中, 这个QPixmap是在VideoThread::run中构造的, 这个线程可能不是从QApplication启动的, 或QPixmap构造时未见qApp实例 **(猜测的)**, 导致assert失败

![image-20220815002233197](data\github\image-20220815002233197.png) 

## 问题解决方案

既然不让使用QPixmap, 那就不用QPixmap, 实现一个RPainterRenderer, 使用QImage代替QPixmap存储绘图数据, 解决问题

调用/继承层如下

```text
QGraphicsScene
+-- RGraphicsItemRenderer (QGraphicsItem)
    !-- RPainterRenderer
        !-- QtAV::VideoRenderer
            !-- ...
```

本项目实现了RPainterRenderer类及其private类的实现

使用QImage接收视频数据, 并使用QPainter绘图至GraphicsItem

测试渲染实现了RGraphicsItemRenderer类及其private类的实现

使用QGraphicsItem将item加入至QGraphicsScene实现视频渲染

## 优化

QPainterRenderer原本的渲染方案 QImage -> QPixmap::fromImage -> QPainter::drawPixmap(..., QPixmap), 复制次数极多

新方案优化QImage, 尝试使用已创建好的QImage输出固定大小的Video

使用一次memcpy将VideoFrame数据提供给QImage, 比同时期使用等于号'='要降低约一半CPU使用率

Native绘图方式CPU使用率还是要比OpenGL高, 有机会尝试实现一个OpenGL的QGraphicsItem.

问题解决, 感谢点赞~
