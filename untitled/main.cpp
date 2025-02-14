#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug> // 添加 QDebug 头文件，用于调试输出
#include <QMessageBox> // 添加 QMessageBox 头文件，用于显示消息框

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // 获取系统语言设置
    QLocale locale = QLocale::system();
    QString lang = locale.name();

    // 加载翻译文件
    QTranslator translator;
    bool loaded = false; // 添加一个变量来跟踪加载是否成功

    if (lang == "en_US") { // 这里判断英文
        loaded = translator.load("untitled_en.qm");
        if (!loaded) {
            qDebug() << "Failed to load untitled_en.qm"; // 输出调试信息
            QMessageBox::critical(nullptr, "Error", "Failed to load untitled_en.qm"); // 显示错误消息框
            // 可以选择使用默认语言或采取其他处理方式
        }
    } else if (lang == "zh_CN") { // 这里判断中文
        loaded = translator.load("untitled_zh_CN.qm");
        if (!loaded) {
            qDebug() << "Failed to load untitled_zh_CN.qm"; // 输出调试信息
            QMessageBox::critical(nullptr, "Error", "Failed to load untitled_zh_CN.qm"); // 显示错误消息框
            // 可以选择使用默认语言或采取其他处理方式
        }
    }

    if (loaded) { // 只在翻译文件加载成功后才安装翻译器
        a.installTranslator(&translator);
    } else {
        qDebug() << "No translation file loaded. Using default language."; // 输出调试信息
        QMessageBox::warning(nullptr, "Warning", "No translation file loaded. Using default language."); // 显示警告消息框
    }

    MainWindow w; // 创建 MainWindow 实例
    w.show(); // 显示窗口
    return a.exec(); // 启动事件循环
}
