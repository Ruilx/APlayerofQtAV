#ifndef RPAINTERRENDERERPRIVATE_H
#define RPAINTERRENDERERPRIVATE_H

#include <QtGui/QPainter>
#include <QtAV/private/VideoRenderer_p.h>

class RPainterRendererPrivate : public QtAV::VideoRendererPrivate
{
public:
	QPainter *painter;
	QImage image;

	RPainterRendererPrivate(){
		this->painter = nullptr;
	}
	~RPainterRendererPrivate(){
		if(this->painter){
			delete this->painter;
			this->painter = nullptr;
		}
	}

	void setupQuality(){
		switch(this->quality){
			case QtAV::VideoRenderer::QualityFastest:
				this->painter->setRenderHint(QPainter::Antialiasing, false);
				this->painter->setRenderHint(QPainter::TextAntialiasing, false);
				this->painter->setRenderHint(QPainter::SmoothPixmapTransform, false);
				this->painter->setRenderHint(QPainter::Antialiasing, false);
				break;
			case QtAV::VideoRenderer::QualityBest:
				this->painter->setRenderHint(QPainter::Antialiasing, true);
				this->painter->setRenderHint(QPainter::TextAntialiasing, true);
				this->painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
				this->painter->setRenderHint(QPainter::Antialiasing, true);
				break;
			case QtAV::VideoRenderer::QualityDefault:
			default:
				break;
		}
	}
};

#endif // RPAINTERRENDERERPRIVATE_H
