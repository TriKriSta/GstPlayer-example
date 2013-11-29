#include "playerform.h"
#include <QApplication>

int main (int argc, char *argv[]) {
    QApplication app(argc, argv);
    PlayerForm p;
    p.show();

  return app.exec();
}
