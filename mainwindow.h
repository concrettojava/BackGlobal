// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videoplayer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 播放单个视频按钮点击事件
    void on_btnPlaySingle_clicked();

    // 播放前四个视频按钮点击事件
    void on_btnPlayFour_clicked();

    // 播放所有视频按钮点击事件
    void on_btnPlayAll_clicked();

private:
    Ui::MainWindow *ui;
    VideoPlayer *m_videoPlayer;   // 视频播放器
    QString m_videoFolderPath;    // 视频文件夹路径
};
#endif // MAINWINDOW_H
