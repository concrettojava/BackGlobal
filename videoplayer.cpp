// videoplayer.cpp
#include "videoplayer.h"
#include <QDirIterator>
#include <QDebug>

VideoPlayer::VideoPlayer(QObject *parent) : QObject(parent), m_layout(nullptr), m_currentLayout(0)
{
}

VideoPlayer::~VideoPlayer()
{
    stopAllVideos();

    // 释放资源
    for (auto player : m_players) {
        player->deleteLater();
    }

    for (auto widget : m_videoWidgets) {
        widget->deleteLater();
    }

    m_players.clear();
    m_videoWidgets.clear();
}

void VideoPlayer::initialize(QGridLayout *layout)
{
    m_layout = layout;
}

void VideoPlayer::loadVideoFolder(const QString &folderPath)
{
    QDir directory(folderPath);

    // 设置过滤器，只获取视频文件
    QStringList filters;
    filters << "*.mp4" << "*.avi" << "*.mov" << "*.wmv" << "*.mkv";
    directory.setNameFilters(filters);

    // 获取视频文件列表
    m_videoFiles = directory.entryInfoList(QDir::Files);

    qDebug() << "加载了" << m_videoFiles.size() << "个视频文件";
}

void VideoPlayer::playSingleVideo(int index)
{
    if (m_videoFiles.isEmpty() || index >= m_videoFiles.size()) {
        qDebug() << "没有可播放的视频文件或索引无效";
        return;
    }

    stopAllVideos();
    clearLayout();
    m_currentLayout = 1;

    // 创建单个播放器
    createPlayer(index);

    // 添加到布局
    addPlayerToLayout(m_videoWidgets.last(), 0, 0);

    // 开始播放
    m_players.last()->play();
}

void VideoPlayer::playFirstFourVideos()
{
    if (m_videoFiles.isEmpty()) {
        qDebug() << "没有可播放的视频文件";
        return;
    }

    stopAllVideos();
    clearLayout();
    m_currentLayout = 2;

    // 确定要播放的视频数量（最多4个）
    int count = qMin(4, m_videoFiles.size());

    // 为每个视频创建播放器并添加到布局
    for (int i = 0; i < count; ++i) {
        createPlayer(i);

        // 计算行和列
        int row = i / 2;
        int col = i % 2;

        addPlayerToLayout(m_videoWidgets.last(), row, col);

        // 开始播放
        m_players.last()->play();
    }
}

void VideoPlayer::playAllVideos()
{
    if (m_videoFiles.isEmpty()) {
        qDebug() << "没有可播放的视频文件";
        return;
    }

    stopAllVideos();
    clearLayout();
    m_currentLayout = 3;

    // 计算网格大小
    int count = m_videoFiles.size();
    int gridSize = qCeil(qSqrt(count)); // 向上取整的平方根，确定网格尺寸

    // 为每个视频创建播放器并添加到布局
    for (int i = 0; i < count; ++i) {
        createPlayer(i);

        // 计算行和列
        int row = i / gridSize;
        int col = i % gridSize;

        addPlayerToLayout(m_videoWidgets.last(), row, col);

        // 开始播放
        m_players.last()->play();
    }
}

void VideoPlayer::stopAllVideos()
{
    for (auto player : m_players) {
        player->stop();
    }
}

int VideoPlayer::getVideoCount() const
{
    return m_videoFiles.size();
}

void VideoPlayer::createPlayer(int index)
{
    if (index >= m_videoFiles.size()) {
        return;
    }

    // 创建媒体播放器
    QMediaPlayer *player = new QMediaPlayer(this);

    // 创建视频窗口
    QVideoWidget *videoWidget = new QVideoWidget;
    videoWidget->setAspectRatioMode(Qt::KeepAspectRatio);

    // 设置播放器和视频窗口的关联
    player->setVideoOutput(videoWidget);

    // 设置媒体源
    player->setMedia(QUrl::fromLocalFile(m_videoFiles.at(index).absoluteFilePath()));

    // 添加到列表
    m_players.append(player);
    m_videoWidgets.append(videoWidget);
}

void VideoPlayer::clearLayout()
{
    if (!m_layout) {
        return;
    }

    // 从布局中移除所有项
    while (m_layout->count() > 0) {
        QLayoutItem *item = m_layout->takeAt(0);
        if (item->widget()) {
            item->widget()->hide();
        }
        delete item;
    }

    // 清除播放器和视频窗口
    for (auto player : m_players) {
        player->stop();
        player->deleteLater();
    }

    for (auto widget : m_videoWidgets) {
        widget->deleteLater();
    }

    m_players.clear();
    m_videoWidgets.clear();
}

void VideoPlayer::addPlayerToLayout(QVideoWidget *videoWidget, int row, int col)
{
    if (!m_layout || !videoWidget) {
        return;
    }

    videoWidget->show();
    m_layout->addWidget(videoWidget, row, col);
}
