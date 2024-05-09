#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkInteractorStyleImage.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    readerDCMSeries = vtkSmartPointer<vtkDICOMImageReader>::New();
    imageViewerDCMSeriesX = vtkSmartPointer<vtkImageViewer2>::New();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::openDCMFolder()
{
    QString folderNameDCM = QFileDialog::getExistingDirectory(this,tr("Open DCM Folder"),QDir::currentPath(),QFileDialog::ShowDirsOnly);
    std::string stdstrFolderNameDCM = folderNameDCM.toUtf8().constData();
    drawDCMSeries(stdstrFolderNameDCM);
}

void MainWindow::drawDCMSeries(std::string folderDCM)
{
    readerDCMSeries->SetDirectoryName(folderDCM.c_str());
    readerDCMSeries->Update();
    imageViewerDCMSeriesX->SetInputConnection(readerDCMSeries->GetOutputPort());
    mMinSliderX = imageViewerDCMSeriesX->GetSliceMin();
    mMaxSliderX = imageViewerDCMSeriesX->GetSliceMax();
    ui->hSliderDCM->setMinimum(mMinSliderX);
    ui->hSliderDCM->setMaximum(mMaxSliderX);
    imageViewerDCMSeriesX->SetRenderWindow(ui->vtkRenderer->GetRenderWindow());
}

void MainWindow::on_btnOpenDCMFolder_clicked()
{
    openDCMFolder();
}

void MainWindow::on_hSliderDCM_sliderMoved(int position)
{
    imageViewerDCMSeriesX->SetSlice(position);
    imageViewerDCMSeriesX->Render();
}