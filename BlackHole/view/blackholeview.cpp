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

    m_gameStateControlLayout_ = new QHBoxLayout();
    m_savePushButton_ = new QPushButton("Save game");
    m_gameStateControlLayout_->addWidget(m_savePushButton_);

    connect(m_savePushButton_, SIGNAL(clicked()),
            this, SLOT(saveButtonClicked()));

    m_mainLayout_ = new QVBoxLayout();
    m_mainLayout_->addLayout(m_actualPlayerLayout_);
    m_mainLayout_->addLayout(m_tablePushButtonsLayout_);
    m_mainLayout_->addLayout(m_sizePushButtonsLayout_);
    m_mainLayout_->addLayout(m_gameStateControlLayout_);

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
    m_tablePushButtons_[l_tableSize/2][l_tableSize/2]->setEnabled(true);
    m_blackHoleButtonMovie_ = new QMovie(":assets/images/black_hole.gif");
    connect(m_blackHoleButtonMovie_, SIGNAL(frameChanged(int)),
            this, SLOT(setBlackHoleButtonIcon(int)));
    if (m_blackHoleButtonMovie_->loopCount() != -1)
    {
        connect(m_blackHoleButtonMovie_, SIGNAL(finished()),
                m_blackHoleButtonMovie_, SLOT(start()));
    }
    m_blackHoleButtonMovie_->start();
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
            QString l_color = "black";
            QString l_imagePath = "";
            switch(l_actTableValue)
            {
            case 1:
                l_imagePath = ":assets/images/player1.png";
                break;
            case 2:
                l_imagePath = ":assets/images/player2.png";
                break;
            }
            m_tablePushButtons_[i][j]->setStyleSheet("background-color: " + l_color);
            m_tablePushButtons_[i][j]->setIcon(QIcon(l_imagePath));
            m_tablePushButtons_[i][j]->setIconSize(QSize(50, 50));
        }
    }
    m_tablePushButtons_[l_tableSize/2][l_tableSize/2]->setEnabled(true);
}

void BlackHoleView::refreshActualPlayer()
{
    int l_actualPlayer = m_blackHoleGameModel_.getActualPlayerValue();
    QString l_imagePath = 1 == l_actualPlayer
                    ? ":assets/images/player1.png"
                    : ":assets/images/player2.png";
    m_actualPlayerButton_->setIcon(QIcon(l_imagePath));
    m_actualPlayerButton_->setIconSize(QSize(20, 20));
}

void BlackHoleView::markTableButton(QPushButton* f_senderButton)
{
    int l_player = m_blackHoleGameModel_.getActualPlayerValue();
    QString l_imagepath = l_player == 1
                        ? ":assets/images/player1"
                        : ":assets/images/player2";
    if (nullptr != m_markedTableButton_)
    {
        m_markedTableButton_->setIcon(QIcon(l_imagepath + ".png"));
        m_markedTableButton_->setIconSize(QSize(50, 50));
    }

    if (f_senderButton == m_markedTableButton_)
    {
        m_markedTableButton_ = nullptr;
    }
    else
    {
        m_markedTableButton_ = f_senderButton;
        m_markedTableButton_->setIcon(QIcon(l_imagepath + "_targeted.png"));
        m_markedTableButton_->setIconSize(QSize(50, 50));
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
void BlackHoleView::setBlackHoleButtonIcon(int f_frame)
{
    int l_tableSize = m_blackHoleGameModel_.getTableSize();
    QPushButton* l_blackHoleButton = m_tablePushButtons_[l_tableSize/2][l_tableSize/2];
    l_blackHoleButton->setIcon(QIcon(m_blackHoleButtonMovie_->currentPixmap()));
    l_blackHoleButton->setIconSize(QSize(50, 50));
}

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
    int l_tableSize = m_blackHoleGameModel_.getTableSize();
    if (l_senderButton == m_tablePushButtons_[l_tableSize/2][l_tableSize/2])
    {
        return;
    }
    markTableButton(l_senderButton);
}

void BlackHoleView::gameOver(int f_player)
{
    QString l_color = 1 == f_player
                    ? "BLUE"
                    : "RED";
    QString l_message = "The winner player is: " + l_color;
    int l_prevTableSize = m_blackHoleGameModel_.getTableSize();
    QMessageBox::information(this, QString("Game Over"), l_message);
    newGame(l_prevTableSize);
}

void BlackHoleView::saveButtonClicked()
{
    if (nullptr == m_saveGame_)
    {
        m_saveGame_ = new SaveGame();
        connect(m_saveGame_, SIGNAL(accepted()),
                this, SLOT(saveGame()));
    }
    m_saveGame_->setGameList(m_blackHoleGameModel_.getSavedGameList());
    m_saveGame_->open();
}

void BlackHoleView::saveGame()
{
    if (m_blackHoleGameModel_.saveGame(m_saveGame_->getSelectedGame()))
    {
        refreshTable();
        QMessageBox::information(this, "BlackHole", "Save was successfull!");
    }
    else
    {
        QMessageBox::warning(this, "BlackHole", "Can't save!");
    }
}
