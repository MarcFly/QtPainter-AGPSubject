#include "canvas.h"


Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    painter = new QPainter(this);
    allowBegin = true;
}

Canvas::~Canvas()
{
    delete painter;
}

QSize Canvas::sizeHint() const
{
    return QSize(256,256); // this returns expected size
}

QSize Canvas::minimumSizeHint() const
{
    return QSize(64,64); // this returns expected size
}

void Canvas::paintEvent(QPaintEvent* ev)
{
    if(allowBegin)
    {
        const QSize& s = this->size();
        painter->eraseRect(QRectF(0,0,s.width(),s.height()));

        allowBegin = false;
        painter->begin(this);

        painter->setBrush(QBrush(QColor(255,255,255),Qt::BrushStyle::SolidPattern));
        painter->setPen(QPen(Qt::PenStyle::NoPen));
        painter->drawRect(rect());

        CallDraw();
    }
}

void Canvas::drawEntity(const DrawStruct& drawData)
{
    painter->setPen(drawData.outline);
    painter->setBrush(drawData.fill);

    const Transform& t = drawData.t;

    switch(drawData.shape)
    {
    case DrawShapes::BG:
        break;
    case DrawShapes::Box:
        painter->translate(t.px, t.py);
        painter->rotate(t.r);
        painter->translate(- t.sx / 2,- t.sy/2);

        painter->drawRect(0, 0, t.sx, t.sy);

        painter->translate(t.sx / 2, t.sy/2);
        painter->rotate(-t.r);
        painter->translate(-t.px,-t.py);

        drawBox(drawData.t);
        break ;
    case DrawShapes::Circle:
        break;
    case DrawShapes::Line:
        break;
    }
}

void Canvas::drawBox(const Transform &t)
{
}

void Canvas::executeEnd()
{
    painter->end();
    allowBegin = true;
}