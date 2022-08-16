#include "MainW.h"
#include <QScopedPointer>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>

#include <QResizeEvent>
#include <QCloseEvent>

//#include <QtOpenGL/QGLWidget>

void MainW::closeEvent(QCloseEvent *e)
{
	Q_UNUSED(e)
	if(this->player != nullptr){
		if(this->player->state() != QtAV::AVPlayer::StoppedState){
			this->player->stop();
		}
	}
}

void MainW::resizeEvent(QResizeEvent *e)
{
	this->output->resizeRenderer(e->size());
}

MainW::MainW(QWidget *parent)
	: QMainWindow(parent)
{
	this->setMinimumSize(802, 602);
	this->resize(802, 602);
//	if (! this->output->widget()){
//		qFatal("Cannot create video renderer");
//	}
	this->player->setRenderer(this->output);
	this->output->resizeRenderer(800, 600);

	this->view->setScene(this->scene);
	this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->scene->addItem(this->output);

	this->setCentralWidget(this->view);

	this->menuBar()->addAction("Open Media (&O)", [this](bool){
		QString openFilePath = QFileDialog::getOpenFileName(this, "Open Media...", this->dir, "All Files (*.*)");
		if(openFilePath.isEmpty()){
			return;
		}
		this->dir = QFileInfo(openFilePath).dir().path();

		this->player->play(openFilePath);
	});

	this->menuBar()->addAction("Pause/Play (&P)", [this](bool){
		if(this->player->isPlaying()){
			// playing是相对于文件载入, 出错, 停止(stop)等相对的状态,
			// 即便是播放器暂停播放, 状态仍然是playing
			// 暂停和反暂停请使用pause(bool)函数
			if (this->player->isPaused()){
				qDebug() << "Player now paused, will resume.";
				this->player->pause(false);
			}else{
				qDebug() << "Player now playing, will pause.";
				this->player->pause(true);
			}
		}
	});

	QMenu *seekMenu = new QMenu("Seek to (&S)", this);
	seekMenu->addAction("0%", [this](){
		this->player->seek((float)0);
	});
	seekMenu->addAction("10%", [this](){
		this->player->seek(0.1);
	});
	seekMenu->addAction("20%", [this](){
		this->player->seek(0.2);
	});
	seekMenu->addAction("30%", [this](){
		this->player->seek(0.3);
	});
	seekMenu->addAction("40%", [this](){
		this->player->seek(0.4);
	});
	seekMenu->addAction("50%", [this](){
		this->player->seek(0.5);
	});
	seekMenu->addAction("60%", [this](){
		this->player->seek(0.6);
	});
	seekMenu->addAction("70%", [this](){
		this->player->seek(0.7);
	});
	seekMenu->addAction("80%", [this](){
		this->player->seek(0.8);
	});
	seekMenu->addAction("90%", [this](){
		this->player->seek(0.9);
	});
	seekMenu->addAction("99%", [this](){
		this->player->seek(0.99);
	});

	this->menuBar()->addMenu(seekMenu);

//	QAction *setOpenGL = new QAction("Set OpenGL (&G)");
//	this->connect(setOpenGL, &QAction::triggered, [this, setOpenGL](bool){
//		static bool enable = false;
//		enable = !enable;
//		this->output->setOpenGL(enable);
//		setOpenGL->setChecked(enable);
//		if (!enable){
//			this->view->setViewport(0);
//			return;
//		}
//		this->view->setCacheMode(QGraphicsView::CacheNone);
//		QGLWidget *glw = new QGLWidget();
//		glw->setAutoFillBackground(false);
//		this->view->setViewport(glw);
//	});
//	setOpenGL->setCheckable(true);
//	this->menuBar()->addAction(setOpenGL);
}

MainW::~MainW()
{
	if(this->player){
		delete this->player;
	}
}

