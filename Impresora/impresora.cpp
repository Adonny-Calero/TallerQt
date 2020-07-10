#include "impresora.h"
#include "ui_impresora.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>


impresora::impresora(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::impresora)
{
    ui->setupUi(this);
    inicializarDatos();
    connect(ui->cmdAnadir, SIGNAL(clicked(bool)),this,SLOT(agregarDis()));
    connect(ui->mnuAcercade,SIGNAL(triggered(bool)),this,SLOT(info()));
    connect(ui->mnuAbrir,SIGNAL(triggered(bool)),this,SLOT(abrir()));
    connect(ui->mnuSalir,SIGNAL(triggered(bool)),this,SLOT(close()));
}

impresora::~impresora()
{
    delete ui;
}

void impresora::guardar()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Guardar datos",QDir::home().absolutePath(), "Archivo de texto (*.txt)");
    QFile data(fileName);

    if(data.open(QFile::WriteOnly | QFile::Truncate)){

       QTextStream salida(&data);
       salida << ui->outDetalle;
       ui->statusbar->showMessage("Datos almacenados en"+fileName,5000);
    }
    data.close();
}

void impresora::info()
{
    QMessageBox::information(this,"acerca de","Inventario de Impresoras\n Desarrollador: Adonny Mateo Calero Arguello\n Ultima actualización: Juev,09,Jul,2020\n Iconos diseñados por <a href=https://www.flaticon.es/autores/monkik title=monkik>monkik</a> from <a href=https://www.flaticon.es/ title=Flaticon> www.flaticon.es</a>");
}

void impresora::abrir()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Abrir datos",QDir::home().absolutePath(), "Archivo de texto (*.txt)");
    QFile data(fileName);

    if(!fileName.isEmpty()){
        QFile file(fileName);
        if(file.open(QFile::ReadOnly)){
            //ui->outDetalle->setPlainText(file.readAll());
        }
    }

    data.close();

}

void impresora::inicializarDatos()
{
    Dispositivo p("Ricoh");
    //Creamos impresoras quemadas
    m_dispositivos.append(new Dispositivo("Ricoh"));
    m_dispositivos.append(new Dispositivo("Xerox"));
    m_dispositivos.append(new Dispositivo("Lexmark"));
    m_dispositivos.append(new Dispositivo("Kyocera"));

    mostrarDatos();
}

void impresora::mostrarDatos()
{
    for(int i=0; i< m_dispositivos.length(); i++){
        ui->inMarca->addItem(m_dispositivos.at(i)->nombre());
    }

    QStringList cabecera = {"Marca","Modelo","Serie","Tipo","Contador","Precio"};
    ui->outDetalle->setColumnCount(6);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);


}

void impresora::anadir()
{
    QString modelo = ui->inModelo->text();
    QString serie = ui->inSerie->text();
    QString contador = ui->inMarcador->text();
    QString precio = ui->inPrecio->text();
    if (modelo == "" && serie == 0){
        ui->statusbar->showMessage("No se ha ingresado datos",2000);
    }
    if (precio == 0){
        ui->statusbar->showMessage("No se ha ingresado datos",2000);
    }
    if(contador ==0){
        ui->statusbar->showMessage("No se ha ingresado datos",2000);
    }

}

void impresora::limpiar()
{
    ui->inModelo->setText("");
    ui->inSerie->setValue(0);
    ui->inBN->setChecked(true);
    ui->inMarcador->setValue(0);
    ui->inPrecio->setValue(0);


}

void impresora::agregarDis()
{
    int index = ui->inMarca ->currentIndex();
    Dispositivo *d =m_dispositivos.at(index);
    QString modelo = ui->inModelo->text();
    QString serie = ui->inSerie->text();
    QString contador = ui->inMarcador->text();
    QString precio = ui->inPrecio->text();
    QString tipo;
    if(ui->inBN->isChecked()){
        tipo="Blanco y negro";
    }else if(ui->inColor->isChecked()){
        tipo="Color";
    }

    //Agregamos datos a la tabla
    int posicion = ui->outDetalle->rowCount();


    ui->outDetalle->insertRow(posicion);
    ui->outDetalle->setItem(posicion,0,new QTableWidgetItem(d->nombre()));
    ui->outDetalle->setItem(posicion,1,new QTableWidgetItem(modelo));
    ui->outDetalle->setItem(posicion,2,new QTableWidgetItem(serie));
    ui->outDetalle->setItem(posicion,3,new QTableWidgetItem(tipo));
    ui->outDetalle->setItem(posicion,4,new QTableWidgetItem(contador));
    ui->outDetalle->setItem(posicion,5,new QTableWidgetItem(precio));

    if (modelo == ""){
        ui->statusbar->showMessage("No se ha ingresado datos",2000);
    }

    limpiar();
}



