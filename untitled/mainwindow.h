#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QProgressBar>
#include "FileSyncWorker.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void selectSourceFolder();//源文件夹选择槽
    void selectDestFolder();//目标文件夹选择槽
    void startSync();       //同步按钮触发的槽
    void onProgressUpdated(int progress);//进度更新槽
    void onSyncFinished();//同步完成槽
    void onSyncError(const QString &error);//错误槽

private:
    Ui::MainWindow *ui;
    QLineEdit *sourceLineEdit; // 源文件夹路径输入框
    QLineEdit *destLineEdit;   // 目标文件夹路径输入框
    QProgressBar *progressBar; //进度条
};

#endif // MAINWINDOW_H
