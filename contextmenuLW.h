#pragma once
#include <QMenu>
#include <QAction>
#include <QTextEdit>
#include <QtWidgets>

class ContextMenu : public QTextEdit {
    Q_OBJECT

public slots:

    void slotActivated(QAction* action){
        QString strColor =  action->text().remove("&");
        setHtml(QString("<BODY BGCOLOR=%1></BODY>").arg(strColor));
    }

private:
        QMenu * m_pmu;

protected:

    virtual void contextMenuEvent(QContextMenuEvent * pe){
        m_pmu->exec(pe->globalPos());
    }

public:

    ContextMenu(QWidget* pwgt = nullptr) : QTextEdit (pwgt) {
        setReadOnly(true);
        m_pmu = new QMenu (this);

        m_pmu->addAction("Войти в группу");
        m_pmu->addAction("Выйти из группы");
        m_pmu->addAction("Удалить группу");
        connect(m_pmu, SIGNAL(triggered(QAction*)), SLOT(slotActivated(QAction*)));

    }

};
