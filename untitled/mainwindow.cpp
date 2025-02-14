#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QProgressBar>
#include <filesystem>
#include "FileSyncWorker.h"  // 引入 FileSyncWorker 类

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)  // 确保 ui 被正确初始化
{
    ui->setupUi(this);
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建 QVBoxLayout
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // 创建控件
    QLabel *sourceLabel = new QLabel(tr("源文件夹:" ),this);
    sourceLineEdit = new QLineEdit(this);
    QPushButton *sourceButton = new QPushButton(tr("选择源文件夹"), this);

    QLabel *destLabel = new QLabel(tr("目标文件夹:"), this);
    destLineEdit = new QLineEdit(this);
    QPushButton *destButton = new QPushButton(tr("选择目标文件夹"), this);

    progressBar = new QProgressBar(this);  // 创建进度条
    progressBar->setRange(0, 100);  // 设置进度条范围
    progressBar->setValue(0);       // 初始化进度条为 0

    QPushButton *syncButton = new QPushButton(tr("开始同步"), this);

    // 将控件添加到布局
    layout->addWidget(sourceLabel);
    layout->addWidget(sourceLineEdit);
    layout->addWidget(sourceButton);
    layout->addWidget(destLabel);
    layout->addWidget(destLineEdit);
    layout->addWidget(destButton);
    layout->addWidget(syncButton);
    layout->addWidget(progressBar);  // 将进度条添加到布局中

    // 连接信号和槽
    connect(sourceButton, &QPushButton::clicked, this, &MainWindow::selectSourceFolder);
    connect(destButton, &QPushButton::clicked, this, &MainWindow::selectDestFolder);
    connect(syncButton, &QPushButton::clicked, this, &MainWindow::startSync);

    qDebug() << tr( "setupUi 完成");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectSourceFolder() {
    QString folder = QFileDialog::getExistingDirectory(this,tr( "选择源文件夹"));
    if (!folder.isEmpty()) {
        sourceLineEdit->setText(folder);
    }
}

void MainWindow::selectDestFolder() {
    QString folder = QFileDialog::getExistingDirectory(this, tr("选择目标文件夹"));
    if (!folder.isEmpty()) {
        destLineEdit->setText(folder);
    }
}

void MainWindow::startSync() {
    QString srcPath = sourceLineEdit->text();  // 获取源文件夹路径
    QString dstPath = destLineEdit->text();   // 获取目标文件夹路径

    // 检查路径是否为空
    if (srcPath.isEmpty() || dstPath.isEmpty()) {
        QMessageBox::warning(this,tr( "错误"),tr( "请先选择文件夹"));
        return;
    }

    // 创建并启动 FileSyncWorker 线程，传递进度条
    FileSyncWorker *worker = new FileSyncWorker(srcPath, dstPath, progressBar);
    connect(worker, &FileSyncWorker::progressUpdated, this, &MainWindow::onProgressUpdated);
    connect(worker, &FileSyncWorker::syncFinished, this, &MainWindow::onSyncFinished);
    connect(worker, &FileSyncWorker::syncError, this, &MainWindow::onSyncError);

    worker->start();  // 启动线程
}

// 更新进度条
void MainWindow::onProgressUpdated(int progress) {
    progressBar->setValue(progress);  // 更新进度条
}

// 同步完成
void MainWindow::onSyncFinished() {
    QMessageBox::information(this, tr("同步完成"),tr("文件同步完成！"));
}

// 错误处理
void MainWindow::onSyncError(const QString &error) {
    QMessageBox::critical(this,tr( "错误"), error);
}
