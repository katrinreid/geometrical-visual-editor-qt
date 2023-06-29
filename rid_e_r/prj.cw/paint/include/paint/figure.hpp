#ifndef POLYGONANDARCPAINT_FIGURE_HPP
#define POLYGONANDARCPAINT_FIGURE_HPP

#include <QList>
#include <QPoint>
#include <QColor>

class Figure {
public:
    Figure() = default;

    ~Figure() = default;

    explicit Figure(const QList<QPoint>& points, QColor color, int width, int mode_);

    /**
     @brief Получает конфигурационные данные (режим, толщина пера, цвет)
     */
    std::string GetConfigData();

    /**
     @brief Создает информацию о фигуре в формате конфигурация:координаты вершин
     @return строка со всей информацией о фигуре
     */
    QString WriteDataToFile();
public:
    QColor color_;
    QList<QPoint> points_;

    int mode_;
    int width_;
    std::string config;
};

Figure operator*(const Figure& figure, double scale);

#endif //POLYGONANDARCPAINT_FIGURE_HPP
