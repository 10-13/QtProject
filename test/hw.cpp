#include <QThread>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QLocale>
#include <QtWidgets/QStylePainter>

class MyWidget : public QWidget {
	private:
	QLabel* text;
public:
	MyWidget() : text(new QLabel(this)) {
		text->setText(QT_VERSION_STR);

		setWindowTitle("Hello world!");
	}

	void resizeEvent(QResizeEvent *event) override {
		QLocale loc{};
		text->setText(loc.toString(this->width()) + ":" + loc.toString(this->height()));
	}
};

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	MyWidget* w = new MyWidget();
	w->resize(600,600);
	w->show();

	return app.exec();
}
