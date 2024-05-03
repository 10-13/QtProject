#include <QThread>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QtWidgets/QStylePainter>

class MyWidget : public QWidget {
public:
	MyWidget() {
		QLabel* label = new QLabel(this);
		label->setText(QT_VERSION_STR);

		setWindowTitle("Hello world!");
	}
};

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	MyWidget* w = new MyWidget();
	w->resize(600,600);
	w->show();

	return app.exec();
}
