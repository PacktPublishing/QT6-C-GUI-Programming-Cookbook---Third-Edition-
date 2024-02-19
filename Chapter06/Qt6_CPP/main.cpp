#include <QCoreApplication>
#include <QDebug>

#include <QLinkedList>
#include <QRegExp>
#include <QStringView>
#include <QTextCodec>
#include <QTextEncoder>
#include <QTextDecoder>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	// QLinkedList
	QLinkedList<QString> list;
	list << "string1" << "string2" << "string3";
	QLinkedList<QString>::iterator it;
	for (it = list.begin(); it != list.end(); ++it)
	{
		qDebug() << "QLinkedList:" << *it;
	}

	// QRegExp
	QRegExp rx("\\d+");
	QString text = "Jacky has 3 carrots, 15 apples, 9 oranges and 12 grapes.";
	QStringList myList;
	int pos = 0;
	while ((pos = rx.indexIn(text, pos)) != -1)
	{
		// Separate all numbers from the sentence
		myList << rx.cap(0);
		pos += rx.matchedLength();
	}
	qDebug() << "QRegExp:" << myList;

	// QStringView
	QStringView x = QString("Good afternoon");
	QStringView y = x.mid(5, 5);
	QStringView z = x.mid(5);
	qDebug() << "QStringView:" << y; // after
	qDebug() << "QStringView:" << z; // afternoon

	// QTextCodec
	QByteArray data = "\xCE\xB1\xCE\xB2\xCE\xB3"; // Alpha, beta, gamma symbols
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QString str = codec->toUnicode(data);
	qDebug() << "QTextCodec:" << str;

	// QTextEncoder
	QString str2 = QChar(0x41); // Character "A"
	QTextCodec *locale = QTextCodec::codecForLocale();
	QTextEncoder *encoder = locale->makeEncoder();
	QByteArray encoded = encoder->fromUnicode(str2);
	qDebug() << "QTextEncoder:" << encoded.data();

	// QTextDecoder
	QByteArray data2 = "\x82\xB1\x82\xF1\x82\xC9\x82\xBF\x82\xCD\x90\xA2\x8A\x45"; // "Hello world" in Japanese
	QTextCodec *codec2 = QTextCodec::codecForName("Shift-JIS");
	QTextDecoder *decoder = codec2->makeDecoder();
	QString decoded = decoder->toUnicode(data2);
	qDebug() << "QTextDecoder:" << decoded;

	return a.exec();
}
