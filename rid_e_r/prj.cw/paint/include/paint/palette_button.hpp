#ifndef POLYGONANDARCPAINT_PALETTE_BUTTON_HPP
#define POLYGONANDARCPAINT_PALETTE_BUTTON_HPP

#include <QPushButton>


class PaletteButton : public QPushButton {

Q_OBJECT

public:
    explicit PaletteButton(QWidget* parent = nullptr, const std::string& color = "#000");

    std::string color;

private:
    const int SIDE_SIZE = 24;
};


#endif //POLYGONANDARCPAINT_PALETTE_BUTTON_HPP
