#ifndef POLYGONANDARCPAINT_CANVAS_HPP
#define POLYGONANDARCPAINT_CANVAS_HPP

#include "figure.hpp"
#include <QWidget>
#include <QColor>

class Canvas : public QWidget {
    Q_OBJECT


public:
    explicit Canvas(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event) override;

    void mouseMoveEvent(QMouseEvent* e) override;

    void mousePressEvent(QMouseEvent* event) override;

    /**
     @brief
     @param f Функция, которая содержит код, для рисования
     @param color Цвет, с помощью которого надо рисовать
     */
    void DrawFigures(std::function<void(QPainter * )> f, QColor color);

    /**
     @brief Перерисовывает все фигуры, которые содержит в figuresList
     */
    void ReDrawAllFigures();

    /**
     @brief Сохраняет только что нарисованную фигуру в figuresList
     */
    void SaveFigure();

    /**
     @brief Очистка всего канваса
     */
    void Clear();

    /**
     @brief
     @param c Новый цвет для отрисовки
     */
    void SetPenColor(QColor c);

public:
    /**
     @brief Режим для выбора вершин фигур
     */
    bool isPointChosen = false;

    /**
     @brief Выбранная вершина
     */
    QPoint* chosenPoint{};

    /**
     @brief Выбранная фигура
     */
    Figure* chosenFigure{};

    /**
     @brief Список сохраненных фигур
     */
    QList <Figure> figuresList{};

    /**
     @brief Список построенных точек текущей несохраненной фигуры
     */
    QList <QPoint> chosenPointsList{};
    QImage canvasImage_;
    QColor penColor_;
    QColor lastColor_;

    /**
     @brief Режим: 1 - Многоугольник
                   2 - Ломаная
                   3 - Ничего не выбрано
     */
    int mode_;

    /**
     @brief Толщина рисуемых линий
     */
    int width_;
};


#endif //POLYGONANDARCPAINT_CANVAS_HPP
