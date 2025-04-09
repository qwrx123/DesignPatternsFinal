#include <QApplication>
#include <QWidget>
#include <QLabel>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Basic Qt6 Application");

    window.show();

    return app.exec();
}