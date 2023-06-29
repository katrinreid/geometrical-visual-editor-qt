#include <string>

enum class Mode {
    Polygon = 1,
    Line,
    None
};

/**
@param mode Режим в виде числа
@return Режим в виде строки
 */
inline std::string StringifyMode(int mode) {
    switch (mode) {
        case static_cast<int>(Mode::Polygon):
            return "Polygon";
        case static_cast<int>(Mode::Line):
            return "Line";
        default:
            return "None";
    }
}

/**
@param mode Режим в виде строки
@return Режим в виде объекта Mode
 */
inline Mode ModifyString(const std::string& mode) {
    if (mode == "Polygon") return Mode::Polygon;
    else if (mode == "Line") return Mode::Line;
    else return Mode::None;
}
