#include "blackholeview.h"

BlackHoleView::BlackHoleView(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Black Hole");
    setFixedSize(sizeHint());

    m_saveGame_ = nullptr;

    m_markedTableButton_ = nullptr;

    m_actualPlayerLayout_ = new QHBoxLayout();
    m_actualPlayerLabel_ = new QLabel("Actual player: ");
    m_actualPlayerButton_ = new QPushButton();
    m_actualPlayerButton_->setEnabled(false);
    m_actualPlayerButton_->setFixedSize(20, 20);
    m_actualPlayerLayout_->addWidget(m_actualPlayerLabel_);
    m_actualPlayerLayout_->addWidget(m_actualPlayerButton_);

    m_tablePushButtonsLayout_ = new QGridLayout();
    m_tablePushButtonsLayout_->setContentsMargins(0, 0, 0, 0);
    m_tablePushButtonsLayout_->setSpacing(0);

    m_sizePushButtonsLayout_ = new QHBoxLayout();
    m_sizePushButton5_ = new QPushButton("5x5");
    m_sizePushButton7_ = new QPushButton("7x7");
    m_sizePushButton9_ = new QPushButton("9x9");
    m_sizePushButtonsLayout_->addWidget(m_sizePushButton5_);
    m_sizePushButtonsLayout_->addWidget(m_sizePushButton7_);
    m_sizePushButtonsLayout_->addWidget(m_sizePushButton9_);

    connect(m_sizePushButton5_, SIGNAL(clicked()),
            this, SLOT(sizeButtonClicked()));
    connect(m_sizePushButton7_, SIGNAL(clicked()),
            this, SLOT(sizeButtonClicked()));
    connect(m_sizePushButton9_, SIGNAL(clicked()),
            this, SLOT(sizeButtonClicked()));

    m_mainLayout_ = new QVBoxLayout();
    m_mainLayout_->addLayout(m_actualPlayerLayout_);
    m_mainLayout_->addLayout(m_tablePushButtonsLayout_);
    m_mainLayout_->addLayout(m_sizePushButtonsLayout_);

    setLayout(m_mainLayout_);

    connect(&m_blackHoleGameModel_, SIGNAL(gameOver(int)),
            this, SLOT(gameOver(int)));

    int l_tableSize = m_blackHoleGameModel_.getTableSize();
    newGame(l_tableSize);
}

BlackHoleView::~BlackHoleView()
{
    if (nullptr != m_saveGame_) delete m_saveGame_;
}

void BlackHoleView::newGame(int f_tableSize)
{
    m_markedTableButton_ = nullptr;
    m_blackHoleGameModel_.newGame(f_tableSize);
    refreshActualPlayer();
    initTable();
    refreshTable();
}

void BlackHoleView::initTable()
{
    for (QVector<QPushButton*> l_row : m_tablePushButtons_)
    {
        for (QPushButton* l_actTableButton : l_row)
        {
            m_tablePushButtonsLayout_->removeWidget(l_actTableButton);
            delete l_actTableButton;
        }
        l_row.clear();
    }

    int l_tableSize = m_blackHoleGameModel_.getTableSize();
    m_tablePushButtons_.resize(l_tableSize);
    for (int i = 0; i < l_tableSize; ++i)
    {
        m_tablePushButtons_[i].resize(l_tableSize);
        for (int j = 0; j < l_tableSize; ++j)
        {
            m_tablePushButtons_[i][j] = new QPushButton();
            m_tablePushButtons_[i][j]->setFixedSize(50, 50);
            m_tablePushButtons_[i][j]->setEnabled(false);
            m_tablePushButtonsLayout_->addWidget(m_tablePushButtons_[i][j], i, j);

            connect(m_tablePushButtons_[i][j], SIGNAL(clicked()),
                    this, SLOT(tableButtonClicked()));
        }
    }
}

void BlackHoleView::refreshTable()
{
    int l_actualPlayer = m_blackHoleGameModel_.getActualPlayerValue();
    int l_tableSize = m_blackHoleGameModel_.getTableSize();
    for (int i = 0; i < l_tableSize; ++i)
    {
        for (int j = 0; j < l_tableSize; ++j)
        {
            int l_actTableValue = m_blackHoleGameModel_.getTableValue(i, j);
            if(l_actualPlayer == l_actTableValue)
            {
                m_tablePushButtons_[i][j]->setEnabled(true);
            }
            else
            {
                m_tablePushButtons_[i][j]->setEnabled(false);
            }
            QString l_color = "";
            switch(l_actTableValue)
            {
            case 1:
                l_color = "red";
                break;
            case 2:
                l_color = "blue";
                break;
            case 42:
                l_color = "black";
                break;
            }
            m_tablePushButtons_[i][j]->setStyleSheet("background-color: " + l_color);
        }
    }
}

void BlackHoleView::refreshActualPlayer()
{
    int l_actualPlayer = m_blackHoleGameModel_.getActualPlayerValue();
    QString l_color = 1 == l_actualPlayer
                    ? "red"
                    : "blue";
    m_actualPlayerButton_->setStyleSheet("background-color: " + l_color);
}

void BlackHoleView::markTableButton(QPushButton* f_senderButton)
{
    int l_player = m_blackHoleGameModel_.getActualPlayerValue();
    QString l_color = l_player == 1
                    ? "red"
                    : "blue";
    if (nullptr != m_markedTableButton_)
    {
        m_markedTableButton_->setStyleSheet("background-color: " + l_color);
    }

    if (f_senderButton == m_markedTableButton_)
    {
        m_markedTableButton_ = nullptr;
    }
    else
    {
        m_markedTableButton_ = f_senderButton;
        m_markedTableButton_->setStyleSheet("background-color: " + l_color + ";"
                                            "border-style: outset;"
                                            "border-width: 2px;"
                                            "border-color: black;");
    }
}

void BlackHoleView::keyPressEvent(QKeyEvent* f_event)
{
    if (nullptr == m_markedTableButton_)
    {
        return;
    }

    int l_location = m_tablePushButtonsLayout_->indexOf(m_markedTableButton_);
    int l_tableSize = m_blackHoleGameModel_.getTableSize();
    int l_xCoord = l_location / l_tableSize;
    int l_yCoord = l_location % l_tableSize;
    switch(f_event->key())
    {
    case Qt::Key_W:
        m_blackHoleGameModel_.makeTurn(l_xCoord, l_yCoord, -1, 0);
        break;
    case Qt::Key_S:
        m_blackHoleGameModel_.makeTurn(l_xCoord, l_yCoord, 1, 0);
        break;
    case Qt::Key_A:
        m_blackHoleGameModel_.makeTurn(l_xCoord, l_yCoord, 0, -1);
        break;
    case Qt::Key_D:
        m_blackHoleGameModel_.makeTurn(l_xCoord, l_yCoord, 0, 1);
        break;
    }
    m_markedTableButton_ = nullptr;
    refreshActualPlayer();
    refreshTable();
}

// slot
void BlackHoleView::sizeButtonClicked()
{
    QPushButton* l_senderButton = dynamic_cast<QPushButton*>(sender());
    QString l_sizeButtonText = l_senderButton->text();
    int l_tableSize = 0;
    if ("5x5" == l_sizeButtonText)
    {
        l_tableSize = 5;
    }
    else if ("7x7" == l_sizeButtonText)
    {
        l_tableSize = 7;
    }
    else if ("9x9" == l_sizeButtonText)
    {
        l_tableSize = 9;
    }
    newGame(l_tableSize);
}

void BlackHoleView::tableButtonClicked()
{
    QPushButton* l_senderButton = dynamic_cast<QPushButton*>(sender());
    markTableButton(l_senderButton);
}

void BlackHoleView::gameOver(int f_player)
{
    QString l_color = 1 == f_player
                    ? "RED"
                    : "BLUE";
    QString l_message = "The winner player is: " + l_color;
    int l_prevTableSize = m_blackHoleGameModel_.getTableSize();
    QMessageBox::information(this, QString("Game Over"), l_message);
    newGame(l_prevTableSize);
}
