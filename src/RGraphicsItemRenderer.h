#ifndef RGRAPHICSITEMRENDERER_H
#define RGRAPHICSITEMRENDERER_H

#include <QtAVWidgets/global.h>
#include "RPainterRenderer.h"

#include <QGraphicsObject>

class RGraphicsItemRendererPrivate;
class RGraphicsItemRenderer : public QGraphicsObject, public RPainterRenderer
{
	Q_OBJECT

	DPTR_DECLARE_PRIVATE(RGraphicsItemRenderer)

	Q_PROPERTY(qreal brightness READ brightness WRITE setBrightness NOTIFY brightnessChanged)
	Q_PROPERTY(qreal contrast READ contrast WRITE setContrast NOTIFY contrastChanged)
	Q_PROPERTY(qreal hue READ hue WRITE setHue NOTIFY hueChanged)
	Q_PROPERTY(qreal saturation READ saturation WRITE setSaturation NOTIFY saturationChanged)
	Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
	Q_PROPERTY(QRectF regionOfInterest READ regionOfInterest WRITE setRegionOfInterest NOTIFY regionOfInterestChanged)
	Q_PROPERTY(qreal sourceAspectRatio READ sourceAspectRatio NOTIFY sourceAspectRatioChanged)
	Q_PROPERTY(qreal outAspectRatio READ outAspectRatio WRITE setOutAspectRatio NOTIFY outAspectRatioChanged)

	Q_PROPERTY(OutAspectRatioMode outAspectRatioMode READ outAspectRatioMode WRITE setOutAspectRatioMode NOTIFY outAspectRatioModeChanged)
	Q_ENUMS(OutAspectRatioMode)
	Q_PROPERTY(int orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)
	Q_PROPERTY(QRect videoRect READ videoRect NOTIFY videoRectChanged)
	Q_PROPERTY(QSize videoFrameSize READ videoFrameSize NOTIFY videoFrameSizeChanged)
	Q_ENUMS(Quality)

public:
	RGraphicsItemRenderer(QGraphicsItem *parent = nullptr);

	QtAV::VideoRendererId id() const override;
	bool isSupported(QtAV::VideoFormat::PixelFormat pixelFormat) const override;

	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	QGraphicsItem *graphicsItem() override { return this; }

	bool isOpenGL() const;
	void setOpenGL(bool o);

	// OpenGLVideo *opengl() const override;

signals:
	void sourceAspectRatioChanged(qreal value) override final;
	void regionOfInterestChanged() override;
	void outAspectRatioChanged() override;
	void outAspectRatioModeChanged() override;
	void brightnessChanged(qreal value) override;
	void contrastChanged(qreal value) override;
	void hueChanged(qreal value) override;
	void saturationChanged(qreal value) override;
	void backgroundColorChanged() override;
	void orientationChanged() override;
	void videoRectChanged() override;
	void videoFrameSizeChanged() override;

protected:
	RGraphicsItemRenderer(RGraphicsItemRendererPrivate &d, QGraphicsItem *parent = nullptr);

	bool receiveFrame(const QtAV::VideoFrame &frame) override;
	void drawBackground() override;

	void drawFrame() override;

	bool event(QEvent *event) override;

private:
	void onSetOutAspectRatioMode(OutAspectRatioMode mode) override;
	void onSetOutAspectRatio(qreal ratio) override;
	bool onSetOrientation(int value) override;
	bool onSetBrightness(qreal brightness) override;
	bool onSetContrast(qreal contrast) override;
	bool onSetHue(qreal hue) override;
	bool onSetSaturation(qreal saturation) override;
};

#endif // RGRAPHICSITEMRENDERER_H
