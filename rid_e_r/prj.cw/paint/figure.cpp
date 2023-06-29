#include "paint/figure.hpp"
#include "paint/mode_enum.hpp"
#include <string>

Figure::Figure(const QList<QPoint>& points, QColor color, int width, int mode) :
        points_(points), color_(color), width_{width}, mode_(mode), config(GetConfigData()) {}

std::string Figure::GetConfigData() {
    std::string configData = std::to_string(width_) + "-" + color_.name().toStdString() + "-" + StringifyMode(mode_);
    return configData;
}

QString Figure::WriteDataToFile() {
    QString stringForFile = "";
    stringForFile.append(QString::fromStdString(this->config + ":"));
    for (int i = 0; i < this->points_.size(); i++) {
        std::string pointInStr = std::to_string(this->points_[i].x()) + "|" + std::to_string(this->points_[i].y()) + ";";
        stringForFile.append(QString::fromStdString(pointInStr));
    }
    return stringForFile;
}

Figure operator*(const Figure& figure, double scale) {
    QList<QPoint> newList{};
    for (QPoint i: figure.points_) {
        newList.append(QPoint(qRound(i.x() * scale), qRound(i.y() * scale)));
    }
    return Figure(newList, figure.color_, figure.width_ * scale, figure.mode_);
}
