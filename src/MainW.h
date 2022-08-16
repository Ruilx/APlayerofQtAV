#ifndef MAINW_H
#define MAINW_H

#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtAV/QtAV>
//#include <QtAVWidgets/GraphicsItemRenderer.h>
#include "RGraphicsItemRenderer.h"

class MainW : public QMainWindow
{
	Q_OBJECT

	QString dir = QApplication::applicationDirPath();

	void closeEvent(QCloseEvent *e) override;
	void resizeEvent(QResizeEvent *e) override;

	QtAV::AVPlayer *player = new QtAV::AVPlayer(this);
	//QtAV::VideoOutput *output = new QtAV::VideoOutput(this);
	//QtAV::GraphicsItemRenderer *output = new QtAV::GraphicsItemRenderer();
	RGraphicsItemRenderer *output = new RGraphicsItemRenderer();

	QGraphicsView *view = new QGraphicsView(this);
	QGraphicsScene *scene = new QGraphicsScene(this);

public:
	MainW(QWidget *parent = nullptr);
	~MainW();
};
#endif // MAINW_H
