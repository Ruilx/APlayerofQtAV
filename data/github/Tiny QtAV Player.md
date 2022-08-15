# Tiny QtAV Player

Original name: A Player of QtAV

[QtAV](https://github.com/wang-bin/QtAV) is a cross-platform multimedia player framework based on Qt and FFmpeg, it uses FFmpeg to convert video and audio codec and shows video frame and interactive components through Qt framework. 

QtAV's official website is [http://www.qtav.org](http://www.qtav.org).

The latest version of QtAV is 1.12.0 public released at June 21, 2017. It has a long time since last released. Developing version now at 1.13.

The using instructions of QtAV please refer to project WIKI.

## The Issue

The renderer module of QtAV, QPainterRenderer classes will crush the program with a Qt error message below, eg:

``` text
QPixmap: Must construct a QGuiApplication before a QPixmap
```

After research for long time, many solutions says the compiling type need setting to 'Release' rather than 'Debug'. 'Release' setting will link DLL to 'QtAVWidgets1.dll' rather than 'QtAVWidgetsd1.dll', the program runs normally but I still not figured out how it works.

But this isn't a prefect solution, and calling FFmpeg api functions directly not a good plan either.

