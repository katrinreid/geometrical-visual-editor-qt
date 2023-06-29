#include <utility>

#include "paint/figure_file_manager.hpp"
#include "paint/mode_enum.hpp"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

FigureFileManager::FigureFileManager(QWidget* parent, QList<Figure> figures) : parent(parent),
                                                                               figuresList(std::move(figures)) {
}

void FigureFileManager::Save() {
    QString fileName = QFileDialog::getSaveFileName(parent, "Сохранить файл", "", "TXT(*.txt)");
    QFile fileSaver(fileName);
    fileSaver.open(QIODevice::WriteOnly);
    fileSaver.write(GetFigureDataInStringFormat().toLatin1());
    fileSaver.close();
}

QString FigureFileManager::GetFigureDataInStringFormat() {
    QString figureStr;
    for (Figure& figure: figuresList) {
        if (figure.mode_ == static_cast<int>(Mode::None)) {
            continue;
        }

        figureStr.append(figure.WriteDataToFile() + QString::fromStdString("\n"));
    }
    return figureStr;
}

QList<Figure> FigureFileManager::Load() {
    QList<Figure> figures;

    QString fileName = QFileDialog::getOpenFileName(parent, "Загрузить файл", "", "TXT(*.txt)");

    QFile fileLoader(fileName);
    fileLoader.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&fileLoader);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> configAndPoints = line.split(":");
        QList<QString> config = configAndPoints[0].split("-");

        int width = config[0].toInt();
        auto color = QColor(config[1]);
        Mode mode = ModifyString(config[2].toStdString());

        QList<QPoint> points{};
        QList<QString> strPoints = configAndPoints[1].split(";");
        for (int i = 0; i < strPoints.size() - 1; i++) {
            QList<QString> coords = strPoints[i].split("|");
            points.append(QPoint(coords[0].toInt(), coords[1].toInt()));
        }
        figures.append(Figure(points, color, width, static_cast<int>(mode)));
    }

    fileLoader.close();
    return figures;
}
