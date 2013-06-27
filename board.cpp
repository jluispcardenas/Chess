#include "board.h"
#include "mainboard.h"
#include "boardevaluator.h"

const char Board::ids[6] = {'k', 'q', 'b', 'n', 'r', 'p' };
char Board::_board[8][8];
pieceColor Board::_mainColor;

Q_DECLARE_METATYPE(move_t);

Board::Board(QWidget *parent) : QWidget(parent), _attach(false)
{
    resize(600, 600);
    setMinimumSize(size());
    setAcceptDrops(true);

    lightTile = new QPixmap(":/images/lightTile.png");
    darkTile = new QPixmap(":/images/darkTile.png");

    mode(HUMAN_HUMAN);
    mainColor(WHITE);

    computer = new Computer(this);

    restart();
}

void Board::restart()
{
    //
    whites = true;
    for (int i = 0; i < 64; i++)
        Board::_board[(i/8)][(i%8)] = '\0';
    QHash<int, Piece*>::iterator i = _pieces.begin();
     while (i != _pieces.end()) {
         _pieces[(i++).key()]->hide();
     }
     _pieces.clear();

    gameOver(false);

    bool swhite = mainColor() == BLACK;
    for (int r = 0; r < 8; r++)
    {
        if (r == 6) swhite = !swhite;
        for (int c = 0; c < 8; c++)
        {
            //
            pieceType type = UNKNOWN;
            if (r == 0 || r == 7)
            {
                type = KING;
                switch (c)
                {
                    case 0:
                    case 7:
                        type = ROOK;
                        break;
                    case 1:
                    case 6:
                        type = KNIGHT;
                        break;
                    case 2:
                    case 5:
                        type = BISHOP;
                        break;
                    default:
                        if (c == (mainColor() == WHITE ? 3 : 4))
                            type = QUEEN;
                        break;
                }
            }
            else if (r == 1 || r == 6)
            {
                type = PAWN;
            }

            if (type != UNKNOWN)
            {
                Piece *p = new Piece(type, (swhite ? WHITE : BLACK), c, r, this);
                save(c, r, p);
            }
        }
    }

    if (!_attach && mode() == HUMAN_COMPUTER)
    {
       // qRegisterMetaType<move_t>("move_t");
         //   connect(computer, SIGNAL(moveReady(move_t)), this, SLOT(onMoveReady(move_t)));
        _attach = true;
    }
}

void Board::paintEvent(QPaintEvent *e)
{
        QPainter *p;
        QWidget::paintEvent(e);
        p = new QPainter(this);
        p->setPen(Qt::black);

        drawBoard(p);

        delete p;
}

void Board::drawBoard(QPainter *p)
{
    QPixmap *qp = darkTile;
    int w = darkTile->height();
    for (int r = 0; r < 8; r++)
    {
        qp = ((r%2) == 0) ? lightTile : darkTile;
        for (int c = 0; c < 8; c++)
        {
            p->drawPixmap(c*w, r*w, *qp);
            qp = (qp == darkTile) ? lightTile : darkTile;
        }
    }
}

pieceColor Board::mainColor(pieceColor c)
{
    if (c != NONE)
        _mainColor = c;
    return _mainColor;
}

gameMode Board::mode(gameMode mode)
{
    return this->_gameMode = mode;
}

gameMode Board::mode()
{
    return this->_gameMode;
}

bool Board::gameOver(int g)
{
    if (g != -1)
        this->_gameOver = (bool)g;
    return this->_gameOver;
}

bool Board::myTurn(pieceColor color)
{
    int whites = this->whites ? 0 : 1;
    return ((whites - (int)color) == 0);
}

bool Board::myTurn()
{
    return myTurn(mainColor());
}

void Board::makeMove(int ac, int ar, int bc, int br, bool intern)
{
    Piece *pc = getPiece(ac, ar);
    if (!intern) {
        // OnMove
        whites = !whites;
    }

    _board[ac][ar] = '\0';
    save(bc, br, pc);

    if (!gameOver() && (br == 0 || br == 7) &&
        pc->type() == PAWN && (mode() != HUMAN_ONLINE || mainColor() == pc->color()))
    {
        // Promote
    }

    // OnMoveComplete
    if (pc->color() == mainColor() && mode() == HUMAN_ONLINE)
    {
        ((MainBoard*)(this->parent()->parent()))->sendMessage(tr("MOV %1x%2:%3x%4\r\n").arg(ac).arg(ar)
                                                .arg(bc).arg(br));
    }
    else if (pc->color() == mainColor() && mode() == HUMAN_COMPUTER)
    {
        computer->nextMove();
    }

    checkAlert();
}

Piece *Board::getPiece(int c, int r)
{
    return _pieces[r*8+c];
}

void Board::save(int c, int r, Piece *pc)
{
    _pieces.remove(r*8+c);
    _pieces[r*8+c] = pc;
    char p = ids[(int)pc->type()];
    _board[c][r] = pc->color() == BLACK ? toupper(p) : p;
}

bool Board::validMove(pieceType type, int c, int r, int dc, int dr, int *capture, bool first)
{
    *capture = -1;
    char piece = '\0', cpiece = '\0';
    pieceColor color;
    int ac = ::abs(c - dc);
    int ar = ::abs(r - dr);
    if (dc > 7 || dr > 7 || (piece = _board[c][r]) == '\0')
    {
        return false;
    }

    color = getColor(piece);
    if ((cpiece = _board[dc][dr]) != '\0')
    {
        if (getColor(cpiece) != color)
            *capture = dc * 8 + dr;
         else
             return false;
    }
    if (type == QUEEN)
    {
        if (c != dc && r != dr)
            type = BISHOP;
        else
            type = ROOK;
    }
    if (type == KNIGHT && !((ar + ac) == 3 && max(ar, ac) == 2))
    {
        return false;
    }
    else if (type == BISHOP)
    {
        if (dc == c || dr == r || ac != ar)
            return false;
        else
            return blocked(c, r, dc, dr) == -1;
    }
    else if (type == ROOK)
    {
        if (dr != r && dc != c)
            return false;
        else
            return blocked(c, r, dc, dr) == -1;
    }
    else if (type == PAWN)
    {
        int ina = color == mainColor() ? -1 : 1;
        int ipos = color == mainColor() ? 6 : 1;
        int dif = r + ina;

        if (!((dr == dif && ((*capture == -1 && c == dc) || (*capture != -1 && ac == 1)))
             || ((r == ipos && *capture == -1 && dr == (dif + ina) && _board[dc][dif] == '\0' && c == dc))))
            return false;
    }
    else if (type == KING)
    {
        if (!(((ac + ar) == 1) || ((ac + ar) == 2 && max(ac, ar) != 2)))
        {
            return false;
        }
    }

    return true;
}

int Board::blocked(int ac, int ar, int bc, int br)
{
    int bl = -1;
    int ica = ac != bc ? (bc > ac ? 1 : -1) : 0;
    int icb = ar != br ? (br > ar ? 1 : -1) : 0;
    int tc = ac + ica;
    int tr = ar + icb;
    while (true) {
        if ((br > ar && tr >= br) || (br < ar && tr <= br)
            || (bc > ac && tc >= bc) || (bc < ac && tc <= bc))
            break;
        if (_board[tc][tr] != '\0')
        {
            bl = (tc * 8) + tr;
            break;
        }
        tc += ica;
        tr += icb;
    }
    return bl;
}

void Board::capture(Piece *cpiece)
{
    cpiece->capture(true);
    cpiece->hide();
    if (cpiece->type() == KING)
    {
        gameOver(true);
        mode(UNSTARTED);
    }
}

QList<move_t> Board::generateValidMoves(pieceColor color, bool calc)
{
    QList<move_t> moves;
    for (int i = 0; i < 64; i++)
    {
        int c = i / 8, r = i % 8;
        char p = _board[c][r];
        if (p != '\0' && getColor(p) == color)
        {
            for (int n = 0; n < 64; n++)
            {
                int c2 = n / 8, r2 = n % 8;
                int capture = -1;
                if (validMove(getType(p), c, r, c2, r2, &capture, false))
                {
                    int score = 0;
                    if (calc)
                    {
                        char backBoard[8][8];
                        arrayCopy(Board::_board, backBoard, 8);
                        _board[c2][r2] = _board[c][r];
                        _board[c][r] = '\0';
                        score = BoardEvaluator::getBoardScore(color);
                        if (capture != -1)
                        {
                            score += (BoardEvaluator::pieceValue(_board[c2][r2]) - BoardEvaluator::pieceValue(p) / 10);
                        }
                        arrayCopy(backBoard, Board::_board, 8);
                    }

                    move_t m = {i, n, score, capture};
                    moves.append(m);
                }
            }
        }
    }
    return moves;
}

pieceColor Board::getColor(char c)
{
    return islower(c) ? WHITE : BLACK;
}

pieceType Board::getType(char c)
{
    for (int i = 0; i < 6; i++)
        if (ids[i] == tolower(c))
            return (pieceType)i;
    return UNKNOWN;
}

void Board::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-chessitem")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Board::dragMoveEvent(QDragMoveEvent *event)
{/*
    if (event->mimeData()->hasFormat("application/x-chessitem")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }*/
}

void Board::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-chessitem")) {
        QByteArray itemData = event->mimeData()->data("application/x-chessitem");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;
        QPoint pos = event->pos() - offset;

        int c = (int)::ceil((double)(pos.x() - 35) / 75);
        int r = (int)::ceil((double)(pos.y() - 35) / 75);

        curDrag->_move(c, r, &pixmap);
        /*int capture = -1;
        if (validMove(curDrag->type(), curDrag->col(), curDrag->row(), c, r, &capture, false)) {
            // save move
            if (capture != -1)
                this->capture(getPiece((capture/8), (capture%8)));
            makeMove(curDrag->col(), curDrag->row(), c, r);

            curDrag->col(c);
            curDrag->row(r);
        }

        curDrag->show();
        curDrag->setPixmap(pixmap);
        curDrag->move(curDrag->x(curDrag->col() * 75),
                       curDrag->y(curDrag->row() * 75));
*/
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Board::mousePressEvent(QMouseEvent *event)
{
    Piece *child = static_cast<Piece*>(childAt(event->pos()));
    if (!child)
        return;

    if (mode() == UNSTARTED || gameOver() || (mode() == HUMAN_HUMAN && !myTurn(child->color()))
        || (mode() != HUMAN_HUMAN && (mainColor() != child->color() || !myTurn())))
    {
        return;
    }

    curDrag = child;

    QPixmap pixmap = *child->pixmap();
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-chessitem", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);
    if (!drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
    {
        child->show();
        child->setPixmap(pixmap);
    }
}

void Board::checkAlert()
{
    if (!gameOver())
    {
        if (Board::checkCheck(whites ? WHITE : BLACK))
        {
            QMessageBox::information(0, tr("Chess"),
                              tr("jaque!"));
        }
    }
}

void Board::receiveCommand(QString msg)
{
    QString command = msg.left(3);
    if (command == "MOV")
    {
        QRegExp rx("MOV ([0-9]+)x([0-9]+):([0-9]+)x([0-9]+)");
        if (rx.exactMatch(msg.trimmed()))
        {
            QStringList list = rx.capturedTexts();
            if (list.count() == 5)
            {
                int ac = fix((list[1]).toInt());
                int ar = fix((list[2]).toInt());
                int bc = fix((list[3]).toInt());
                int br = fix((list[4]).toInt());
                Piece *p;
                if ((p = _pieces[ar*8+ac]) && p->color() != mainColor())
                    p->_move(bc, br);
            }
        }
    }
    else if (command == "PRM")
    {

    }
}

void Board::onMoveReady(move_t move)
{
    Piece *p;
    if ((p = getPiece(move.from/8, move.from%8)) && p->color() != mainColor()) {
        p->_move(move.to / 8, move.to % 8);
    }
}

bool Board::checkCheck(pieceColor color)
{
    char ck = color == WHITE ? 'k' : 'K';
    int pos = getPos(ck);
    int kc = pos / 8, kr = pos % 8;
    for (int i = 0; i < 64; i++)
    {
        int c = i / 8, r = i % 8;
        char p = _board[c][r];
        if (p != '\0' && getColor(p) != getColor(ck))
        {
            int capture = -1;
            if (validMove(getType(p), c, r, kc, kr, &capture))
            {
                return true;
            }
        }
    }

    return false;
}

int Board::getPos(char p, int distinct)
{
    for (int i = 0; i < 64; i++)
        if (p == _board[(i / 8)][(i % 8)] && (distinct == -1 || i != distinct))
            return i;
    return -1;
}

int Board::fix(int n)
{
    return ::abs(n - 7);
}

void Board::arrayCopy(char arr[][8], char arr2[][8], int s)
{
    for (int i = 0; i < s; i++)
    {
        for (int n = 0; n < s; n++)
        {
            arr2[i][n] = arr[i][n];
        }
    }
}

Board::~Board()
{
    delete lightTile;
    delete darkTile;
}
