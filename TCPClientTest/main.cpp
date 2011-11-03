
#include <QtCore/QCoreApplication>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTcpSocket* tcpSocket = new QTcpSocket(0);
    tcpSocket->connectToHost("127.0.0.1", 53533);
    if ( tcpSocket->waitForConnected () )
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        //out.setVersion(QDataStream::Qt_4_0);
        //out << 0x0100; 
        out << "http://www.google.ca";
        tcpSocket->write(block);
    }
    return a.exec();
}
