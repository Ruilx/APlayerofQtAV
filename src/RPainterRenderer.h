#ifndef RPAINTERRENDERER_H
#define RPAINTERRENDERER_H

#include <QtAV/VideoRenderer.h>

class RPainterRendererPrivate;
class RPainterRenderer : public QtAV::VideoRenderer
{
	DPTR_DECLARE_PRIVATE(RPainterRenderer)

public:
	RPainterRenderer();
	bool isSupported(QtAV::VideoFormat::PixelFormat pixelFormat) const override;

protected:
	bool preparePixmap(const QtAV::VideoFrame &frame);
	void drawBackground() override;

	void drawFrame() override;

	RPainterRenderer(RPainterRendererPrivate &d);
};

#endif // RPAINTERRENDERER_H
