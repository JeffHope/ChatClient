#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H
#include <QMenu>
#include <QtWidgets>
#include <QTextEdit>
#include <QAction>

class contextMenu : public QTextEdit {
    Q_OBJECT

private:
    QMenu *m_pmenu;
protected:
    virtual void contextMenuEvent(QContextMenuEvent *e) override{
        m_pmenu->exec(e->globalPos());
    }
public:
    contextMenu(QWidget* pwgt = nullptr) : QTextEdit(pwgt) {
        setReadOnly(true);
        m_pmenu = new QMenu (this);
        m_pmenu->addAction("Войти в группу");
        m_pmenu->addAction("Покинуть группу");
        m_pmenu->addAction("Удалить группу");
    }
public slots:
    void groupsMenu(QAction* action){

    }


};

#endif // CONTEXTMENU_H
