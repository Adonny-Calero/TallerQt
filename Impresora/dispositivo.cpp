#include "dispositivo.h"

Dispositivo::Dispositivo(QObject *parent) : QObject(parent)
{
    m_nombre = "";
}

Dispositivo::Dispositivo(QString nombre)
{
    m_nombre = nombre;
}

QString Dispositivo::nombre() const
{
    return m_nombre;
}

