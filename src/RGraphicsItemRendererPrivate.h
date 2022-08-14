#ifndef RGRAPHICSITEMRENDERERPRIVATE_H
#define RGRAPHICSITEMRENDERERPRIVATE_H

#include "RGraphicsItemRendererPrivate.h"
#include "RPainterRendererPrivate.h"

#include <QMatrix4x4>

class RGraphicsItemRendererPrivate : public RPainterRendererPrivate
{
	bool frame_changed = false;

	QMatrix4x4 matrix;

public:
	RGraphicsItemRendererPrivate(): RPainterRendererPrivate(){
	}

	~RGraphicsItemRendererPrivate(){}

//	void setupAspectRatio(){
//		this->matrix.setToIdentity();
//		this->matrix.scale();
//	}

	void setupAspectRatio(){
		return;
	}

	bool checkGL(){
		return false;
	}
};

#endif // RGRAPHICSITEMRENDERERPRIVATE_H
