#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QWidget>
#include <QUrl>

class QLineEdit;
class QToolButton;
class QWebView;
class QListView;
class QNetworkReply;
class QNetworkAccessManager;

class WebBrowser : public QWidget
{
    Q_OBJECT
public:
    WebBrowser(QWidget *parent = 0);

signals:
    void searchFor(const QString &);

public slots:
    void loadPage();
    void updateAddressBar(const QUrl &url);
    void readyToSearch();
    void showPage(const QByteArray &content);

private slots:
    int getNextUrl(const QByteArray &content, QUrl *u);
    
private:
    QLineEdit *addressBar;
    QToolButton *backButton;
    QToolButton *forwardButton;
    QToolButton *reloadButton;

    QWebView *browser;
    QListView *imageList;
};

#endif // WEBBROWSER_H
