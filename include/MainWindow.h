#ifndef MAINWINDOW_H

#define MAINWINDOW_H


#include <QMainWindow>

#include <vtkSmartPointer.h>

#include <vtkPolyDataMapper.h>

#include <vtkActor.h>

#include <vtkRenderer.h>

#include <vtkRenderWindow.h>

#include <vtkDICOMImageReader.h>

#include <vtkImageViewer2.h>

namespace Ui {

class MainWindow;

}


class MainWindow : public QMainWindow

{

    Q_OBJECT

    

public:

    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    

private slots:

    void openDCMFolder();

    void drawDCMSeries(std::string folderDCM);


    void on_btnOpenDCMFolder_clicked();


    void on_hSliderDCM_sliderMoved(int position);


private:

    Ui::MainWindow *ui;

    vtkSmartPointer<vtkDICOMImageReader> readerDCMSeries;

    vtkSmartPointer<vtkImageViewer2> imageViewerDCMSeriesX;

    int mMinSliderX;

    int mMaxSliderX;

};


#endif // MAINWINDOW_H

