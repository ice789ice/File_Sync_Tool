#ifndef FILESYNCWORKER_H
#define FILESYNCWORKER_H

#include <QThread>
#include <QDir>
#include <QFileInfoList>
#include <QFile>
#include <QDebug>
#include <QProgressBar>
#include <QString>

namespace fs = std::filesystem;

class FileSyncWorker : public QThread {
    Q_OBJECT // 必须包含 Q_OBJECT 宏

public:
    FileSyncWorker(const QString &srcPath,const QString &dstPath,QProgressBar* progressBar); // 构造函数，接收源文件夹和目标文件夹路径

    //重写QThread 的run()函数，执行文件同步
    void run() override;
signals:
    void progressUpdated(int progress); // 更新进度的信号
    void syncFinished(); // 同步完成的信号
    void syncError(const QString &error); // 错误信息信号



private:
    QString sourcePath;//源文件夹路径
    QString destPath;//目标文件夹路径
    QProgressBar* progressBar;//进度条指针
};

#endif // FILESYNCWORKER_H
