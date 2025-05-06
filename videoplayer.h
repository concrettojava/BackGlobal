// videoplayer.h
#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileInfoList>
#include <QDir>
#include <QGridLayout>
#include <QtMath>

class VideoPlayer : public QObject
{
    Q_OBJECT
public:
    explicit VideoPlayer(QObject *parent = nullptr);
    ~VideoPlayer();

    // 初始化播放器
    void initialize(QGridLayout *layout);

    // 加载视频文件夹
    void loadVideoFolder(const QString &folderPath);

    // 播放单个视频（默认第一个）
    void playSingleVideo(int index = 0);

    // 以网格布局播放前四个视频
    void playFirstFourVideos();

    // 播放所有视频
    void playAllVideos();

    // 停止所有视频播放
    void stopAllVideos();

    // 获取视频文件数量
    int getVideoCount() const;

private:
    // 创建视频播放器和视频窗口
    void createPlayer(int index);

    // 清除布局
    void clearLayout();

    // 添加播放器到布局
    void addPlayerToLayout(QVideoWidget *videoWidget, int row, int col);

    QGridLayout *m_layout;                   // 网格布局
    QList<QMediaPlayer*> m_players;          // 媒体播放器列表
    QList<QVideoWidget*> m_videoWidgets;     // 视频窗口列表
    QFileInfoList m_videoFiles;              // 视频文件列表
    int m_currentLayout;                     // 当前布局类型
};

#endif // VIDEOPLAYER_H
