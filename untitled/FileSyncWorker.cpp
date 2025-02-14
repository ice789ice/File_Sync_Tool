#include "FileSyncWorker.h"
#include <QDebug>
#include <QDir>
#include <filesystem>

namespace fs = std::filesystem;

FileSyncWorker::FileSyncWorker(const QString &srcPath, const QString &dstPath,QProgressBar* progressBar)
    : sourcePath(srcPath), destPath(dstPath),progressBar(progressBar)
{
}

void FileSyncWorker::run() {
    try {
        fs::path sourceDir(sourcePath.toStdString());  // 将 QString 转换为 std::filesystem::path
        fs::path targetDir(destPath.toStdString());

        // 检查源文件夹是否存在
        if (!fs::exists(sourceDir)) {
            emit syncError("源文件夹不存在！");
            return;
        }

        // 遍历源文件夹中的所有文件和文件夹
        int totalFiles = std::distance(fs::recursive_directory_iterator(sourceDir), fs::recursive_directory_iterator{});
        int currentFile = 0;

        for (const auto& entry : fs::recursive_directory_iterator(sourceDir)) {
            const fs::path& sourceFilePath = entry.path();
            fs::path relativePath = fs::relative(sourceFilePath, sourceDir);
            fs::path targetFilePath = targetDir / relativePath;

            // 如果是文件，进行复制
            if (fs::is_regular_file(sourceFilePath)) {
                if (fs::exists(targetFilePath)) {
                    // 如果目标文件较旧，进行文件更新
                    if (fs::last_write_time(sourceFilePath) > fs::last_write_time(targetFilePath)) {
                        fs::copy(sourceFilePath, targetFilePath, fs::copy_options::overwrite_existing);
                    }
                } else {
                    fs::copy(sourceFilePath, targetFilePath);  // 目标文件夹没有文件，直接复制
                }
            }

            // 发射信号更新进度
            emit progressUpdated(100);  // 进度更新，这里根据实际情况可以计算进度
        }

        // 同步完成信号
        emit syncFinished();

    } catch (const std::exception &e) {
        // 捕获并发射错误信号
        emit syncError(e.what());
    }
}
