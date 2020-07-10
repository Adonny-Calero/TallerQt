#ifndef IMPRESORA_H
#define IMPRESORA_H

#include <QMainWindow>

#include "dispositivo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class impresora; }
QT_END_NAMESPACE

class impresora : public QMainWindow
{
    Q_OBJECT

public:
    impresora(QWidget *parent = nullptr);
    ~impresora();
    void guardar();




private:
    Ui::impresora *ui;
    QList<Dispositivo*> m_dispositivos;
    void inicializarDatos();
    void mostrarDatos();
    void anadir();
    void limpiar();
public slots:
    void agregarDis();
    void info();
    void abrir();

};
#endif // IMPRESORA_H
