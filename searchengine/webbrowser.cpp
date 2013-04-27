#include "webbrowser.h"
#include <QLayout>
#include <QToolButton>
#include <QLineEdit>
#include <QWebView>
#include <QSplitter>
#include <QListView>
#include <QStringListModel>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElementCollection>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

WebBrowser::WebBrowser(QWidget *parent) :
    QWidget(parent)
{
    addressBar = new QLineEdit(this);
    backButton = new QToolButton(this);
    forwardButton = new QToolButton(this);
    reloadButton = new QToolButton(this);

    backButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    forwardButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    reloadButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    connect(addressBar, SIGNAL(returnPressed()), this, SLOT(loadPage()));

    QHBoxLayout *toolsLayout = new QHBoxLayout;
    toolsLayout->addWidget(backButton);
    toolsLayout->addWidget(forwardButton);
    toolsLayout->addWidget(reloadButton);
    toolsLayout->addWidget(addressBar);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(toolsLayout);

    browser = new QWebView(this);
//    connect(browser, SIGNAL(urlChanged(QUrl)), this, SLOT(updateAddressBar(QUrl)));


    imageList = new QListView;

    QSplitter *splitter = new QSplitter;
    splitter->addWidget(browser);

    mainLayout->addWidget(splitter);

    backButton->setDefaultAction(browser->pageAction(QWebPage::Back));
    forwardButton->setDefaultAction(browser->pageAction(QWebPage::Forward));
    reloadButton->setDefaultAction(browser->pageAction(QWebPage::Reload));
}

void WebBrowser::loadPage() {
    QString word = addressBar->text();
    emit searchFor(word);
}

void WebBrowser::updateAddressBar(const QUrl &url) {
    addressBar->setText(url.toString());
}

void WebBrowser::showPage(const QByteArray &content) {
        QUrl u = QUrl::fromUserInput(addressBar->text());
        browser->setHtml(content, u);
}

int WebBrowser::getNextUrl(const QByteArray &content, QUrl *u) {
    int start_link;
    u->clear();
    if ((start_link = content.indexOf("<a href=")) < 0)
        return -1;

    int start_quote = content.indexOf('"', start_link);
    int end_quote = content.indexOf('"', ++start_quote);
    u->setUrl(content.mid(start_quote, end_quote - start_quote));
    return end_quote;
}

void 
WebBrowser::readyToSearch()
{
}
