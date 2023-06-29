#ifndef PAINTAPP_HPP
#define PAINTAPP_HPP

#include "canvas.hpp"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <functional>

class PaintApp : public QMainWindow {

Q_OBJECT

public:
    explicit PaintApp(QWidget* parent = nullptr);

    ~PaintApp() override;

    /**
     @param layout Слой, где будут размещены кнопки с цветами
     */
    void AddPaletteButtons(QHBoxLayout* layout);

    /**
     @param layout Слой, где будут размещены кнопки с режимами рисования
     */
    void AddFunctionButton(QHBoxLayout* layout);

public slots:

    void SetColor();

    void CreatePolygon();

    void CreateLine();

    void SetChoose();

    void Clear();

    void Scale();

    void SaveFigures();

    void LoadFigures();

public:
    Canvas* canvas_;
    int width_ = 1200;
    int height_ = 800;
};

#endif // PAINTAPP_HPP
