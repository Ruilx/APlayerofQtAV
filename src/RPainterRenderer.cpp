#include "RPainterRenderer.h"

#include <RPainterRendererPrivate.h>
#include <QtAV/FilterContext.h>

#include <QDebug>

RPainterRenderer::RPainterRenderer(): QtAV::VideoRenderer(*new RPainterRendererPrivate())
{
	DPTR_D(RPainterRenderer);
	d.filter_context = QtAV::VideoFilterContext::create(QtAV::VideoFilterContext::QtPainter);
}

RPainterRenderer::RPainterRenderer(RPainterRendererPrivate &d): QtAV::VideoRenderer(d)
{
	d.filter_context = QtAV::VideoFilterContext::create(QtAV::VideoFilterContext::QtPainter);
}

bool RPainterRenderer::isSupported(QtAV::VideoFormat::PixelFormat pixelFormat) const {
	return QtAV::VideoFormat::imageFormatFromPixelFormat(pixelFormat) != QImage::Format_Invalid;
}

bool RPainterRenderer::preparePixmap(const QtAV::VideoFrame &frame){
	DPTR_D(RPainterRenderer);

	QImage::Format imageFormat = frame.imageFormat();
	if(frame.constBits(0)){
		d.video_frame = frame;
	}else{
		if(imageFormat == QImage::Format_Invalid){
			d.video_frame = frame.to(QtAV::VideoFormat::Format_RGB32);
			imageFormat = d.video_frame.imageFormat();
		}else{
			d.video_frame = frame.to(frame.pixelFormat());
		}
	}
	const bool swapRGB = (int)imageFormat < 0;
	if(swapRGB){
		imageFormat = (QImage::Format)(-imageFormat);
	}

	//d.image = QImage((uchar*)d.video_frame.constBits(), d.video_frame.width(), d.video_frame.height(), d.video_frame.bytesPerLine(), imageFormat);

	if(d.image.width() != d.video_frame.bytesPerLine() / 4 || d.image.height() != d.video_frame.height()){
		qDebug() << "Image rewrite!" << d.image;
		//d.image = QImage(d.video_frame.size(), imageFormat);
		d.image = QImage(d.video_frame.bytesPerLine() / 4, d.video_frame.height(), imageFormat);
	}

	if(d.image.format() != imageFormat){
		qDebug() << "Image format not same" << "Image:" << d.image.format() << "Video:" << d.video_frame.imageFormat();
		d.image = d.image.convertToFormat(imageFormat);
	}

//	if(d.video_frame.bytesPerLine() != d.image.bytesPerLine()){
//		qDebug() << "Image bytes per line not same" << "Image:" << d.image.bytesPerLine() << "Video:" << d.video_frame.bytesPerLine();
//	}

	// if videoframe has not save bytesPerLine to image, the video output will show displacement
	// QImage construct function has the argument to specify how many bytes need to copy in line
	// maybe QImage calculated every line size before copy image data
	// here uses only ONE-COPY method to copy whole data to image, but it cannot cover situation
	// when bytesPerLine not same between videoframe and image (at same imageformat).
	memcpy(d.image.bits(), (uchar*)d.video_frame.constBits(), d.image.bytesPerLine() * d.image.height());

	if(swapRGB){
		d.image = d.image.rgbSwapped();
	}

	return true;
}

void RPainterRenderer::drawBackground(){
	DPTR_D(RPainterRenderer);

	if(!d.painter){
		return;
	}
	const QRegion bgRegion(this->backgroundRegion());
	if(bgRegion.isEmpty()){
		return;
	}

	d.painter->save();
	d.painter->setClipRegion(bgRegion);
	d.painter->fillRect(QRect(QPoint(), this->rendererSize()), this->backgroundColor());
	d.painter->restore();
}

void RPainterRenderer::drawFrame(){

	DPTR_D(RPainterRenderer);

	if(!d.painter){
		return;
	}
	if(d.image.isNull()){
		return;
	}
	QRect roi = realROI();
	if(d.rotation() == 0){
		if(roi.size() == d.out_rect.size()){
			d.painter->drawImage(d.out_rect.topLeft(), d.image, roi);
		}else{
			d.painter->drawImage(d.out_rect, d.image, roi);
		}
		return;
	}
	d.painter->save();
	d.painter->translate(this->rendererWidth() / 2, this->rendererHeight() / 2);

	if(d.rotation() % 180){
		d.painter->scale((qreal)d.out_rect.width() / (qreal)this->rendererHeight(), (qreal)d.out_rect.height() / (qreal)this->rendererWidth());
	}else{
		d.painter->scale((qreal)d.out_rect.width() / (qreal)this->rendererWidth(), (qreal)d.out_rect.height() / (qreal)this->rendererHeight());
	}
	d.painter->rotate(d.rotation());
	d.painter->translate(-rendererWidth() / 2, -rendererHeight() / 2);
	d.painter->drawImage(QRect(0, 0, this->rendererWidth(), this->rendererHeight()), d.image, roi);
	d.painter->restore();
}



