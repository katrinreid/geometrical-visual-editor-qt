#ifndef POLYGONANDARCPAINT_FIGURE_FILE_MANAGER_HPP
#define POLYGONANDARCPAINT_FIGURE_FILE_MANAGER_HPP

#include "figure.hpp"
#include <QList>
#include <QPoint>
#include <QWidget>


class FigureFileManager {
public:
    FigureFileManager() = default;

    ~FigureFileManager() = default;

    FigureFileManager(QWidget* parent, QList<Figure> figures);

    /**
     @brief Сохраняет информацию о всех фигурах в файл на устройстве пользователя
     */
    void Save();

    /**
     @return Список фигур, полученных из файла
     */
    QList<Figure> Load();

private:
    /**
     @return Строка, хранящая информацию о всех фигурах (конфигурационная информация и координаты вершин)
     */
    QString GetFigureDataInStringFormat();

private:
    QList<Figure> figuresList{};
    QWidget* parent{};
};


#endif //POLYGONANDARCPAINT_FIGURE_FILE_MANAGER_HPP
