#include "paint/canvas.hpp"
#include "paint/mode_enum.hpp"

#include <QMouseEvent>
#include <QPainter>
#include <cmath>

Canvas::Canvas(QWidget*parent) : QWidget(parent), width_(5), mode_(static_cast<int>(Mode::Polygon)) {
    canvasImage_ = QImage(size(), QImage::Format_RGB32);
    canvasImage_.fill(Qt::white);
    penColor_ = QColor(0, 0, 0);
    lastColor_ = penColor_;
}

void Canvas::DrawFigures(std::function<void(QPainter*)> f, QColor color = -1) {
    QPainter painter(&canvasImage_);
    QColor temp = penColor_;
    penColor_ = color == -1 ? penColor_ : color;
    QPen p(penColor_, width_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(p);

    f(&painter);

    painter.end();
    penColor_ = temp;
    update();
}

void Canvas::paintEvent(QPaintEvent*event) {
    QPainter painter(this);
    painter.drawImage(rect(), canvasImage_, canvasImage_.rect());
}

void Canvas::mouseMoveEvent(QMouseEvent*e) {
    QWidget::mouseMoveEvent(e);
}

void Canvas::mousePressEvent(QMouseEvent*event) {
    if (event->button() == Qt::LeftButton) {
        if (mode_ != static_cast<int>(Mode::None)) {
            chosenPointsList.append(event->pos());
        }

        switch (mode_) {
            case static_cast<int>(Mode::Polygon):
                if (chosenPointsList.size() > 2) {
                    lastColor_ = penColor_;
                    ReDrawAllFigures();
                    DrawFigures([this](QPainter*painter) {
                        painter->drawPolygon(chosenPointsList.toVector());

                        for (QPoint i: chosenPointsList) {
                            painter->setBrush(penColor_);
                            painter->drawEllipse(i, width_ * 2, width_ * 2);
                        }
                    });
                }
                break;
            case static_cast<int>(Mode::Line):
                if (chosenPointsList.size() >= 2) {
                    lastColor_ = penColor_;
                    ReDrawAllFigures();
                    DrawFigures([this](QPainter* painter) {
                        for (int i = 0; i < chosenPointsList.size() - 1; i++) {
                            painter->drawLine(chosenPointsList[i], chosenPointsList[i + 1]);
                        }

                        for (QPoint i: chosenPointsList) {
                            painter->setBrush(penColor_);
                            painter->drawEllipse(i, width_ * 2, width_ * 2);
                        }
                    });
                }
                break;
            case static_cast<int>(Mode::None):
                if (isPointChosen) {
                    *chosenPoint = event->pos();
                    isPointChosen = false;
                    ReDrawAllFigures();
                    return;
                }

                QPoint now = event->pos();
                for (auto& i: figuresList) {
                    for (auto& j: i.points_) {
                        if (abs(j.x() - now.x()) <= i.width_ * 2 && abs(j.y() - now.y()) <= i.width_ * 2) {
                            chosenPoint = &j;
                            chosenFigure = &i;
                            isPointChosen = true;
                            DrawFigures([this](QPainter*painter) {
                                painter->setBrush(penColor_);
                                painter->drawEllipse(*chosenPoint, width_ * 2, width_ * 2);
                            }, Qt::red);
                            break;
                        }
                    }
                }
                break;
        }
    }
}

void Canvas::Clear() {
    canvasImage_ = QImage(this->size(), QImage::Format_RGB32);
    canvasImage_.fill(Qt::white);
    update();
}

//void Canvas::keyPressEvent(QKeyEvent* event) {
//    qDebug() << event->key();
//    if (event->key() == Qt::Key_Enter) {
//
//    }
//}

void Canvas::ReDrawAllFigures() {
    Clear();
    for (Figure figure: figuresList) {
        DrawFigures([&figure](QPainter*painter) {
            switch (figure.mode_) {
                case static_cast<int>(Mode::Polygon):
                    painter->drawPolygon(figure.points_.toVector());

                    for (QPoint i: figure.points_) {
                        painter->setBrush(figure.color_);
                        painter->drawEllipse(i, figure.width_ * 2, figure.width_ * 2);
                    }
                    break;
                case static_cast<int>(Mode::Line):
                    for (int i = 0; i < figure.points_.size() - 1; i++) {
                        painter->drawLine(figure.points_[i], figure.points_[i + 1]);
                    }

                    for (QPoint i: figure.points_) {
                        painter->setBrush(figure.color_);
                        painter->drawEllipse(i, figure.width_ * 2, figure.width_ * 2);
                    }
                    break;
                case static_cast<int>(Mode::None):
                    break;
            }

        }, figure.color_);
    }
}

void Canvas::SaveFigure() {
    figuresList.append(Figure(chosenPointsList, lastColor_, width_, mode_));
    chosenPointsList.clear();
}

void Canvas::SetPenColor(QColor c) {
    penColor_ = c;
}
