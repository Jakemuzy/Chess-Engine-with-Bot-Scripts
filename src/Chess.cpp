#include "Chess.h"
#include <iostream>

//  Move struct
Move::Move(int _x, int _y) : x(_x), y(_y) {}

bool Move::operator==(const Move &other) const
{
    if (x == other.x && y == other.y)
        return true;
    return false;
}

//  If Move is in a vector containing possible moves
bool Move::inVector(const std::vector<Move> &moves) const
{
    for (int i = 0; i < moves.size(); i++)
    {
        if ((*this) == moves[i])
            return true;
    }
    return false;
}

void Move::print()
{
    std::cout << "X: " << x << ", " << "Y: " << y << " \n";
}


// Base class implementation
ChessPiece::ChessPiece() {}
ChessPiece::ChessPiece(Color _color) : color(_color) {}

Color ChessPiece::getColor()
{
    return color;
}

PieceType ChessPiece::getType()
{
    return type;
}

bool ChessPiece::move(int x, int y, int destX, int destY, ChessPiece* board[80])
{
    std::cerr << "ERROR: No piece occupies this space \n";
    return 0; 
}

void ChessPiece::print()
{
    std::cout << "Type: " << type << ", Color: " << (color == WHITE ? "White" : "Black") << ", Value: " << value << "\n";
}

std::string ChessPiece::printName()
{
    switch (type)
    {
    case PAWN:
        return "Pawn";
    case KNIGHT:
        return "Knight";
    case BISHOP:
        return "Bishop";
    case ROOK:
        return "Rook";
    case QUEEN:
        return "Queen";
    case KING:
        return "King";
    default:
        return "BLANK";
    }
}


// Pawn class
Pawn::Pawn(Color _color) 
{
    color = _color;
    type = PAWN;
    value = 1;
}

bool Pawn::move(int x, int y, int destX, int destY, ChessPiece* board[80])
{
    //  Direction
    int pos = x + y * 8;
    int sign = ((*board[pos]).getColor() == WHITE) ? -1 : 1;

    //  Don't need to check if move is out of bounds, because board already excludes them
    std::vector<Move> possibleMoves;

    //  Forward
    if((*board[(y + sign) * 8 + x]).getType() == BLANK)
        possibleMoves.push_back(Move(x, y + sign));

    //  Diag left
    if(x > 0)
    {
        ChessPiece& other = (*board[(y + sign) * 8 + (x - 1)]);
        if (other.getType() != BLANK && other.getColor() != (*board[pos]).getColor())
            possibleMoves.push_back(Move(x - 1, y + sign));
            
    }
    //  Diag right
    if(x < 7)
    {
        ChessPiece& other = (*board[(y + sign) * 8 + (x + 1)]);
        if (other.getType() != BLANK && other.getColor() != (*board[pos]).getColor())
            possibleMoves.push_back(Move(x + 1, y + sign));
    }
    
    Move dest(destX, destY);
    if (dest.inVector(possibleMoves))
        return true;

    std::cout << "Not a valid move for PAWN at (" << x << ", " << y << ")\n\n";
    return false;
}

//  Knight
Knight::Knight(Color _color) 
{
    color = _color;
    type = KNIGHT;
    value = 3;
}

bool Knight::move(int x, int y, int destX, int destY, ChessPiece* board[80])
{
    int pos = x + y * 8;

    //  Distance from piece
    int distX = abs(x - destX);
    int distY = abs(y - destY);

    //  If total distance from knight is 3, but not in a straight direction
    if(distX + distY == 3 && distX != 3 && distY != 3)
    {
        //Valid if moving to blank or enemy
        ChessPiece& other = (*board[(destY * 8) + destX]);
        if(other.getType() == BLANK || other.getColor() != (*board[pos]).getColor())
            return true;
    }

    std::cout << "Not a valid move for KNIGHT at (" << x << ", " << y << ")\n\n";
    return false;
}

//  Bishop
Bishop::Bishop(Color _color) 
{
    color = _color;
    type = BISHOP;
    value = 3;
}

bool Bishop::move(int x, int y, int destX, int destY, ChessPiece* board[80])
{
    return 1;
}

//  Rook
Rook::Rook(Color _color) 
{
    color = _color;
    type = ROOK;
    value = 5;
}

bool Rook::move(int x, int y, int destX, int destY, ChessPiece* board[80])
{
    
    return 1;
}

//  Queen
Queen::Queen(Color _color) 
{
    color = _color;
    type = QUEEN;
    value = 9;
}

bool Queen::move(int x, int y, int destX, int destY, ChessPiece* board[80])
{
    return 1;
}

//  King
King::King(Color _color)
{
    color = _color;
    type = KING;
    value = 2147483647;
}

bool King::move(int x, int y, int destX, int destY, ChessPiece* board[80])
{
    return 1;
}




//Board
Board::Board()
{
    board[0] = new Rook(BLACK);     board[1] = new Knight(BLACK);   board[2] = new Bishop(BLACK);   board[3] = new Queen(BLACK);  board[4] = new King(BLACK);   board[5] = new Bishop(BLACK);    board[6] = new Knight(BLACK);     board[7] = new Rook(BLACK);
    for(int i = 8; i < 16; i++){ board[i] = new Pawn(BLACK); }
    for(int i = 16; i < 64; i++){ board[i] = new ChessPiece(); }
    for(int i = 64; i < 72; i++){ board[i] = new Pawn(WHITE); }
    board[72] = new Rook(WHITE);     board[73] = new Knight(WHITE);   board[74] = new Bishop(WHITE);   board[75] = new Queen(WHITE);  board[76] = new King(WHITE);  board[77] = new Bishop(WHITE);   board[78] = new Knight(WHITE);    board[79] = new Rook(WHITE);

    //board[24 + 4] = new Knight(WHITE);
}

void Board::move(int x, int y, int destX, int destY)
{
    //  Board Bounds
    if (destX < 0 || destX > 7 || destY < 0 || destY > 7)
    {
        std::cerr << "ERROR: Destination is outside of board bounds \n";
        return;
    }
    if (x < 0 || x > 7 || y < 0 || y > 7)
    {
        std::cerr << "ERROR: Piece is outside of board bounds \n";
        return;
    }

    int pos = x + y * 8;
    int destPos = destX + destY * 8;

    if((*board[pos]).move(x, y, destX, destY, board))
    {
        board[destPos] = board[pos];
        board[pos] = new ChessPiece();
        std::cout << "\n";
    }
}

void Board::print()
{
    for (int i = 0; i < 80; i++)
    {
        std::cout << (*board[i]).printName() << " ";
        if ((i + 1) % 8 == 0) 
            std::cout << "\n";
    }
}
