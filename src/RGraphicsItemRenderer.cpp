#include "RGraphicsItemRenderer.h"

#include "RGraphicsItemRendererPrivate.h"

#include <QtAV/FilterContext.h>
#include <QtAVWidgets/global.h>

#include <QCoreApplication>
#include <QGraphicsScene>
#include <QPainter>

RGraphicsItemRenderer::RGraphicsItemRenderer(QGraphicsItem *parent): QGraphicsObject(parent), RPainterRenderer(*new RGraphicsItemRendererPrivate()){
	this->setFlag(ItemIsFocusable);
}

RGraphicsItemRenderer::RGraphicsItemRenderer(RGraphicsItemRendererPrivate &d, QGraphicsItem *parent): QGraphicsObject(parent), RPainterRenderer(d){
	this->setFlag(ItemIsFocusable);
}

bool RGraphicsItemRenderer::receiveFrame(const QtAV::VideoFrame &frame){
	this->preparePixmap(frame);
	QCoreApplication::postEvent(this, new QEvent(QEvent::User));
	return true;
}

void RGraphicsItemRenderer::drawBackground(){
	//DPTR_D(RGraphicsItemRenderer);
	RPainterRenderer::drawBackground();
}

void RGraphicsItemRenderer::drawFrame(){
	DPTR_D(RGraphicsItemRenderer);
	if(!d.painter){
		return;
	}
	RPainterRenderer::drawFrame();
}

bool RGraphicsItemRenderer::event(QEvent *event){
	if(event->type() != QEvent::User){
		return QGraphicsObject::event(event);
	}
	if(this->scene() != nullptr){
		this->scene()->update(this->sceneBoundingRect());
		return true;
	}else{
		qCritical() << "Item's scene is nullptr!";
		return false;
	}
}

void RGraphicsItemRenderer::onSetOutAspectRatioMode(RGraphicsItemRenderer::OutAspectRatioMode mode){
	Q_UNUSED(mode)
	DPTR_D(RGraphicsItemRenderer);
	d.setupAspectRatio();
}

void RGraphicsItemRenderer::onSetOutAspectRatio(qreal ratio){
	Q_UNUSED(ratio)
	DPTR_D(RGraphicsItemRenderer);
	d.setupAspectRatio();
}

bool RGraphicsItemRenderer::onSetOrientation(int value){
	Q_UNUSED(value);
	d_func().setupAspectRatio();
	this->update();
	return true;
}

bool RGraphicsItemRenderer::onSetBrightness(qreal brightness){
	Q_UNUSED(brightness)
	if(!this->isOpenGL()){
		return false;
	}
	return false;
}

bool RGraphicsItemRenderer::onSetContrast(qreal contrast){
	Q_UNUSED(contrast)
	if(!this->isOpenGL()){
		return false;
	}
	return false;
}

bool RGraphicsItemRenderer::onSetHue(qreal hue){
	Q_UNUSED(hue)
	if(!this->isOpenGL()){
		return false;
	}
	return false;
}

bool RGraphicsItemRenderer::onSetSaturation(qreal saturation){
	Q_UNUSED(saturation)
	if(!this->isOpenGL()){
		return false;
	}
	return false;
}

QtAV::VideoRendererId RGraphicsItemRenderer::id() const{
	return QtAV::VideoRendererId_GraphicsItem;
}

bool RGraphicsItemRenderer::isSupported(QtAV::VideoFormat::PixelFormat pixelFormat) const{
	return RPainterRenderer::isSupported(pixelFormat);
}

QRectF RGraphicsItemRenderer::boundingRect() const{
	return QRectF(0, 0, this->rendererWidth(), this->rendererHeight());
}

void RGraphicsItemRenderer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Q_UNUSED(option);
	Q_UNUSED(widget);

	DPTR_D(RGraphicsItemRenderer);
	d.painter = painter;
	QtAV::QPainterFilterContext *ctx = static_cast<QtAV::QPainterFilterContext*>(d.filter_context);
	if(ctx){
		ctx->painter = d.painter;
	}else{
		qWarning() << "FilterContext not available!";
	}
	painter->save();
	painter->beginNativePainting();

	this->handlePaintEvent();

	painter->endNativePainting();
	painter->restore();

	d.painter = nullptr;
	if(ctx){
		ctx->painter = nullptr;
	}
}

bool RGraphicsItemRenderer::isOpenGL() const{
	return false;
}

void RGraphicsItemRenderer::setOpenGL(bool o){
	Q_UNUSED(o)
	return;
}











