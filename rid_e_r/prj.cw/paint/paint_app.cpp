#include "paint/paint_app.hpp"
#include "paint/palette_button.hpp"
#include "paint/figure_file_manager.hpp."
#include "paint/mode_enum.hpp"

#include <QInputDialog>
#include <QMenuBar>
#include <QMenu>

const std::vector<std::string> COLOR{
        "#000000",
        "#141923",
        "#414168",
        "#3a7fa7",
        "#35e3e3",
        "#8fd970",
        "#5ebb49",
        "#458352",
        "#dcd37b",
        "#fffee5",
        "#ffd035",
        "#cc9245",
        "#a15c3e",
        "#a42f3b",
        "#f45b7a",
        "#c24998",
        "#81588d",
        "#bcb0c2",
        "#ffffff"
};

PaintApp::PaintApp(QWidget* parent)
        : QMainWindow(parent), canvas_(new Canvas()) {

    this->setWindowTitle("Paint");
    auto* widget = new QWidget();
    auto* vLayout = new QVBoxLayout(widget);
    auto* topLayout = new QHBoxLayout();
    auto* colorLayout = new QHBoxLayout();
    auto* functionButtonLayout = new QHBoxLayout();

    topLayout->addWidget(canvas_);
    AddPaletteButtons(colorLayout);
    AddFunctionButton(functionButtonLayout);

    vLayout->addLayout(topLayout);
    vLayout->addLayout(colorLayout);
    vLayout->addLayout(functionButtonLayout);

    setCentralWidget(widget);
    setFixedSize(width_, height_);

    auto* saveFile = new QAction("Сохранить");
    auto* loadFile = new QAction("Загрузить");
    auto* file = menuBar()->addMenu("Файл");
    file->addAction(saveFile);
    file->addAction(loadFile);

    connect(saveFile, &QAction::triggered, this, &PaintApp::SaveFigures);
    connect(loadFile, &QAction::triggered, this, &PaintApp::LoadFigures);
}

PaintApp::~PaintApp() {
    delete canvas_;
}

void PaintApp::AddPaletteButtons(QHBoxLayout* layout) {
    layout->addStretch();
    for (const std::string& c: COLOR) {
        auto* button = new PaletteButton(this, c);
        QObject::connect(button, SIGNAL (clicked()), this, SLOT(SetColor()));

        layout->addWidget(button);
        layout->addStretch();
    }
}

void PaintApp::AddFunctionButton(QHBoxLayout* layout) {
    std::vector<std::pair<std::string, void (PaintApp::*)()>> functionButtonName{
            {"Polygon", &PaintApp::CreatePolygon},
            {"Line",    &PaintApp::CreateLine},
            {"Choose",  &PaintApp::SetChoose},
            {"Clear",   &PaintApp::Clear},
            {"Scale",   &PaintApp::Scale},
    };
    layout->addStretch();
    for (std::pair buttonData: functionButtonName) {
        auto* funcButton = new QPushButton(this);
        funcButton->setText(QString::fromStdString(buttonData.first));
        QObject::connect(funcButton, &QPushButton::clicked, this, buttonData.second);

        layout->addWidget(funcButton);
        layout->addStretch();
    }
}

void PaintApp::SetColor() {
    canvas_->SetPenColor(QColor(QString::fromStdString(((PaletteButton*) sender())->color)));
}

void PaintApp::CreatePolygon() {
    canvas_->SaveFigure();
    canvas_->mode_ = static_cast<int>(Mode::Polygon);
}

void PaintApp::CreateLine() {
    canvas_->SaveFigure();
    canvas_->mode_ = static_cast<int>(Mode::Line);
}

void PaintApp::SetChoose() {
    canvas_->SaveFigure();
    canvas_->mode_ = static_cast<int>(Mode::None);
}

void PaintApp::Clear() {
    canvas_->chosenPointsList.clear();
    canvas_->figuresList.clear();
    canvas_->Clear();
}

void PaintApp::Scale() {
    if (!canvas_->isPointChosen)
        return;

    bool ok;
    QString text = QInputDialog::getText(this, "Масштаб", "Введите масштаб", QLineEdit::Normal, "0.8", &ok);

    if (!ok || text.isEmpty())
        return;

    *canvas_->chosenFigure = *canvas_->chosenFigure * text.toDouble();
    canvas_->ReDrawAllFigures();
}

void PaintApp::SaveFigures() {
    FigureFileManager fileManager = FigureFileManager(this, canvas_->figuresList);
    fileManager.Save();
}

void PaintApp::LoadFigures() {
    FigureFileManager fileManager = FigureFileManager(this, canvas_->figuresList);
    canvas_->figuresList = fileManager.Load();
    canvas_->ReDrawAllFigures();
}

