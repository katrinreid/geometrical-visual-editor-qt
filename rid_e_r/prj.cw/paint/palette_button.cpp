#include "paint/palette_button.hpp"

PaletteButton::PaletteButton(QWidget* parent, const std::string& color) : QPushButton(parent),
                                                                          color(color) {
    this->setFixedSize(QSize(SIDE_SIZE, SIDE_SIZE));
    this->setStyleSheet(QString::fromStdString("background-color: ") + QString::fromStdString(color));
}
