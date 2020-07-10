#ifndef DISPOSITIVO_H
#define DISPOSITIVO_H

#include <QObject>

class Dispositivo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString nombre READ nombre)
public:
    explicit Dispositivo(QObject *parent = nullptr);
    Dispositivo(QString nombre);
    QString nombre() const;

signals:

private:
    QString m_nombre;

};

#endif // DISPOSITIVO_H
