// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗口标题
    setWindowTitle("多视频播放器");

    // 创建视频播放器
    m_videoPlayer = new VideoPlayer(this);

    // 初始化视频播放器，传递布局
    m_videoPlayer->initialize(ui->gridLayout);

    // 设置视频文件夹路径（这里写死一个路径，实际使用时需要替换为实际路径）
    m_videoFolderPath = "D:\\jezetek\\videos"; // 替换为您的视频文件夹路径

    // 加载视频文件夹
    m_videoPlayer->loadVideoFolder(m_videoFolderPath);

    // 检查是否加载到视频
    int videoCount = m_videoPlayer->getVideoCount();
    if (videoCount > 0) {
        qDebug() << "成功加载" << videoCount << "个视频文件";
        ui->statusbar->showMessage(QString("已加载 %1 个视频文件").arg(videoCount));
    } else {
        qDebug() << "未找到视频文件，请检查路径：" << m_videoFolderPath;
        ui->statusbar->showMessage(QString("未找到视频文件，请检查路径：%1").arg(m_videoFolderPath));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnPlaySingle_clicked()
{
    qDebug() << "播放单个视频";
    m_videoPlayer->playSingleVideo();
    ui->statusbar->showMessage("正在播放单个视频");
}

void MainWindow::on_btnPlayFour_clicked()
{
    qDebug() << "播放前四个视频";
    m_videoPlayer->playFirstFourVideos();
    ui->statusbar->showMessage("正在播放前四个视频");
}

void MainWindow::on_btnPlayAll_clicked()
{
    qDebug() << "播放所有视频";
    m_videoPlayer->playAllVideos();
    ui->statusbar->showMessage("正在播放所有视频");
}
