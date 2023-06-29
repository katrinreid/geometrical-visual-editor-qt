#include "paint/paint_app.hpp"

#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    PaintApp w;
    w.show();
    return a.exec();
}
